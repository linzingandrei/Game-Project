#include "Player.hpp"

void Player::UpdatePlayerFrame() {
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

    if (flip == true) {
        source.width = -1 * source.width;
    }

    DrawTexturePro(playerTextures, source, dest, (Vector2){0, 0}, 0, WHITE);
}

Vector2 Player::GetPlayerPosition() {
    return this->playerPosition;
}