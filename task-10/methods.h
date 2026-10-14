#pragma once
#include "structures.h"

void PrintInputData(const uint16_t input)
{
    //..
}

void PrintBitfield(const uint16_t input)
{
    //...
}

uint16_t SetBitAtPosition(const uint16_t input, int index, bool value)
{
    //...
    return 0;
}

//---------

uint16_t SetData(const uint16_t input, const uint16_t data)
{
    //...
    return 0;
}

uint16_t SetPlayers(const uint16_t input, const uint16_t players)
{
    //...
    return 0;
}

uint16_t GetPlayers(const uint16_t input)
{
    //...
    return 0;
}

uint16_t GetData(const uint16_t input)
{
    //...
    return 0;
}

//---------

uint16_t PlayerInputToBitfield(const PlayerInput& input)
{
    //...
    return 0;
}

PlayerInput BitfieldToPlayerInput(const uint16_t input)
{
    //...
    return PlayerInput { };
}

