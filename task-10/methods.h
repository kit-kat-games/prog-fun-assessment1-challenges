#pragma once
#include <iostream>
#include <map>
#include "structures.h"

const uint16_t PLAYER_BIT_PLAYER_FOUR = 0b1 << 15;
const uint16_t PLAYER_BIT_PLAYER_THREE = 0b1 << 14;
const uint16_t PLAYER_BIT_PLAYER_TWO = 0b1 << 13;
const uint16_t PLAYER_BIT_PLAYER_ONE = 0b1 << 12;
const uint16_t DATA_BIT_SHOULDER_R2 = 0b1 << 11;
const uint16_t DATA_BIT_SHOULDER_R1 = 0b1 << 10;
const uint16_t DATA_BIT_SHOULDER_L2 = 0b1 << 9;
const uint16_t DATA_BIT_SHOULDER_L1 = 0b1 << 8;
const uint16_t DATA_BIT_BUTTON_Y = 0b1 << 7;
const uint16_t DATA_BIT_BUTTON_X = 0b1 << 6;
const uint16_t DATA_BIT_BUTTON_B = 0b1 << 5;
const uint16_t DATA_BIT_BUTTON_A = 0b1 << 4;
const uint16_t DATA_BIT_DPAD_DOWN = 0b1 << 3;
const uint16_t DATA_BIT_DPAD_RIGHT = 0b1 << 2;
const uint16_t DATA_BIT_DPAD_UP = 0b1 << 1;
const uint16_t DATA_BIT_DPAD_LEFT = 0b1 << 0;

const std::map<uint16_t, int> bitIndexMap = {
    { PLAYER_BIT_PLAYER_FOUR, 15 },
    { PLAYER_BIT_PLAYER_THREE, 14 },
    { PLAYER_BIT_PLAYER_TWO, 13 },
    { PLAYER_BIT_PLAYER_ONE, 12 },
    { DATA_BIT_SHOULDER_R2, 11 },
    { DATA_BIT_SHOULDER_R1, 10 },
    { DATA_BIT_SHOULDER_L2, 9 },
    { DATA_BIT_SHOULDER_L1, 8 },
    { DATA_BIT_BUTTON_Y, 7 },
    { DATA_BIT_BUTTON_X, 6 },
    { DATA_BIT_BUTTON_B, 5 },
    { DATA_BIT_BUTTON_A, 4 },
    { DATA_BIT_DPAD_DOWN, 3 },
    { DATA_BIT_DPAD_RIGHT, 2 },
    { DATA_BIT_DPAD_UP, 1 },
    { DATA_BIT_DPAD_LEFT, 0 },
};

const uint16_t DATA_MASK_SHOULDER = 0b1111 << 8;
const uint16_t DATA_MASK_BUTTON = 0b1111 << 4;
const uint16_t DATA_MASK_DPAD = 0b1111 << 0;

// Forward Declarations
PlayerInput BitfieldToPlayerInput(const uint16_t input);
uint16_t SetBitAtPosition(const uint16_t input, int index, bool value);

void PrintInputData(const uint16_t input)
{
    PlayerInput playerInput = BitfieldToPlayerInput(input);

    //std::cout << std::boolalpha;
    std::cout << "Player #" << playerInput.playerIndex << std::endl;
    std::cout << "Button States:" << std::endl;
    std::cout << "- L1: " << playerInput.shoulderButtons.L1Pressed << std::endl;
    std::cout << "- L2: " << playerInput.shoulderButtons.L2Pressed << std::endl;
    std::cout << "- R1: " << playerInput.shoulderButtons.R1Pressed << std::endl;
    std::cout << "- R2: " << playerInput.shoulderButtons.R2Pressed << std::endl;
    std::cout << "- A: " << playerInput.buttons.APressed << std::endl;
    std::cout << "- B: " << playerInput.buttons.BPressed << std::endl;
    std::cout << "- X: " << playerInput.buttons.XPressed << std::endl;
    std::cout << "- Y: " << playerInput.buttons.YPressed << std::endl;
    std::cout << "- Left: " << playerInput.dpad.leftPressed << std::endl;
    std::cout << "- Right: " << playerInput.dpad.rightPressed << std::endl;
    std::cout << "- Up: " << playerInput.dpad.upPressed << std::endl;
    std::cout << "- Down: " << playerInput.dpad.downPressed << std::endl;
    //std::cout << std::noboolalpha;
}

