//
// Created by nils on 18.03.21.
//

#ifndef TEST_PROJECT_IR_SENSOR_H
#define TEST_PROJECT_IR_SENSOR_H


#include <pico.h>

class IR_Sensor {
public:
    /**
     * @param pin the GPIO pin to read from
     * @param hz the frequency to read at
     * @param active_low true if the sensor uses active low mode
     */
    IR_Sensor(uint pin, uint hz, bool active_low = false);

    void read(uint* buff,uint len);
    void read(int* buff, uint len);
    void read(bool buff[], uint len);
    void change_freq(uint hz);
    uint pin;
private:
    uint hz;
    int correction;
    int sleep_period_us;
};


#endif //TEST_PROJECT_IR_SENSOR_H
