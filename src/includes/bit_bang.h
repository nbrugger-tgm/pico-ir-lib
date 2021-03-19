//
// Created by nils on 18.03.21.
//
#ifndef TEST_PROJECT_BIT_BANG_H
#define TEST_PROJECT_BIT_BANG_H
/**
 * Shifts a bit into the number. Works like a shift register.
 *
 * shift(0110,1) will result in the number that was 0110 bevore to be 10110 with 1 being the LSB
 * @param number the number to use as shift register
 * @param bit the bit to shift
 */
void shift(uint* number, bool bit);

/**
 * Uses printf to print a binary representation of a number
 * @param number the number to print in binary
 */
void print_binary(uint number);

/**
 * Converts a series of bits (aka bool[]) to a int
 * @param buf the bits to convert
 * @param bufsize the number of bits
 * @param number the number to save the result into
 */
void binary_to_int(bool buf[],int bufsize,uint* number);
#endif //TEST_PROJECT_BIT_BANG_H
