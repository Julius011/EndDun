#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"
#include "structs.c"

#define MAP_WIDTH 512
#define MAP_HEIGHT 512
#define TILE_SIZE 32

int worldMap[MAP_WIDTH][MAP_HEIGHT];

// Load all the textures from sprite folder
void LoadAllTextures()
{
    // Players sprites
    textures[TEXTURE_PLAYER_IDLE] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_RIGHT] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_LEFT] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_UP] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_DOWN] = LoadTexture("sprites/HunterWithGun.png");

    // Animalsprites
    textures[TEXTURE_ANIMAL_TURKEY] = LoadTexture("sprites/Turkey.png");
    textures[TEXTURE_ANIMAL_BIGHORNSHEEP] = LoadTexture("sprites/BigHornSheep.png");
    textures[TEXTURE_ANIMAL_PRONGHORN] = LoadTexture("sprites/Pronghorn.png");
    textures[TEXTURE_ANIMAL_BLACKBEAR] = LoadTexture("sprites/Blackbear.png");
    textures[TEXTURE_ANIMAL_ROCKYMOUNTAINELK] = LoadTexture("sprites/RockyMountainElk.png");
    textures[TEXTURE_ANIMAL_MOUNTAINLION] = LoadTexture("sprites/Mountainlion.png");
}

void GenerateTerrain()
{
    // Initialize the random number generator with a seed
    srand(GetTime());

    // Fill the worldMap with random heights
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            worldMap[x][y] = GetRandomValue(0, 255);
        }
    }
}

int main()
{
    InitWindow(800, 600, "Procedural Generation");
    SetTargetFPS(60);  // Sets the framerate
    LoadAllTextures(); // Call the "LoadAllTextures" function
    GenerateTerrain(); // 

    // Player initialise
    Hunter player = (Hunter){
        .animations = {
            (Animation){
                .texture_id = TEXTURE_PLAYER_IDLE,
                .current_frame = 0,
                .max_frame = 1,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation){
                .texture_id = TEXTURE_PLAYER_RUNNING_RIGHT,
                .current_frame = 0,
                .max_frame = 1,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation){
                .texture_id = TEXTURE_PLAYER_RUNNING_LEFT,
                .current_frame = 0,
                .max_frame = 1,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation){
                .texture_id = TEXTURE_PLAYER_RUNNING_UP,
                .current_frame = 0,
                .max_frame = 1,
                .frame_duration = 0.1f,
                .timer = 0,
            },
            (Animation){
                .texture_id = TEXTURE_PLAYER_RUNNING_DOWN,
                .current_frame = 0,
                .max_frame = 1,
                .frame_duration = 0.1f,
                .timer = 0,
            }},
        .rect = (Rectangle){800 / 2, 600 / 2, 16, 32},
        .velocity = 0,
        .current_animation = 0};

    while (!WindowShouldClose())
    {
        //----------------------------------------------------
        // Update
        //----------------------------------------------------

        // Update necessary animation:
        {
            // Player
            Animation *player_animation = &player.animations[player.current_animation];
            player_animation->timer += GetFrameTime();
            if (player_animation->timer >= player_animation->frame_duration)
            {
                player_animation->current_frame++;
                if (player_animation->current_frame > player_animation->max_frame)
                {
                    player_animation->current_frame = 0;
                }
                player_animation->timer = 0.0f;
            };
        }

        // Player move input
        if (IsKeyDown(KEY_RIGHT))
        {
            player.rect.x += 10.0f;
            player.current_animation = 1; // Set animation to running right
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            player.rect.x -= 10.0f;
            player.current_animation = 2; // Set animation to running left
        }
        else if (IsKeyDown(KEY_UP))
        {
            player.rect.y -= 10.0f;
            player.current_animation = 3; // Set animation to running up
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            player.rect.y += 10.0f;
            player.current_animation = 4; // Set animation to running down
        }

        //----------------------------------------------------
        // Draw
        //----------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        // Render the terrain
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                // Calculate the position for this tile
                int posX = x * TILE_SIZE;
                int posY = y * TILE_SIZE;

                // Map the height value to a grayscale color
                Color color = (Color){worldMap[x][y], worldMap[x][y], worldMap[x][y], 255};

                // Draw a rectangle as a terrain tile
                DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, color);
            }
        }

        // Draw player
        DrawTexturePro(textures[player.animations[player.current_animation].texture_id], (Rectangle){32 * player.animations[player.current_animation].current_frame, 0, 16, 32}, player.rect, Vector2Zero(), 0, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}