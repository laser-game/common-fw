#ifndef __CM_COLOR_INCLUDED__
#define __CM_COLOR_INCLUDED__

#include <vector>
#include <string>

using namespace std;

class RGB
{
private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
public:
    inline RGB(uint8_t r, uint8_t g, uint8_t b)
    {
        red = r;
        green = g;
        blue = b;
    }

    inline RGB(void)
    {
        red = 0;
        green = 0;
        blue = 0;
    }

    inline uint8_t get_red(void)
    {
        return red;
    }

    inline uint8_t get_green(void)
    {
        return green;
    }

    inline uint8_t get_blue(void)
    {
        return blue;
    }

    inline void set_red(uint8_t r)
    {
        red = r;
    }

    inline void set_green(uint8_t g)
    {
        green = g;
    }

    inline void set_blue(uint8_t b)
    {
        blue = b;
    }

    inline void set_rgb(uint8_t r, uint8_t g, uint8_t b)
    {
        red = r;
        green = g;
        blue = b;
    }
};

#endif // ifndef __CM_COLOR_INCLUDED__
