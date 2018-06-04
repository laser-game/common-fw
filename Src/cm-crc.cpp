#include "cm-crc.hpp"

uint64_t CRC32::_generator_polynomial;
uint32_t CRC32::_table[256];

void CRC32::init(vector<uint8_t> gp)
{
    _generator_polynomial = 1;
    uint16_t i;

    for (i = 0; i < gp.size(); i++)
        _generator_polynomial += uint64_t(1) << gp[i];

    for (i = 0; i < 256; i++)
        _table[i] = _calculate(i);
}

uint32_t CRC32::_calculate(uint8_t byte)
{
    const uint64_t MASK_MSB  = 0x8000000000;
    const uint64_t MASK_CRC  = 0x00FFFFFFFF;
    const uint64_t MASK_DATA = 0xFF00000000;

    uint8_t i;
    uint64_t gp = _generator_polynomial;

    for (i = 0; !(gp & MASK_MSB); i++)
        gp <<= 1;

    uint64_t vector   = (uint64_t) byte << 32;
    uint64_t mask_bit = MASK_MSB;

    for (i = 0; (vector & MASK_DATA); i++, gp >>= 1, mask_bit >>= 1)
    {
        if (vector & mask_bit)
        {
            vector ^= gp;
        }
    }

    return (uint32_t) (vector & MASK_CRC);
}

uint32_t CRC32::calculate(uint8_t byte)
{
    return _table[byte];
}

uint32_t CRC32::calculate(CircularBuffer *buffer, uint16_t start, uint16_t size)
{
    uint32_t crc = ~0;
    uint16_t index, i;
    for (i = 0, index = start; i < size; i++, index++)
        crc = _table[(crc ^ buffer->read(index)) & 0xFF] ^ (crc >> 8);
    return ~crc;
}
