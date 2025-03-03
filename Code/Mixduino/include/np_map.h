
#ifndef ARDUINO_NP_MAP_H
#define ARDUINO_NP_MAP_H
#include <Arduino.h>

#pragma once

//////////////////////////////////////
// NEOPIXELS

const uint8_t NP_PADL1    = 0;
const uint8_t NP_PADL2    = 1;
const uint8_t NP_PADL3    = 2;
const uint8_t NP_PADL4    = 3;
const uint8_t NP_PADL5    = 4;
const uint8_t NP_PADL6    = 5;
const uint8_t NP_PADL7    = 6;
const uint8_t NP_PADL8    = 7;
const uint8_t NP_RANGE_L  = 8;
const uint8_t NP_SYNC_L   = 9;
const uint8_t NP_PADR1   = 10;
const uint8_t NP_PADR2   = 11;
const uint8_t NP_PADR3   = 12;
const uint8_t NP_PADR4   = 13;
const uint8_t NP_PADR5   = 14;
const uint8_t NP_PADR6   = 15;
const uint8_t NP_PADR7   = 16;
const uint8_t NP_PADR8   = 17;
const uint8_t NP_DECK_SEL = 18;
const uint8_t NP_RANGE_R  = 19;
const uint8_t NP_SYNC_R   = 20;

const uint8_t px_padl_set[] = {
    NP_PADL1,
    NP_PADL2,
    NP_PADL3,
    NP_PADL4,
    NP_PADL5,
    NP_PADL6,
    NP_PADL7,
    NP_PADL8
};

const uint8_t px_padr_set[] = {
    NP_PADR1,
    NP_PADR2,
    NP_PADR3,
    NP_PADR4,
    NP_PADR5,
    NP_PADR6,
    NP_PADR7,
    NP_PADR8
};

#endif
