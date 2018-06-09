#include "cm-packet.hpp"

void Packet::create(void)
{
    uint32_t crc;
    uint16_t size  = data.size() + PACKET_SIZE_INFO;

    this->stream.push_back(address);
    this->stream.push_back((uint8_t) (size >> 8));
    this->stream.push_back((uint8_t) (size & 0xFF));

    for (uint16_t i = 0; i < data.size(); i++)
        this->stream.push_back(data[i]);

    crc = CRC32::calculate(this->stream.data(), this->stream.size());
    this->stream.push_back((uint8_t) (crc >> 24));
    this->stream.push_back((uint8_t) (crc >> 16));
    this->stream.push_back((uint8_t) (crc >> 8));
    this->stream.push_back((uint8_t) (crc >> 0));
}

void Packet::create(CircularBuffer *buffer, vector<uint8_t> data)
{
    uint32_t crc;
    uint16_t size  = data.size() + PACKET_SIZE_INFO;
    uint16_t start = buffer->get_index_write();

    buffer->insert(address);
    buffer->insert((uint8_t) (size >> 8));
    buffer->insert((uint8_t) (size & 0xFF));

    for (uint8_t i = 0; i < data.size(); i++)
        buffer->insert(data[i]);

    crc = CRC32::calculate(buffer, start, data.size() + PACKET_SIZE_HEAD);
    buffer->insert((uint8_t) (crc >> 24));
    buffer->insert((uint8_t) (crc >> 16));
    buffer->insert((uint8_t) (crc >> 8));
    buffer->insert((uint8_t) (crc >> 0));
}

bool Packet::find(CircularBuffer *buffer)
{
    uint32_t crc;
    uint16_t size, index = 0;

    for (uint16_t i = 0; i < buffer->size(); i++, index++)
        if (buffer->read(index) == address or buffer->read(index == BROADCAST_ADDRESS))
        {
            size  = uint16_t(buffer->read(index + 1)) << 8;
            size += uint16_t(buffer->read(index + 2));
            if (size >= PACKET_SIZE_MIN and size <= PACKET_SIZE_MAX and size <= CIRCULAR_BUFFER_SIZE)
            {
                crc  = uint32_t(buffer->read(index + size - 4)) << 24;
                crc += uint32_t(buffer->read(index + size - 3)) << 16;
                crc += uint32_t(buffer->read(index + size - 2)) << 8;
                crc += buffer->read(index + size - 1);
                if (crc == CRC32::calculate(buffer, index, size - PACKET_SIZE_CRC))
                {
                    buffer->destroy_packet(index);
                    this->size        = size;
                    this->index_start = buffer->transform_index(index + PACKET_SIZE_HEAD);
                    this->index_stop  = buffer->transform_index(index + size - 1 - PACKET_SIZE_CRC);

                    this->data.clear();
                    for (i = 0; i < (size - PACKET_SIZE_INFO); i++)
                        this->data.push_back(buffer->read(i + PACKET_SIZE_HEAD));

                    return true;
                }
            }
        }
    return false;
}
