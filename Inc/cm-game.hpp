#ifndef __CM_GAME_INCLUDED__
#define __CM_GAME_INCLUDED__

#include "cm-sound.hpp"
#include <vector>
#include <string>

using namespace std;

typedef enum game_mode_t {
    GAME_MODE_SOLO,
    GAME_MODE_TEAM,
} game_mode_t;

typedef enum button_action_mode_t {
    BUTTON_ACTION_MODE_DISABLE,
    BUTTON_ACTION_MODE_FUSE,
    BUTTON_ACTION_MODE_WHITE_FLASHLIGHT,
    BUTTON_ACTION_MODE_ULTRA_VIOLET_FLASHLIGHT,
} button_action_mode_t;

class BaseGame
{
private:
    string name;
    game_mode_t game_mode;
    button_action_mode_t button_action_mode;
    sound_set_t sound_set_type;
    uint32_t game_duration;
    uint32_t death_duration;
    uint32_t batch_shots_count;
    bool enable_sound;
    bool enable_vest_light;
    bool enable_immorality;
public:
    inline BaseGame(void)
    { }
};

#endif // ifndef __CM_GAME_INCLUDED__
