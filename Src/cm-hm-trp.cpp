#include "cm-hm-trp.hpp"

#define HMTP_BAUDRATE_ARRAY { 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200 }

HMTRP::HMTRP(
  UART_HandleTypeDef *huart,
  uint32_t            baudrate,
  uint8_t             transmission_power,
  uint16_t            receiving_bandwidth,
  uint8_t             frequency_deviation
) : UART(huart)
{
    this->working_frequency   = 0;
    this->wireless_data_rate  = 0;
    this->receiving_bandwidth = 0;
    this->frequency_deviation = 0;
    this->transmission_power  = 0;
    this->uart_transfer_speed = 0;

    config(false);
    enable(false);
    HAL_Delay(10);
    enable(true);
    HAL_Delay(10);
    config(true);

    while (not read_config())
    {
        for (uint32_t bd : HMTP_BAUDRATE_ARRAY)
        {
            set_baudrate(bd);
            if (read_config())
            {
                break;
            }
        }
    }

    if (this->wireless_data_rate != baudrate)
    {
        // global->usb->tx("config wireless_data_rate\n");
        while (not set_wireless_data_rate(baudrate))
            ;
    }

    if (this->uart_transfer_speed != baudrate)
    {
        // global->usb->tx("config uart_transfer_speed\n");
        while (not set_uart_transfer_speed(baudrate))
            ;
    }

    if (this->receiving_bandwidth != receiving_bandwidth)
    {
        // global->usb->tx("config receiving_bandwidth\n");
        while (not set_receiving_bandwidth(receiving_bandwidth))
            ;
    }

    if (this->frequency_deviation != frequency_deviation)
    {
        // global->usb->tx("config frequency_deviation\n");
        while (not set_frequency_deviation(frequency_deviation))
            ;
    }

    if (this->transmission_power != transmission_power)
    {
        // global->usb->tx("config transmission_power\n");
        while (not set_transmission_power(transmission_power))
            ;
    }

    read_config();
    config(false);
    rx_it();
}

void HMTRP::cmd(vector<uint8_t> vector_bytes)
{
    tx(vector_uint8_t_array(0xAA, 0xFA));
    tx(vector_bytes);
}

bool HMTRP::check_ok(void)
{
    uint8_t buffer[4];
    rx(buffer, 4, 500);
    if (buffer[0] == 'O' and buffer[1] == 'K' and buffer[2] == '\r' and buffer[3] == '\n')
    {
        return true;
    }
    return false;
}

bool HMTRP::check_data_rate(uint32_t baudrate)
{
    for (uint32_t bd : HMTP_BAUDRATE_ARRAY)
        if (baudrate == bd)
            return true;

    return false;
}

bool HMTRP::read_config(void)
{
    uint8_t buffer[16];

    vector<uint8_t> conf;
    conf.push_back(0xE1);

    cmd(conf);
    if (rx(buffer, 16, 500) != HAL_OK)
    {
        return false;
    }

    this->working_frequency  = uint32_t(buffer[0]) << 24;
    this->working_frequency += uint32_t(buffer[1]) << 16;
    this->working_frequency += uint32_t(buffer[2]) << 8;
    this->working_frequency += uint32_t(buffer[3]);

    this->wireless_data_rate  = uint32_t(buffer[4]) << 24;
    this->wireless_data_rate += uint32_t(buffer[5]) << 16;
    this->wireless_data_rate += uint32_t(buffer[6]) << 8;
    this->wireless_data_rate += uint32_t(buffer[7]);

    this->receiving_bandwidth  = uint16_t(buffer[8]) << 8;
    this->receiving_bandwidth += uint16_t(buffer[9]);

    this->frequency_deviation = buffer[10];

    this->transmission_power = buffer[11];

    this->uart_transfer_speed  = uint32_t(buffer[12]) << 24;
    this->uart_transfer_speed += uint32_t(buffer[13]) << 16;
    this->uart_transfer_speed += uint32_t(buffer[14]) << 8;
    this->uart_transfer_speed += uint32_t(buffer[15]);

    if (this->working_frequency != 869000000)
    {
        return false;
    }

    return true;
} // read_config

bool HMTRP::reset_to_default(void)
{
    vector<uint8_t> conf;
    conf.push_back(0xF0);
    cmd(conf);
    set_baudrate(9600);
    return check_ok();
}

bool HMTRP::set_wireless_data_rate(uint32_t baudrate) // bps
{
    if (check_data_rate(baudrate))
    {
        vector<uint8_t> conf;
        conf.push_back(0xC3);
        conf.push_back(uint8_t((baudrate >> 24) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 16) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 8) & 0xFF));
        conf.push_back(uint8_t(baudrate & 0xFF));
        cmd(conf);
        return check_ok();
    }
    return false;
}

bool HMTRP::set_uart_transfer_speed(uint32_t baudrate) // bps
{
    if (check_data_rate(baudrate))
    {
        vector<uint8_t> conf;
        conf.push_back(0x1E);
        conf.push_back(uint8_t((baudrate >> 24) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 16) & 0xFF));
        conf.push_back(uint8_t((baudrate >> 8) & 0xFF));
        conf.push_back(uint8_t(baudrate & 0xFF));
        cmd(conf);
        set_baudrate(baudrate);
        return check_ok();
    }
    return false;
}

bool HMTRP::set_receiving_bandwidth(uint16_t receiving_bandwidth) // kHz
{
    if (receiving_bandwidth > 620 or receiving_bandwidth < 30)
    {
        return false;
    }

    vector<uint8_t> conf;
    conf.push_back(0xB4);
    conf.push_back(uint8_t((receiving_bandwidth >> 8) & 0xFF));
    conf.push_back(uint8_t(receiving_bandwidth & 0xFF));
    cmd(conf);
    return check_ok();
}

bool HMTRP::set_frequency_deviation(uint8_t frequency_deviation) // kHz
{
    if (frequency_deviation > 160 or frequency_deviation < 10)
    {
        return false;
    }

    vector<uint8_t> conf;
    conf.push_back(0xA5);
    conf.push_back(frequency_deviation);
    cmd(conf);
    return check_ok();
}

bool HMTRP::set_transmission_power(uint8_t transmission_power) // level
{
    /* transmission_power [level] -> [dbm]
     *                      0     ->   1
     *                      1     ->   2
     *                      2     ->   5
     *                      3     ->   8
     *                      4     ->   11
     *                      5     ->   14
     *                      6     ->   17
     *                      7     ->   20
     */

    if (transmission_power > 7)
    {
        return false;
    }

    vector<uint8_t> conf;
    conf.push_back(0x96);
    conf.push_back(transmission_power);
    cmd(conf);
    return check_ok();
}

void HMTRP::print_config(void)
{
    // global->usb->tx("\nCONFIG:");
    // global->usb->tx("\nworking_frequency: " + to_string(working_frequency));
    // global->usb->tx("\nwireless_data_rate: " + to_string(wireless_data_rate));
    // global->usb->tx("\nreceiving_bandwidth: " + to_string(receiving_bandwidth));
    // global->usb->tx("\nfrequency_deviation: " + to_string(frequency_deviation));
    // global->usb->tx("\ntransmission_power: " + to_string(transmission_power));
    // global->usb->tx("\nuart_transfer_speed: " + to_string(uart_transfer_speed) + '\n');
}
