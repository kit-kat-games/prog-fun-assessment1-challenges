/*
    Assessment 1 - Challenge 10
    Task: Bitwise Controller Input Manipulation

*/

#include <iostream>
#include <vector>
#include <string>
#include "structures.h"
#include "methods.h"

const int BITFIELD_LENGTH = 16;
const std::vector<uint16_t> playerBits = { PLAYER_BIT_PLAYER_ONE, PLAYER_BIT_PLAYER_TWO, PLAYER_BIT_PLAYER_THREE, PLAYER_BIT_PLAYER_FOUR };
const std::map<uint16_t, int> playerBitIndexMap = {
    { PLAYER_BIT_PLAYER_ONE, 1 },
    { PLAYER_BIT_PLAYER_TWO, 2 },
    { PLAYER_BIT_PLAYER_THREE, 3 },
    { PLAYER_BIT_PLAYER_FOUR, 4 },
};

enum Error {
    ERROR_NO_PLAYER_BITS_FLIPPED,
    ERROR_MULTIPLE_PLAYER_BITS_FLIPPED,
    ERROR_FAILED_CIN,
    ERROR_EMPTY_INPUT,
    ERROR_INVALID_BITFIELD_CHARS,
    ERROR_INVALID_BITFIELD_LENGTH,
};

void handleError(const Error e) {
    switch (e) {
    case ERROR_NO_PLAYER_BITS_FLIPPED:
        std::cerr << "[!] ERROR: No player bits set in bitfield. Controller input data should have exactly 1 player bit set." << std::endl;
        break;
    case ERROR_MULTIPLE_PLAYER_BITS_FLIPPED:
        std::cerr << "[!] ERROR: Multiple player bits set in bitfield. Controller input data should have exactly 1 player bit set." << std::endl;
        break;
    case ERROR_FAILED_CIN:
        std::cerr << "[!] ERROR: Input failed." << std::endl;
        break;
    case ERROR_EMPTY_INPUT:
        std::cerr << "[!] ERROR: Input is empty." << std::endl;
        break;
    case ERROR_INVALID_BITFIELD_CHARS:
        std::cerr << "[!] ERROR: Invalid chars in bitfield." << std::endl;
        break;
    case ERROR_INVALID_BITFIELD_LENGTH:
        std::cerr << "[!] ERROR: Invalid length of bitfield." << std::endl;
        break;
    }
}

int decideTransformation(const uint16_t bitfield) {
    int transformation = 0;

    for (uint16_t playerBit : playerBits) {
        if ((bitfield | playerBit) == bitfield) {
            if (transformation == 0) { transformation = playerBitIndexMap.at(playerBit); }
            else { throw ERROR_MULTIPLE_PLAYER_BITS_FLIPPED; }
        }
    }

    if (transformation == 0) { throw ERROR_NO_PLAYER_BITS_FLIPPED; }

    return transformation;
}

bool checkBitfieldValid(const uint16_t bitfield) {
    bool onePlayerBitFlipped = false;
    for (uint16_t playerBit : playerBits) {
        if ((bitfield | playerBit) == bitfield) {
            if (onePlayerBitFlipped) {
                throw ERROR_MULTIPLE_PLAYER_BITS_FLIPPED;
            }
            else {
                onePlayerBitFlipped = true;
            }
        }
    }
    if (!onePlayerBitFlipped) {
        throw ERROR_NO_PLAYER_BITS_FLIPPED;
    }
}

uint16_t convertStringToBitfield(std::string bitfieldString) {
    uint16_t bitfield = 0b0;
    for (int i = 0; i < bitfieldString.length(); i++) {
        char c = bitfieldString[i];
        if (c != '0' && c != '1') {
            throw ERROR_INVALID_BITFIELD_CHARS;
        }
        if (c == '1') {
            bitfield |= 0b1 << (bitfieldString.length() - 1 - i);
        }
    }
    return bitfield;
}

uint16_t inputBinaryNumber() {
    std::string input = "";
    std::string whitespaceStrippedInput = "";
    uint16_t bitfield = 0b0;
    while (true) {
        getline(std::cin, input);
        if (std::cin.fail()) { throw ERROR_FAILED_CIN; }
        if (input == "") { throw ERROR_EMPTY_INPUT; }
        for (char c : input) {
            if (!isspace(c) && c != '0' && c != '1') { throw ERROR_INVALID_BITFIELD_CHARS; }
            if (!isspace(c)) { whitespaceStrippedInput += c; }
        }
        if (whitespaceStrippedInput.length() == 0) { throw ERROR_EMPTY_INPUT; }
        if (whitespaceStrippedInput.length() != BITFIELD_LENGTH) { throw ERROR_INVALID_BITFIELD_LENGTH; }

        try {
            bitfield = convertStringToBitfield(whitespaceStrippedInput);
            return bitfield;
        }
        catch (const Error e) { handleError(e); }
    }
}

