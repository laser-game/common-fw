#ifndef __CM_PACKET_INLUDED__
#define __CM_PACKET_INLUDED__

#include <vector>

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include "cm-crc.hpp"
#include "cm-circular-buffer.hpp"
#include "cm-macro.hpp"

using namespace std;

class Packet
{
private:
    uint8_t address;
    uint16_t size;
    vector<uint8_t> data;
    const uint8_t PACKET_SIZE_MIN  = 8;
    const uint16_t PACKET_SIZE_MAX = 512;
    const uint8_t PACKET_SIZE_HEAD = 3;
    const uint8_t PACKET_SIZE_CRC  = 4;
    const uint8_t PACKET_SIZE_INFO = PACKET_SIZE_HEAD + PACKET_SIZE_CRC;
public:
    inline Packet(uint8_t address)
    {
        this->address = address;
    }

    inline void set_address(uint8_t address)
    {
        this->address = address;
    }

    inline uint8_t get_address(void) const
    {
        return address;
    }

    void create(CircularBuffer *buffer, vector<uint8_t> data);
    void find(CircularBuffer *buffer);
};

#endif // ifndef __CM_PACKET_INLUDED__
