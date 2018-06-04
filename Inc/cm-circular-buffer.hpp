#ifndef __CM_CIRCULAR_BUFFER_INLUDED__
#define __CM_CIRCULAR_BUFFER_INLUDED__

#include <vector>

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

using namespace std;

class CircularBuffer
{
private:
    const uint16_t BUFFER_SIZE = 512;
    uint16_t index_write;
    uint16_t index_read;
    uint8_t *data;
public:
    CircularBuffer();
    inline ~CircularBuffer(){ delete [] data; }

    inline uint16_t size(void) const { return BUFFER_SIZE; }

    inline uint16_t get_index_write(void) const { return index_write; }

    inline uint16_t get_index_read(void) const { return index_read; }

    inline void set_index_read(uint16_t index){ index_read = index; }

    inline uint16_t transform_index(uint16_t index) const
    {
        return (index >= BUFFER_SIZE) ? index % BUFFER_SIZE : index;
    }

    inline uint8_t read(uint16_t index) const { return data[transform_index(index)]; }

    void insert(uint8_t byte);
    void insert_random_array(uint16_t size);
    void print(void) const;
};

#endif // ifndef __CM_CIRCULAR_BUFFER_INLUDED__
