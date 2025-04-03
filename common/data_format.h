#ifndef DATA_FORMAT_H
#define DATA_FORMAT_H

#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t name[20];
    uint8_t message[50];
} data_1_t;

typedef struct __attribute__((packed)) {
    uint8_t name[20];
    uint8_t message[50];
} data_2_t;

typedef union __attribute__((packed)) {
    data_1_t data1;
    data_2_t data2;
} message_t;

#endif