uint16_t getUserInput() {
    while (true) {
        try {
            std::cout << ">> Please input a 16 digit binary number: ";
            uint16_t bitfield = inputBinaryNumber();
            if (checkBitfieldValid(bitfield)) {
                return bitfield;
            }
        }
        catch (const Error e) { handleError(e); }
    }
}

uint16_t player2Transformation(uint16_t bitfield) {
    // DOWN-RIGHT-UP-LEFT -> Clockwise would be RIGHT-UP-LEFT-DOWN -> Left Shift 1, grabbing Down bit and appplying to where Left currently is
    uint16_t dpadBits = bitfield & DATA_MASK_DPAD;
    uint16_t bitfieldWithoutDpadBits = bitfield & ~DATA_MASK_DPAD;

    bool dpadDownSet = (bitfield | DATA_BIT_DPAD_DOWN) == bitfield;
    dpadBits = dpadBits << 1;
    dpadBits = SetBitAtPosition(dpadBits, bitIndexMap.at(DATA_BIT_DPAD_LEFT), dpadDownSet);
    dpadBits &= DATA_MASK_DPAD;

    bitfield = bitfieldWithoutDpadBits | dpadBits;

    return bitfield;
}

uint16_t player3Transformation(uint16_t bitfield) {
    // DOWN-RIGHT-UP-LEFT -> Counter Clockwise would be LEFT-DOWN-RIGHT-UP -> Right Shift 1, grabbing Left bit and appplying to where Down currently is
    uint16_t dpadBits = bitfield & DATA_MASK_DPAD;
    uint16_t bitfieldWithoutDpadBits = bitfield & ~DATA_MASK_DPAD;

    bool dpaLeftSet = (bitfield | DATA_BIT_DPAD_LEFT) == bitfield;
    dpadBits = dpadBits >> 1;
    dpadBits = SetBitAtPosition(dpadBits, bitIndexMap.at(DATA_BIT_DPAD_DOWN), dpaLeftSet);
    dpadBits &= DATA_MASK_DPAD;

    bitfield = bitfieldWithoutDpadBits | dpadBits;

    // Invert all bits in shoulderBits range
    uint16_t shoulderBits = bitfield & DATA_MASK_SHOULDER;
    uint16_t bitfieldWithoutShoulderBits = bitfield & ~DATA_MASK_SHOULDER;

    uint16_t shoulderBitsInverted = ~shoulderBits;
    shoulderBitsInverted &= DATA_MASK_SHOULDER;

    bitfield = bitfieldWithoutShoulderBits | shoulderBitsInverted;

    return bitfield;
}

uint16_t swapBits(uint16_t bitfield, int bitIndexA, int bitIndexB) {
    bool bitASet = SetBitAtPosition(bitfield, bitIndexA, true) == bitfield;
    bool bitBSet = SetBitAtPosition(bitfield, bitIndexB, true) == bitfield;
    bitfield = SetBitAtPosition(bitfield, bitIndexA, bitBSet);
    bitfield = SetBitAtPosition(bitfield, bitIndexB, bitASet);
    return bitfield;
}

uint16_t player4Transformation(uint16_t bitfield) {
    // Invert all bits in shoulderBits range
    uint16_t shoulderBits = bitfield & DATA_MASK_SHOULDER;
    uint16_t bitfieldWithoutShoulderBits = bitfield & ~DATA_MASK_SHOULDER;

    uint16_t shoulderBitsInverted = ~shoulderBits;
    shoulderBitsInverted &= DATA_MASK_SHOULDER;

    bitfield = bitfieldWithoutShoulderBits | shoulderBitsInverted;
    PrintBitfield(bitfield);
    // Swap the following : DPad Right <-> DPad Left, DPad Up <-> DPad Down, Button A <-> Button B, Button X <-> Button Y
    bitfield = swapBits(bitfield, bitIndexMap.at(DATA_BIT_DPAD_RIGHT), bitIndexMap.at(DATA_BIT_DPAD_LEFT));
    bitfield = swapBits(bitfield, bitIndexMap.at(DATA_BIT_DPAD_UP), bitIndexMap.at(DATA_BIT_DPAD_DOWN));
    bitfield = swapBits(bitfield, bitIndexMap.at(DATA_BIT_BUTTON_A), bitIndexMap.at(DATA_BIT_BUTTON_B));
    bitfield = swapBits(bitfield, bitIndexMap.at(DATA_BIT_BUTTON_X), bitIndexMap.at(DATA_BIT_BUTTON_Y));
    return bitfield;
}

uint16_t doTransformation(const uint16_t bitfield) {
    switch (decideTransformation(bitfield)) {
    case 1:
        return bitfield;
    case 2:
        return player2Transformation(bitfield);
    case 3:
        return player3Transformation(bitfield);
    case 4:
        return player4Transformation(bitfield);
    }
}

int main(int argc, char* argv[])
{
    uint16_t bitfield = getUserInput();
    uint16_t transformedBitfield = doTransformation(bitfield);
    PrintBitfield(transformedBitfield);
}