#include "raylib.h"
#include <iostream>
#include "FastNoiseLite.h"
#include <vector>

using namespace std;

FastNoiseLite noise;

void init() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    noise.SetFrequency(0.05f);
}

vector<float> noiseData(128 * 128);
int indexx = 0;

vector<Texture2D> textureData(128 * 128);
Texture2D lightTexture;
Texture2D darkTexture;
Texture2D waterTexture;
Texture2D mountainTexture;

void processing() {
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            float noiseValue = noise.GetNoise((float)x, (float)y);
            noiseData[indexx] = noiseValue;

            float normalizedValue = (noiseValue + 1.0f) / 2.0f;

            if (normalizedValue < 0.3f) {
                textureData[indexx] = waterTexture;
            } 
            else if (normalizedValue < 0.4f) {
                textureData[indexx] = lightTexture;
            }
            else if (normalizedValue < 0.7f) {
                textureData[indexx] = lightTexture;
            }
            else if (normalizedValue < 0.9) {
                textureData[indexx] = darkTexture;
            }
            else {
                textureData[indexx] = mountainTexture;
            }

            indexx += 1;
        }
    }
}

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 1100

#define PLAYER_IDLE_COUNT 6
#define PLAYER_IDLE_TIME 0.15 
int playerIdleIndex = 0;
float playerIdleTimer = PLAYER_IDLE_TIME;

#define PLAYER_RIGHT_COUNT 6
#define PLAYER_RIGHT_TIME 0.15 
int playerRightIndex = 0;
float playerRightTimer = PLAYER_RIGHT_TIME;

#define PLAYER_LEFT_COUNT 6
#define PLAYER_LEFT_TIME 0.15 
int playerLeftIndex = 0;
float playerLeftTimer = PLAYER_LEFT_TIME;

#define PLAYER_UP_COUNT 6
#define PLAYER_UP_TIME 0.15 
int playerUpIndex = 0;
float playerUpTimer = PLAYER_UP_TIME;

#define PLAYER_DOWN_COUNT 6
#define PLAYER_DOWN_TIME 0.15 
int playerDownIndex = 0;
float playerDownTimer = PLAYER_DOWN_TIME;

Texture2D atlas;

void UpdatePlayerFrame(void);

Vector2 playerPosition = {(128 * 128) / 2.0f, (128 * 128) / 2.0f};
float playerSpeed = 250.0f;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");

    // Camera2D camera;
    // camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    // camera.rotation = 0.0f;
    // camera.zoom = 1.0f;
    // camera.target = playerPosition;

    lightTexture = LoadTexture("assets/grass-light.png");
    darkTexture = LoadTexture("assets/grass-dark.png");
    waterTexture = LoadTexture("assets/water.png");
    mountainTexture = LoadTexture("assets/mountain.png");

    init();
    processing();


    Rectangle srcRect = { 0, 0, (float)lightTexture.width, (float)lightTexture.height };

    atlas = LoadTexture("assets/player.png");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            // BeginMode2D(camera);
            ClearBackground(RAYWHITE);
            // camera.target = playerPosition;

            int cellSize = 4;
            for (int y = 0; y < 128; y++) {
                for (int x = 0; x < 128; x++) {
                    int index = y * 128 + x;
                    Texture2D texture = textureData[index]; 

                    Rectangle destRect = {(float)(x * cellSize), (float)(y * cellSize), (float)cellSize, (float)cellSize};

                    DrawTexturePro(texture, srcRect, destRect, {0, 0}, 0, WHITE);
                }
            }

            UpdatePlayerFrame();
            // EndMode2D();
        EndDrawing();
    }

    return 0;
}


void UpdatePlayerFrame(void) {
    Rectangle source;
    Vector2 playerDrawOffset = { (48 * 5) / 2.0f, (48 * 5) / 2.0f };
    Rectangle dest = { playerPosition.x - playerDrawOffset.x, playerPosition.y - playerDrawOffset.y, 48 * 5, 48 * 5 };

    bool flip = false;

    float deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_W)) {
        source = (Rectangle){(float)playerUpIndex * 48, 48 * 5, 48, 48};
        playerPosition.y -= playerSpeed * deltaTime;

        playerUpTimer -= deltaTime;
        if (playerUpTimer < 0) {
            playerUpTimer = PLAYER_UP_TIME;

            playerUpIndex += 1;
            if (playerUpIndex >= PLAYER_UP_COUNT) {
                playerUpIndex = 0;
            }
        }
    } 
    else if (IsKeyDown(KEY_A)) {
        source = (Rectangle){(float)playerRightIndex * 48, 48 * 4, 48, 48};
        playerPosition.x -= playerSpeed * deltaTime;

        playerRightTimer -= deltaTime;
        if (playerRightTimer < 0) {
            playerRightTimer = PLAYER_RIGHT_TIME;

            playerRightIndex += 1;
            if (playerRightIndex >= PLAYER_RIGHT_COUNT) {
                playerRightIndex = 0;
            }
        }

        flip = true;
    }
    else if (IsKeyDown(KEY_D)) {
        source = (Rectangle){(float)playerRightIndex * 48, 48 * 4, 48, 48};
        playerPosition.x += playerSpeed * deltaTime;

        playerRightTimer -= deltaTime;
        if (playerRightTimer < 0) {
            playerRightTimer = PLAYER_RIGHT_TIME;

            playerRightIndex += 1;
            if (playerRightIndex >= PLAYER_RIGHT_COUNT) {
                playerRightIndex = 0;
            }
        }
    }
    else if (IsKeyDown(KEY_S)) {
        source = (Rectangle){(float)playerDownIndex * 48, 48 * 3, 48, 48};
        playerPosition.y += playerSpeed * deltaTime;

        playerDownTimer -= deltaTime;
        if (playerDownTimer < 0) {
            playerDownTimer = PLAYER_DOWN_TIME;

            playerDownIndex += 1;
            if (playerDownIndex >= PLAYER_DOWN_COUNT) {
                playerDownIndex = 0;
            }
        }
    }
    else {
        source = (Rectangle){(float)playerIdleIndex * 48, 0, 48, 48};

        playerIdleTimer -= deltaTime;
        if (playerIdleTimer < 0) {
            playerIdleTimer = PLAYER_IDLE_TIME;

            playerIdleIndex += 1;
            if (playerIdleIndex >= PLAYER_IDLE_COUNT) {
                playerIdleIndex = 0;
            }
        }
    }

    // BeginDrawing();

    //     ClearBackground(RAYWHITE);

        if (flip == true) {
            source.width = -1 * source.width;
        }

        DrawTexturePro(atlas, source, dest, (Vector2){0, 0}, 0, WHITE);

    // EndDrawing();
}