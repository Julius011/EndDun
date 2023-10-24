#include "raylib.h"
#include "raymath.h"

#define MAX_TEXTURES_IN_MEMORY 128
#define MAX_ANIMATIONS_PER_ENTITY 6
#define MAX_ANIMATIONS_PER_OBJECT 1

Texture2D textures[MAX_TEXTURES_IN_MEMORY];

typedef enum  
{
    TEXTURE_PLAYER_IDLE,
    TEXTURE_PLAYER_RUNNING_RIGHT,
    TEXTURE_PLAYER_RUNNING_LEFT,
    TEXTURE_PLAYER_RUNNING_UP,
    TEXTURE_PLAYER_RUNNING_DOWN,
    TEXTURE_ANIMAL_TURKEY,
    TEXTURE_ANIMAL_BIGHORNSHEEP,
    TEXTURE_ANIMAL_PRONGHORN,
    TEXTURE_ANIMAL_BLACKBEAR,
    TEXTURE_ANIMAL_ROCKYMOUNTAINELK,
    TEXTURE_ANIMAL_MOUNTAINLION,
    TEXTURE_NUM
} textures_e;

typedef struct
{
    textures_e texture_id;
    int current_frame;
    int max_frame;
    float frame_duration;
    float timer;
} Animation;

typedef struct
{
    float velocity;
    float soundLevel;
    int ammunition;
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_ENTITY];
    int current_animation;
} Hunter;

typedef struct
{
    float velocity;
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_ENTITY];
    int current_animation;
} Animal;