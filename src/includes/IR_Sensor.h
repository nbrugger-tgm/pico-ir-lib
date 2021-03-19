//
// Created by nils on 18.03.21.
//

#ifndef TEST_PROJECT_IR_SENSOR_H
#define TEST_PROJECT_IR_SENSOR_H


#include <pico.h>

/**
 * An Infrared sensor bound to a certain pin
 */
class IR_Sensor {
public:
    /**
     * Autoconfigures the pin to the given parameters and creates an IR sensor
     * @param pin the GPIO pin to read from
     * @param hz the frequency to read at
     * @param active_low true if the sensor uses active low mode
     */
    IR_Sensor(uint pin, uint hz, bool active_low = false);

    /**
     * Read from the pin at the given frequency
     * @param buff the number to write the result into
     * @param len the number of bits to read
     */
    void read(uint* buff,uint len);
    /**
     * Read from the pin at the given frequency
     * @param buff the number to write the result into
     * @param len the number of bits to read
     */
    void read(int* buff, uint len);
    /**
     * Read from the pin at the given frequency
     * @param buff the bits (bool[]) to write the result into
     * @param len the number of bits to read
     */
    void read(bool buff[], uint len);

    /**
     * Changes the operation frequency of the sensor
     * @param hz the new frequency
     */
    void change_freq(uint hz);

    /**
     * The pin this sensor uses
     */
     const uint* get_pin = &pin;
private:
    uint pin;
    uint hz;
    int correction;
    int sleep_period_us;
};


#endif //TEST_PROJECT_IR_SENSOR_H
