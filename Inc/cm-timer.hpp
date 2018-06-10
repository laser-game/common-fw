#ifndef __CM_TIM_INCLUDED__
#define __CM_TIM_INCLUDED__

#define UART_TIMEOUT 0xFFFF

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include <vector>
#include <string>

using namespace std;

class Timer
{
private:
    TIM_HandleTypeDef *htim;
public:
    inline Timer(TIM_HandleTypeDef *htim)
    {
        this->htim = htim;
    }

    inline TIM_HandleTypeDef * get_htim(void)
    {
        return htim;
    }

    inline void start_tim(void)
    {
        HAL_TIM_Base_Start(htim);
    }

    inline void start_tim_it(void)
    {
        HAL_TIM_Base_Start_IT(htim);
    }

    inline void stop_tim(void)
    {
        HAL_TIM_Base_Stop(htim);
    }

    inline void stop_tim_it(void)
    {
        HAL_TIM_Base_Stop_IT(htim);
    }

    inline void set_tim_cnt(uint16_t cnt)
    {
        htim->Instance->CNT = cnt;
    }

    inline uint16_t get_tim_cnt(void)
    {
        return htim->Instance->CNT;
    }
};

#endif // ifndef __CM_TIM_INCLUDED__
