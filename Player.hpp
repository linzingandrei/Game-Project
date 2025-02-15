#include "raylib.h"

class Player {
private:
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

    Vector2 playerPosition = {(128 * 128) / 2.0f, (128 * 128) / 2.0f};
    float playerSpeed = 250.0f;

    Texture2D playerTextures = LoadTexture("assets/player.png");

public:
    void UpdatePlayerFrame(void);
    Vector2 GetPlayerPosition();
};