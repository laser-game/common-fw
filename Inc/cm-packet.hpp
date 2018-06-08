#ifndef __CM_PACKET_INLUDED__
#define __CM_PACKET_INLUDED__

#define PACKET_SIZE_MIN  8
#define PACKET_SIZE_MAX  512
#define PACKET_SIZE_HEAD 3
#define PACKET_SIZE_CRC  4
#define PACKET_SIZE_INFO PACKET_SIZE_HEAD + PACKET_SIZE_CRC

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include "cm-crc.hpp"
#include "cm-circular-buffer.hpp"
#include "cm-macro.hpp"

#include <vector>
using namespace std;

class Packet
{
private:
    uint8_t address;
    uint16_t size;
    vector<uint8_t> data;

    uint16_t index_start;
    uint16_t index_stop;

public:
    inline Packet(uint8_t address)
    {
        this->address     = address;
        this->index_start = 0;
        this->index_stop  = 0;
    }

    inline void set_address(uint8_t address)
    {
        this->address = address;
    }

    inline uint8_t get_address(void) const
    {
        return address;
    }

    inline uint16_t get_index_start(void) const
    {
        return this->index_start;
    }

    inline uint16_t get_index_stop(void) const
    {
        return this->index_stop;
    }

    inline uint16_t get_size(void) const
    {
        return this->size;
    }

    void create(CircularBuffer *buffer, vector<uint8_t> data);
    bool find(CircularBuffer *buffer);
};

#endif // ifndef __CM_PACKET_INLUDED__
