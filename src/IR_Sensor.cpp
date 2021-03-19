//
// Created by nils on 18.03.21.
//
#if !runLocal
#include <hardware/timer.h>
#include <includes/IR_Sensor.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>


IR_Sensor::IR_Sensor(uint pin, uint hz,bool active_low) {
    change_freq(hz);
    this->pin = pin;
    gpio_init(pin);
    if(active_low)
        gpio_pull_up(pin);
    else
        gpio_pull_down(pin);
    bi_decl(bi_1pin_with_name((int)pin,"IR Sensor"));
}

void IR_Sensor::change_freq(uint hz) {
    this->hz = hz;
    this->correction = 1000000%hz;
    this->sleep_period_us = (1000000-correction)/hz;
}

void IR_Sensor::read(uint *buff, uint len) {
    for (int i = 0;i<len;i++){
        *buff = *buff << 1;
        if(gpio_get(pin))
            *buff = *buff | 1;
        busy_wait_us_32(sleep_period_us);
        if(i%hz == 0)
            busy_wait_us_32(correction);
    }
}

void IR_Sensor::read(int *buff, uint len) {
    for (int i = 0;i<len;i++){
        *buff = *buff << 1;
        if(gpio_get(pin))
            *buff = *buff | 1;
        busy_wait_us_32(sleep_period_us);
        if(i%hz == 0)
            busy_wait_us_32(correction);
    }
}

void IR_Sensor::read(bool buff[], uint len) {
    for (int i = 0;i<len;i++){
        buff[i] = gpio_get(pin);
        busy_wait_us_32(sleep_period_us);
        if(i%hz == 0)
        busy_wait_us_32(correction);
    }
}
#endif