#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"
#include "structs.c"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

// Load all the textures from sprite folder
void LoadAllTextures()
{
    // Players sprites
    textures[TEXTURE_PLAYER_IDLE] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_RIGHT] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_LEFT] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_UP] = LoadTexture("sprites/HunterWithGun.png");
    textures[TEXTURE_PLAYER_RUNNING_DOWN] = LoadTexture("sprites/HunterWithGun.png");

    // Animal sprites
    textures[TEXTURE_ANIMAL_TURKEY] = LoadTexture("sprites/Turkey.png");
    textures[TEXTURE_ANIMAL_BIGHORNSHEEP] = LoadTexture("sprites/BigHornSheep.png");
    textures[TEXTURE_ANIMAL_PRONGHORN] = LoadTexture("sprites/Pronghorn.png");
    textures[TEXTURE_ANIMAL_BLACKBEAR] = LoadTexture("sprites/Blackbear.png");
    textures[TEXTURE_ANIMAL_ROCKYMOUNTAINELK] = LoadTexture("sprites/RockyMountainElk.png");
    textures[TEXTURE_ANIMAL_MOUNTAINLION] = LoadTexture("sprites/Mountainlion.png");

    // Tile sprites
    textures[TEXTURE_TILE_GRASS] = LoadTexture("sprites/GrassTile.png");
    textures[TEXTURE_TILE_GRASS2] = LoadTexture("sprites/GrassTile2.png");
}

// Generate world
void GenerateWorld() {
    for (int i = 0; i < WORLD_SIZE; i++) {
        for (int j = 0; j < WORLD_SIZE; j++) {
            world[i][j].rect = (Rectangle){i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            world[i][j].tileType = GetRandomValue(0, 1);
        }
    }
}

// Render world
void RenderWorld() {
    for (int i = 0; i < RENDER_SIZE; i++) {
        for (int j = 0; j < RENDER_SIZE; j++) {
            if ((i * TILE_SIZE) > SCREEN_WIDTH || (j * TILE_SIZE) > SCREEN_HEIGHT) {
                continue; // Skip rendering if outside the screen
            }
            Rectangle tileRect = world[i][j].rect;
            if (world[i][j].tileType == 0) {
                DrawTexture(textures[TEXTURE_TILE_GRASS], tileRect.x, tileRect.y, WHITE);
            } else {
                DrawTexture(textures[TEXTURE_TILE_GRASS2], tileRect.x, tileRect.y, WHITE);
            }
        }
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Procedural Generation");
    SetTargetFPS(60);  // Sets the framerate
    LoadAllTextures(); // Load texture
    GenerateWorld();

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
        .rect = (Rectangle){SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 16, 32},
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

        // Hidden collision
        if (player.rect.x > 785)
        {
            player.rect.x -= 10.0f;
        }
        else if (player.rect.x < 100)
        {
            player.rect.x += 10.0f;
        }
        if (player.rect.y > 568)
        {
            player.rect.y -= 10.0f;
        }
        else if (player.rect.y < 100)
        {
            player.rect.y += 10.0f;
        }

        //----------------------------------------------------
        // Draw
        //----------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        RenderWorld();

        // Draw black blocks around render view
        DrawRectangle(0, 0, 100, 700, BLACK);
        DrawRectangle(0, 0, 900, 100, BLACK); 
        DrawRectangle(800, 0, 100, 700, BLACK); 
        DrawRectangle(0, 600, 900, 100, BLACK); 

        // Draw player
        DrawTexturePro(textures[player.animations[player.current_animation].texture_id], (Rectangle){32 * player.animations[player.current_animation].current_frame, 0, 16, 32}, player.rect, Vector2Zero(), 0, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
