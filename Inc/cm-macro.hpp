#ifndef __CM_MACRO_INCLUDED__
#define __CM_MACRO_INCLUDED__


#include <vector>

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

using namespace std;

#define vector_uint8_t_array(array ...) \
    ( \
      vector<uint8_t>({ array }) \
    )

#define gpio_pin_state_to_int(pin_state) \
    ( \
      (pin_state == GPIO_PIN_SET) ? 1 : 0 \
    )

#define gpio_pin_state_to_bool(pin_state) \
    ( \
      (pin_state == GPIO_PIN_SET) ? true : false \
    )

#define bool_to_gpio_pin_state(pin_state) \
    ( \
      (pin_state) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET) \
    )

#endif // ifndef __CM_MACRO_INCLUDED__
