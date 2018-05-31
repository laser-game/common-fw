#ifndef __CM_UART_INCLUDED__
#define __CM_UART_INCLUDED__

#define UART_TIMEOUT 0xFFFF

#ifdef STM32_F4
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
        rx();
    }

    inline void tx(string str)
    {
        HAL_UART_Transmit(huart, (uint8_t *) str.c_str(), str.size(), UART_TIMEOUT);
    }

    inline void tx(uint8_t byte)
    {
        HAL_UART_Transmit(huart, (uint8_t *) &byte, 1, UART_TIMEOUT);
    }

    inline void rx(void)
    {
        HAL_UART_Receive_IT(huart, buffer_rx, 1);
    }

    inline UART_HandleTypeDef * get_huart()
    {
        return huart;
    }
};

#endif // ifndef __CM_UART_INCLUDED__
