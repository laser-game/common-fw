#ifndef __CM_GUN_INCLUDED__
#define __CM_GUN_INCLUDED__


typedef enum gun_cmd_t {
    GUN_CMD_SET_CONGIG,
    GUN_CMD_GET_CONFIG,
    GUN_CMD_DISABLE_SHOT,
    GUN_CMD_ENABLE_SHOT,
    GUN_CMD_SHOT,
} gun_cmd_t;


// každej cmd má 1 vector_byte
// dopsat cmnd tak, aby přenášená konfigurace byla větší...


#endif // ifndef __CM_GUN_INCLUDED__
