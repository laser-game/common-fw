#ifndef __CM_UART_INCLUDED__
#define __CM_UART_INCLUDED__

#define UART_TIMEOUT 0xFFFF

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include <vector>
#include <string>

using namespace std;

class UART
{
private:
    UART_HandleTypeDef *huart;
public:
    uint8_t buffer_rx[1];
    uint8_t buffer_tx[1];

    inline UART(UART_HandleTypeDef *huart)
    {
        this->huart = huart;
    }

    inline void set_baudrate(uint32_t baudrate = 9600)
    {
        huart->Init.BaudRate = baudrate;
        HAL_UART_Init(huart);
    }

    inline HAL_StatusTypeDef tx(uint8_t byte)
    {
        return HAL_UART_Transmit(huart, (uint8_t *) &byte, 1, UART_TIMEOUT);
    }

    inline HAL_StatusTypeDef tx(uint8_t *byte_array, uint16_t size, uint32_t timeout = UART_TIMEOUT)
    {
        return HAL_UART_Transmit(huart, byte_array, size, timeout);
    }

    inline HAL_StatusTypeDef tx(vector<uint8_t> vector_bytes)
    {
        return HAL_UART_Transmit(huart, (uint8_t *) vector_bytes.data(), vector_bytes.size(), UART_TIMEOUT);
    }

    inline HAL_StatusTypeDef tx(string str)
    {
        return HAL_UART_Transmit(huart, (uint8_t *) str.c_str(), str.size(), UART_TIMEOUT);
    }

    inline HAL_StatusTypeDef rx(uint8_t *p_data, uint16_t size, uint32_t timeout = UART_TIMEOUT)
    {
        return HAL_UART_Receive(huart, p_data, size, timeout);
    }

    inline HAL_StatusTypeDef rx_it(void)
    {
        return HAL_UART_Receive_IT(huart, buffer_rx, 1);
    }

    inline UART_HandleTypeDef * get_huart()
    {
        return huart;
    }
};

#endif // ifndef __CM_UART_INCLUDED__
