#pragma once

#include <stdint.h>

struct PdiParam
{
    uint16_t Slot = 0;
    uint8_t  Subslot = 0;
    uint16_t Index = 0;
    uint8_t  Subindex = 0;
};
