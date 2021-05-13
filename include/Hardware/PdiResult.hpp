#pragma once

#include <stdint.h>

struct PdiResult
{
    bool ServiceDone = false;
    uint16_t  ErrorCode = 0;
    uint16_t  AddInfo = 0;
};
