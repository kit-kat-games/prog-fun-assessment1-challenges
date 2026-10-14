#pragma once

typedef struct ShoulderButtonState
{
    bool L1Pressed;
    bool L2Pressed;
    bool R1Pressed;
    bool R2Pressed;
} ShoulderButtonState;

//----

typedef struct ButtonState
{
    bool APressed;
    bool BPressed;
    bool XPressed;
    bool YPressed;
} ButtonState;

//----

typedef struct DPadState
{
    bool leftPressed;
    bool rightPressed;
    bool upPressed;
    bool downPressed;
} DPadState;

//----

typedef struct PlayerInput
{
    int playerIndex;

    ShoulderButtonState shoulderButtons;
    ButtonState buttons;
    DPadState dpad;
    
} PlayerInput;
