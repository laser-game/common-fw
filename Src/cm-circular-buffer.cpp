#include "cm-circular-buffer.hpp"

CircularBuffer::CircularBuffer()
{
    index_write = 0;
    index_read  = 0;
    data        = new uint8_t[CIRCULAR_BUFFER_SIZE];
}

void CircularBuffer::insert(uint8_t byte)
{
    data[index_write] = byte;
    if (++index_write >= CIRCULAR_BUFFER_SIZE)
        index_write = 0;
}

/*void CircularBuffer::print() const
{
    printf("buffer:\n");
    for (uint16_t i = 0; i < CIRCULAR_BUFFER_SIZE; i++)
    {
        if ((i % 32) == 0 && i)
            printf("\n");
        printf("%02X ", data[i]);
    }
    printf("\n\n");
}*/
