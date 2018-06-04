#ifndef __CM_VEST_INCLUDED__
#define __CM_VEST_INCLUDED__

#include <vector>
#include <string>

using namespace std;

class BasicVest
{
private:
    uint8_t address;
    uint8_t battery;
    bool enable;
    bool online;
    bool has_failure;
public:
    inline BasicVest()
    {
        address = 0;
        battery = 0;
        enable = false;
        online = false;
        has_failure = false;
    }

    inline void set_address(uint32_t address)
    {
        this->address = address;
    }

    inline uint8_t get_address(void) const
    {
        return address;
    }

    inline void set_battery(uint32_t battery)
    {
        this->battery = battery;
    }

    inline uint8_t get_battery(void) const
    {
        return battery;
    }

    inline void set_enable(bool enable)
    {
        this->enable = enable;
    }

    inline bool get_enable(void) const
    {
        return enable;
    }

    inline void set_online(bool online)
    {
        this->online = online;
    }

    inline bool get_online(void) const
    {
        return online;
    }

    inline void set_failure(bool failure)
    {
        this->has_failure = failure;
    }

    inline bool get_failure(void) const
    {
        return has_failure;
    }
};

#endif // ifndef __CM_VEST_INCLUDED__
