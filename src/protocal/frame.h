#pragma once

#include "stdint.h"

// #pragma pack (1)

typedef enum
{
    FRAME_NONE = 0,
    FRAME_IMU,
    FRAME_STRING,
    FRAME_CONTROL,

} Frame_ID_t;

typedef struct
{
    float gyro[3];
    float accel[3];
    float mag[3];

} Frame_IMU_t;

typedef struct
{
    char string[255];

} Frame_String_t;

typedef struct
{
    float throttle[2];
    float sensor[2];

} Frame_Ctrl_t;


typedef struct
{
    Frame_ID_t id;
    uint32_t tick;

    union {
        uint8_t raw[256];
        Frame_IMU_t imu;
        Frame_String_t string;
    };

} Frame_t;

