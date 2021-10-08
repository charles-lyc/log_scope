#pragma once

#include "frame.h"
#include "qwidget.h"

typedef struct
{
    uint8_t head;
    uint16_t crc16;

    uint8_t payload_length;
    Frame_t payload[256];

} Pack_t;

class Package
{
private:
    Pack_t packTx;
    Pack_t packRx;

public:
    Package();
    ~Package();

    bool Parse(Frame_t *frame, char dataByte);
    void Pack(Frame_t *frame);
};


