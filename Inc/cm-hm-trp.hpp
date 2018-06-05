#ifndef __CM_HMTRP_INLUDED__
#define __CM_HMTRP_INLUDED__

#ifdef STM32_F0
# include "stm32f0xx_hal.h"
#elif defined STM32_F4
# include "stm32f4xx_hal.h"
#endif

#include "cm-uart.hpp"
#include "cm-macro.hpp"

#include <vector>
#include <string>

using namespace std;

class HMTRP : public UART
{
private:
    uint32_t working_frequency;
    uint32_t wireless_data_rate;
    uint16_t receiving_bandwidth;
    uint8_t frequency_deviation;
    uint8_t transmission_power;
    uint32_t uart_transfer_speed;

    void cmd(vector<uint8_t> vector_bytes);
    bool check_ok(void);
    bool check_data_rate(uint32_t baudrate);
    bool read_config(void);
    bool reset_to_default(void);
    bool set_wireless_data_rate(uint32_t baudrate);
    bool set_uart_transfer_speed(uint32_t baudrate);
    bool set_receiving_bandwidth(uint16_t receiving_bandwidth);
    bool set_frequency_deviation(uint8_t frequency_deviation);
    bool set_transmission_power(uint8_t transmission_power);

    inline void enable(bool ena = true)
    {
        HAL_GPIO_WritePin(RF_ENABLE_GPIO_Port, RF_ENABLE_Pin, bool_to_gpio_pin_state(not ena));
    }

    inline void config(bool cnf = true)
    {
        HAL_GPIO_WritePin(RF_CONFIG_GPIO_Port, RF_CONFIG_Pin, bool_to_gpio_pin_state(not cnf));
    }

public:
    HMTRP(
      UART_HandleTypeDef *huart,
      uint32_t            baudrate = 57600,
      uint8_t             transmission_power = 7,
      uint16_t            receiving_bandwidth = 105,
      uint8_t             frequency_deviation = 35
    );

    void print_config(void);

    inline uint32_t get_working_frequency(void)
    {
        return working_frequency;
    }

    inline uint32_t get_wireless_data_rate(void)
    {
        return wireless_data_rate;
    }

    inline uint16_t get_receiving_bandwidth(void)
    {
        return receiving_bandwidth;
    }

    inline uint8_t get_frequency_deviation(void)
    {
        return frequency_deviation;
    }

    inline uint8_t get_transmission_power(void)
    {
        return transmission_power;
    }

    inline uint32_t get_uart_transfer_speed(void)
    {
        return uart_transfer_speed;
    }
};

#endif // ifndef __CM_HMTRP_INLUDED__
