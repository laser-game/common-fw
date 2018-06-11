#ifndef __CM_PLAYER_INCLUDED__
#define __CM_PLAYER_INCLUDED__

#include <vector>
#include <string>

#include "cm-rgb.hpp"

using namespace std;

class BasicPlayer
{
private:
    bool alive;
    string player_name;
    uint8_t player_team;
    uint8_t vest_address;
    uint32_t points;
    uint32_t shots_count;
    uint32_t kills_count;
    uint32_t deaths_count;
    uint32_t friendly_kills_count;
public:
    RGB color;

    inline BasicPlayer()
    {
        alive = false;
        player_name = "";
        player_team = 0;
        vest_address = 0; //TODO pointer na vestu
        points = 0;
        shots_count = 0;
        kills_count = 0;
        deaths_count = 0;
        friendly_kills_count = 0;
    }

    inline void set_name(string name)
    {
        this->player_name = name;
    }

    inline string get_name(void)
    {
        return player_name;
    }

    inline void set_points(uint32_t points)
    {
        this->points = points;
    }

    inline uint32_t get_points(void)
    {
        return points;
    }

    inline void set_shots_count(uint32_t shots_count)
    {
        this->shots_count = shots_count;
    }

    inline uint32_t get_shots_count(void)
    {
        return shots_count;
    }

    inline void set_kills_count(uint32_t kills_count)
    {
        this->kills_count = kills_count;
    }

    inline uint32_t get_kills_count(void)
    {
        return kills_count;
    }

    inline void set_deaths_count(uint32_t deaths_count)
    {
        this->deaths_count = deaths_count;
    }

    inline uint32_t get_deaths_count(void)
    {
        return deaths_count;
    }

    inline void set_friendly_kills_count(uint32_t friendly_kills_count)
    {
        this->friendly_kills_count = friendly_kills_count;
    }

    inline uint32_t get_friendly_kills_count(void)
    {
        return friendly_kills_count;
    }

    inline bool is_alive(void)
    {
        return this->alive;
    }

    inline void death(void)
    {
        this->alive = false;
        this->deaths_count++;
    }

    inline void live(void)
    {
        this->alive = true;
    }
};

#endif // ifndef __CM_PLAYER_INCLUDED__
