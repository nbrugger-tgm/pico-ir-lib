//
// Created by nils on 19.03.21.
//

#ifndef TEST_PROJECT_NAC_PROTOCOLL_H
#define TEST_PROJECT_NAC_PROTOCOLL_H


#include <map>
#include "IR_Sensor.h"

/**
 * A method to catch NAC transmissions
 * @param addr the transmitted address
 * @param cmd the transmitted command
 */
typedef void (*NAC_Callback)(uint8_t,uint8_t);

/**
 * @param addr the address for which the method was called
 */
typedef void (*command_handler_t)(uint8_t);
typedef std::map<uint8_t,command_handler_t> command_map_t;

class NEC_Protocol {
private:
    const uint pulse_dur = 562;

    uint last_cmd_start_us = 0;
    const uint hold_pause_ms = 110;
    const uint hold_pause_us_max = (hold_pause_ms + 5)*1000;
    const uint hold_pause_us_min = (hold_pause_ms - 3)*1000;
    const uint hold_high_probes = (4500/2)/pulse_dur;
    const uint hold_low_probes = 9000/pulse_dur;
    bool wait_for_hold_pulse_end = false;

    uint8_t last_addr = 0;
    uint8_t last_cmd = 0;

    bool par = false;
    bool ir_sign = false;
    uint code = 0;
    uint data_pos = 0;
    bool data[32];
    uint rise_time = 0;
    bool read_high = false;
    const uint min_H_time = pulse_dur*2.8;
    const uint max_H_time = pulse_dur*3.2;
    const uint min_L_time = pulse_dur*0.9;
    const uint max_L_time = pulse_dur*1.1;
    const uint par_low_probes = 9000/pulse_dur;
    const uint par_high_probes = 4500/pulse_dur;
    const uint half_pulse = pulse_dur/2;
    NAC_Callback callback;
    command_map_t* command_table;
    unsigned int pin;
    uint low_probes;
    uint h_probes;
    uint32_t now;
    uint32_t time;
public:
    /**
     * The interrupt for the IR_LED pin
     * DO NOT CALL THIS YOURSELF!
     */
    void internal_interrupt(uint gpio, uint32_t events);
    /**
     * @param callback This method is called when the NAC receives a transmission
     */
    NEC_Protocol(IR_Sensor* sensor, NAC_Callback callback);
    /**
     * Creates a NAC protocol that resolves commands agains a table and calls regarding callback functions
     * @param sensor the sensor to read the values from
     * @param command_table a table including
     */
    NEC_Protocol(IR_Sensor* sensor, command_map_t* command_table);
    /**
     * resets the protocol to start listening for the next transmission
     */
    void reset();

    /**
     * Registers the interrupt to the pico
     *
     * ATTENTION: PICO ONLY ALLOWS A SINGLE INTERRUPT AT A TIME
     */
    void register_interrupt();



};


#endif //TEST_PROJECT_NAC_PROTOCOLL_H
