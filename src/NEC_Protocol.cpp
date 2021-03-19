//
// Created by nils on 19.03.21.
//

#include <hardware/timer.h>
#include <hardware/gpio.h>
#include <map>
#include "includes/NEC_Protocol.h"
#include "includes/bit_bang.h"

void c_level_ir_interrupt(uint gpio,uint32_t events);
void command_resolver_callback(uint8_t addr, uint8_t cmd);

std::map<uint8_t, command_handler_t>* c_level_command_table;
void NEC_Protocol::internal_interrupt(uint gpio, uint32_t events) {
    if(wait_for_hold_pulse_end) {
        now = time_us_32();
        busy_wait_us_32(half_pulse);
        ir_sign = gpio_get(pin);
        if(ir_sign){
            printf("Hold end pulse wasn't low\n");
            reset();
            return;
        }
        busy_wait_us_32(pulse_dur);
        ir_sign = gpio_get(pin);
        if(!ir_sign){
            while (!gpio_get(pin));
            printf("Hold endpulse is too long (%lu us)\n",time_us_32()-now);
            reset();
            return;
        }
        wait_for_hold_pulse_end = false;
        par = false;
        callback(last_addr, last_cmd);
    }else if(!par) {
//test low parity
        now = time_us_32();
        time = now-last_cmd_start_us;
        bool accept_repeat = time >= hold_pause_us_min && time <= hold_pause_us_max;


        low_probes = par_low_probes;
        if(accept_repeat){
            low_probes = hold_low_probes;
        }else{
            reset();
        }
        for (int i = 0; i < low_probes; ++i) {
            busy_wait_us_32(pulse_dur);
            ir_sign = gpio_get(gpio);
            if (ir_sign) {
                printf("PARITY probe %d/%d was high\n",i,low_probes);
                reset();
                return;
            }
        }

        //test parrity high
        h_probes = par_high_probes;
        if(accept_repeat)
            h_probes = hold_high_probes;
        for (int i = 0; i < h_probes; ++i) {
            busy_wait_us_32(pulse_dur);
            ir_sign = gpio_get(gpio);
            if(!ir_sign){
                printf("PARITY probe %d/%d was low\n",i,h_probes);
                reset();
                return;
            }
        }
        last_cmd_start_us = now;
        if(accept_repeat){
            wait_for_hold_pulse_end = true;
            par = false;
        }else{
            par = true;
        }
    }else{
        if(read_high){
            rise_time = time_us_32()-rise_time;
            if(rise_time >= min_H_time && rise_time <= max_H_time){
                data[data_pos++] = true;
            }else if(rise_time >= min_L_time && rise_time <= max_L_time){
                data[data_pos++] = false;
            }else{
                printf("Time for high pulse was nether 3x or 1x (single pulse time: %d us, this pulse %d us)\n",pulse_dur,rise_time);
                reset();
                return;
            }
            if(data_pos == 32){
                uint trans = 0;
                binary_to_int(data,32,&trans);
                uint8_t bit_mask = 0b11111111;
                uint8_t i_cmd = bit_mask & trans;
                uint8_t cmd = bit_mask & trans >> 8;
                uint8_t i_addr = bit_mask & trans >> 16;
                uint8_t addr = bit_mask & trans >> 24;
                if((addr ^ i_addr) != bit_mask)
                    printf("I_ADDR wasn't the inverted address! (I_ADDR: %u, ADDR: %u)",i_addr,addr);
                if((cmd ^ i_cmd) != bit_mask)
                    printf("I_CMD wasn't the inverted command! (I_CMD: %u, CMD: %u)",i_cmd,cmd);
                c_level_command_table = this->command_table;
                last_cmd = cmd;
                last_addr = addr;
                callback(addr,cmd);
                par = false;
                data_pos = 0;
                read_high = false;
                wait_for_hold_pulse_end = false;
                return;
            }
            read_high = false;
        }
        busy_wait_us_32(half_pulse);
        ir_sign = gpio_get(gpio);
        if (ir_sign){
            printf("Error in receival (bit: %d)! Expected low!\n",data_pos);
            reset();
            return;
        }
        busy_wait_us_32(half_pulse);
        rise_time = time_us_32();
        read_high = true;
    }

}

void NEC_Protocol::reset(){
    par = false;
    read_high = false;
    data_pos = 0;
    last_cmd_start_us = 0;
    wait_for_hold_pulse_end = false;
}
static std::map<int, NEC_Protocol*> ir_pin_map;
NEC_Protocol::NEC_Protocol(IR_Sensor* sensor, NAC_Callback callback) {
    this->callback = callback;
    pin = *(sensor->get_pin);
    ir_pin_map[pin] = this;
}

void NEC_Protocol::register_interrupt() {
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, true, &c_level_ir_interrupt);
}

NEC_Protocol::NEC_Protocol(IR_Sensor *sensor, command_map_t* command_table) {
    this->callback = &command_resolver_callback;
    pin = *(sensor->get_pin);
    ir_pin_map[pin] = this;
    this->command_table = command_table;
}

void c_level_ir_interrupt(uint gpio, uint32_t events) {
    ir_pin_map[gpio]->internal_interrupt(gpio,events);
}
void command_resolver_callback(uint8_t addr, uint8_t cmd) {
    auto it = c_level_command_table->find(cmd);
    if(it != c_level_command_table->end())
    {
        command_handler_t handler = it->second;
        handler(addr);
    }else{
        printf("No command handler for %X",cmd);
    }
}
