#include "raylib.h"
#include "FastNoiseLite.h"
#include <vector>

FastNoiseLite noise;

void init() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
}

std::vector<float> noiseData(128 * 128);
int indexx = 0;

void processing() {
    for (int y = 0; y < 128; y++) {
        for (int x = 0; x < 128; x++) {
            noiseData[indexx++] = noise.GetNoise((float)x, (float)y);
        }
    }
}


int main() {
    InitWindow(1800, 1000, "Game");

    init();
    processing();

    Texture2D lightTexture = LoadTexture("grass-light.png");
    Texture2D darkTexture = LoadTexture("grass-dark.png");

    Rectangle srcRect = { 0, 0, (float)lightTexture.width, (float)lightTexture.height };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int cellSize = 128;
        for (int y = 0; y < 128; y++) {
            for (int x = 0; x < 128; x++) {
                int index = y * 128 + x;
                Texture2D texture = ((x + y) % 2 == 0) ? darkTexture : lightTexture;

                Rectangle destRect = {(float)(x * cellSize), (float)(y * cellSize), (float)cellSize, (float)cellSize};

                DrawTexturePro(texture, srcRect, destRect, {0, 0}, 0, WHITE);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}