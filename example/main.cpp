#include <pico/stdlib.h>
#include <cstdio>

//This are the infrared includes
#include <includes/NAC_Protocoll.h>
#include <includes/bit_bang.h>

//you need a single GPIO pin
uint sensor_pin = 27;


void on_receive(uint8_t addr,uint8_t cmd);


//Listener method definitions
void on_ON(uint8_t addr);
void on_OFF(uint8_t addr);
void on_LIGHT(uint8_t addr);
void on_8H(uint8_t addr);
void on_4H(uint8_t addr);
void on_MULTI(uint8_t addr);


//command map
//this maps IR addresses (eg. different buttons) to functions
command_map_t cmds = {
        {0x48,&on_ON}, //using &function_name to create a function reference
        {0x58,&on_OFF},
        {0x78,&on_LIGHT},
        {0x80,&on_4H},
        {0x40,&on_8H},
        {0xC0,&on_MULTI}
};

int main() {
    stdio_init_all();

    //Creating a sensor on the regarding pin
    //hz is not important for the NIC protocoll as it is not hertz based
    //my sensor is (as most sensors are) active low
    IR_Sensor s = IR_Sensor(sensor_pin, 0,true);

    //now a Protocol (In this case NAC) is created for the sensor
    NAC_Protocoll prot = NAC_Protocoll(&s, &cmds);


    //Use this if you want to handle keycodes yourself
    //NAC_Protocoll prot = NAC_Protocoll(&s, &on_receive);


    //this is important. ATTENTION Pico supports only a single interrupt at a time so you can only use one Sensor (sadly)
    prot.register_callback();

    //also important if you do not do this the pico will exit
    while (1);
}

/**
 * A listener for the NAC protocol.
 * Is called when the protocol received a command
 * @param addr
 * @param cmd
 */
void on_receive(uint8_t addr, uint8_t cmd) {
    printf("[NAC Package] ");
    printf("Address (0x%x): ",addr);
    print_binary(addr);
    printf("   Command: ");
    print_binary(cmd);
    printf(" (0x%X)",cmd);
    printf("\n");
}

void on_ON(uint8_t addr) {
    printf("ON!!\n");
}

void on_OFF(uint8_t addr) {
    printf("OFF!!\n");
}

void on_LIGHT(uint8_t addr) {
    printf("LIGHT!!\n");
}

void on_8H(uint8_t addr) {
    printf("8H!!\n");
}

void on_MULTI(uint8_t addr) {
    printf("MULTI!!\n");
}

void on_4H(uint8_t addr) {
    printf("4H!!\n");
}






