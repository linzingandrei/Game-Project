#include "raylib.h"
#include <iostream>
#include "FastNoiseLite.h"
#include <vector>
#include "Player.hpp"

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




int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");

    Player player;

    Camera2D camera;
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.target = player.GetPlayerPosition();

    lightTexture = LoadTexture("assets/grass-light.png");
    darkTexture = LoadTexture("assets/grass-dark.png");
    waterTexture = LoadTexture("assets/water.png");
    mountainTexture = LoadTexture("assets/mountain.png");

    init();
    processing();


    Rectangle srcRect = { 0, 0, (float)lightTexture.width, (float)lightTexture.height };


    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            BeginMode2D(camera);
            ClearBackground(RAYWHITE);
            camera.target = player.GetPlayerPosition();

            int cellSize = 128;
            for (int y = 0; y < 128; y++) {
                for (int x = 0; x < 128; x++) {
                    int index = y * 128 + x;
                    Texture2D texture = textureData[index]; 

                    Rectangle destRect = {(float)(x * cellSize), (float)(y * cellSize), (float)cellSize, (float)cellSize};

                    DrawTexturePro(texture, srcRect, destRect, {0, 0}, 0, WHITE);
                }
            }

            player.UpdatePlayerFrame();
            EndMode2D();
        EndDrawing();
    }

    return 0;
}