void PrintBitfield(const uint16_t input)
{
    for (int i = 15; i >= 0; i--) {
        if (SetBitAtPosition(input, i, true) == input) {
            std::cout << "1";
        }
        else {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
}

uint16_t SetBitAtPosition(const uint16_t input, int index, bool value)
{
    if (value == true) {
        return input | (0b1 << index);
    }
    else {
        return input & (~(0b1 << index));
    }
}

//---------

uint16_t SetData(const uint16_t input, const uint16_t data)
{
    return input & data;
}

uint16_t SetPlayers(const uint16_t input, const uint16_t players)
{
    return input & (players << 12);
}

uint16_t GetPlayers(const uint16_t input)
{
    return input & (0b1111 << 12);
}

uint16_t GetData(const uint16_t input)
{
    return input & (~(0b1111 << 12));
}

//---------

uint16_t PlayerInputToBitfield(const PlayerInput& input)
{
    uint16_t result = 0b0;
    switch (input.playerIndex) {
    case 1:
        result |= PLAYER_BIT_PLAYER_ONE;
        break;
    case 2:
        result |= PLAYER_BIT_PLAYER_TWO;
        break;
    case 3:
        result |= PLAYER_BIT_PLAYER_THREE;
        break;
    case 4:
        result |= PLAYER_BIT_PLAYER_FOUR;
        break;
    }

    if (input.shoulderButtons.L1Pressed) {
        result |= DATA_BIT_SHOULDER_L1;
    }
    if (input.shoulderButtons.L2Pressed) {
        result |= DATA_BIT_SHOULDER_L2;
    }
    if (input.shoulderButtons.R1Pressed) {
        result |= DATA_BIT_SHOULDER_R1;
    }
    if (input.shoulderButtons.R2Pressed) {
        result |= DATA_BIT_SHOULDER_R2;
    }
    if (input.buttons.APressed) {
        result |= DATA_BIT_BUTTON_A;
    }
    if (input.buttons.BPressed) {
        result |= DATA_BIT_BUTTON_B;
    }
    if (input.buttons.XPressed) {
        result |= DATA_BIT_BUTTON_X;
    }
    if (input.buttons.YPressed) {
        result |= DATA_BIT_BUTTON_Y;
    }
    if (input.dpad.leftPressed) {
        result |= DATA_BIT_DPAD_LEFT;
    }
    if (input.dpad.rightPressed) {
        result |= DATA_BIT_DPAD_RIGHT;
    }
    if (input.dpad.upPressed) {
        result |= DATA_BIT_DPAD_UP;
    }
    if (input.dpad.downPressed) {
        result |= DATA_BIT_DPAD_DOWN;
    }
    
    // Apply Transformation ???

    return result;
}

PlayerInput BitfieldToPlayerInput(const uint16_t input)
{
    int playerIndex = 0;
    if ((input | PLAYER_BIT_PLAYER_ONE) == input) {
        playerIndex = 1;
    }
    else if ((input | PLAYER_BIT_PLAYER_TWO) == input) {
        playerIndex = 2;
    }
    else if ((input | PLAYER_BIT_PLAYER_THREE) == input) {
        playerIndex = 3;
    }
    else if ((input | PLAYER_BIT_PLAYER_FOUR) == input) {
        playerIndex = 4;
    }

    ShoulderButtonState shoulderButtons = ShoulderButtonState(
        (input | DATA_BIT_SHOULDER_L1) == input,
        (input | DATA_BIT_SHOULDER_L2) == input,
        (input | DATA_BIT_SHOULDER_R1) == input,
        (input | DATA_BIT_SHOULDER_R2) == input
    );  
    ButtonState buttons = ButtonState(
        (input | DATA_BIT_BUTTON_A) == input,
        (input | DATA_BIT_BUTTON_B) == input,
        (input | DATA_BIT_BUTTON_X) == input,
        (input | DATA_BIT_BUTTON_Y) == input
    );
    DPadState dpad = DPadState(
        (input | DATA_BIT_DPAD_LEFT) == input,
        (input | DATA_BIT_DPAD_RIGHT) == input,
        (input | DATA_BIT_DPAD_UP) == input,
        (input | DATA_BIT_DPAD_DOWN) == input
    );

    return PlayerInput(playerIndex, shoulderButtons, buttons, dpad);
}

