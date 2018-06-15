#ifndef __CM_GPIO_INCLUDED__
#define __CM_GPIO_INCLUDED__


#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include "cm-macro.hpp"

#include <vector>
#include <string>
using namespace std;

class Pin
{
private:
    uint16_t pin;
    GPIO_TypeDef *port;
public:
    inline Pin(GPIO_TypeDef *port, uint16_t pin)
    {
        this->pin = pin;
        this->port = port;
    }

    inline void set(bool level)
    {
        HAL_GPIO_WritePin(port, pin, bool_to_gpio_pin_state(level));
    }

    inline bool get(void)
    {
        return HAL_GPIO_ReadPin(port, pin);
    }
};

#endif // ifndef __CM_GPIO_INCLUDED__
