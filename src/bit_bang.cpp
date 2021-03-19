//
// Created by nils on 18.03.21.
//

#include <cstdio>
#include <climits>
#include "includes/bit_bang.h"


void shift(uint *number, bool bit) {
    *number = *number << 1;
    *number = *number | (bit ? 1 : 0);
}



void print_binary(uint number) {
    for (int i = 0; i < sizeof(typeof(number))*2; ++i) {
        printf("%u",number>>i & 1);
    }
}


void binary_to_int(bool *buf,int bufsize, uint *number) {
    for(int i = 0;i<bufsize;i++){
        shift(number,buf[i]);
    }
}
