#include "raylib.h"
#include "raymath.h"

#define MAX_TEXTURES_IN_MEMORY 128
#define MAX_ANIMATIONS_PER_ENTITY 6
#define MAX_ANIMATIONS_PER_OBJECT 1
#define TILE_SIZE 32
#define WORLD_SIZE 175
#define RENDER_SIZE 25

Texture2D textures[MAX_TEXTURES_IN_MEMORY];

typedef struct {
    int tileType;
    Rectangle rect;
} Tile;

Tile world[WORLD_SIZE][WORLD_SIZE]; // 2D array to hold the world's tiles

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
    TEXTURE_TILE_GRASS,
    TEXTURE_TILE_GRASS2,
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
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_ENTITY];
    int current_animation;
} Hunter;

typedef struct
{
    Rectangle rect;
    Animation animations[MAX_ANIMATIONS_PER_ENTITY];
    int current_animation;
} Animal;
