#include <pico/stdlib.h>
#include <cstdio>
#include <includes/NAC_Protocoll.h>
#include <includes/bit_bang.h>

uint sensor_pin = 27;
void on_receive(uint8_t addr,uint8_t cmd);

void on_ON(uint8_t addr);
void on_OFF(uint8_t addr);
void on_LIGHT(uint8_t addr);
void on_8H(uint8_t addr);
void on_4H(uint8_t addr);
void on_MULTI(uint8_t addr);
command_map_t cmds = {
        {0x48,&on_ON},
        {0x58,&on_OFF},
        {0x78,&on_LIGHT},
        {0x80,&on_4H},
        {0x40,&on_8H},
        {0xC0,&on_MULTI}
};

int main() {
    stdio_init_all();
    IR_Sensor s = IR_Sensor(sensor_pin, 0,true);
    NAC_Protocoll prot = NAC_Protocoll(&s, &cmds);
    prot.register_callback();
    while (1);
}
void on_receive(uint8_t addr, uint8_t cmd) {
    printf("[NAC Package] ");
    printf("Address : ");
    print_binary(addr);
    printf("   Command: ");
    print_binary(cmd);
    printf(" (0x%X)",cmd);
    printf("\n");
}

void on_ON(uint8_t addr) {
    printf("ON!!");
}

void on_OFF(uint8_t addr) {
    printf("OFF!!");
}

void on_LIGHT(uint8_t addr) {
    printf("LIGHT!!");
}

void on_8H(uint8_t addr) {
    printf("8H!!");
}

void on_MULTI(uint8_t addr) {
    printf("MULTI!!");
}

void on_4H(uint8_t addr) {
    printf("4H!!");
}






