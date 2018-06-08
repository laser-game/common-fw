#ifndef __CM_CIRCULAR_BUFFER_INLUDED__
#define __CM_CIRCULAR_BUFFER_INLUDED__

#define CIRCULAR_BUFFER_SIZE 512

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include <vector>
using namespace std;

class CircularBuffer
{
private:
    uint16_t index_write;
    uint16_t index_read;
    uint8_t *data;
public:
    CircularBuffer();
    inline ~CircularBuffer(){ delete [] data; }

    inline uint16_t size(void) const { return CIRCULAR_BUFFER_SIZE; }

    inline uint16_t get_index_write(void) const { return index_write; }

    inline uint16_t get_index_read(void) const { return index_read; }

    inline void set_index_read(uint16_t index){ index_read = index; }

    inline uint16_t transform_index(uint16_t index) const
    {
        return (index >= CIRCULAR_BUFFER_SIZE) ? index % CIRCULAR_BUFFER_SIZE : index;
    }

    inline uint8_t read(uint16_t index) const { return data[transform_index(index)]; }

    void destroy_packet(uint16_t index){ ++data[index]; }

    void insert(uint8_t byte);
    void insert_random_array(uint16_t size);
    void print(void) const;
};

#endif // ifndef __CM_CIRCULAR_BUFFER_INLUDED__
