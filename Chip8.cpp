#include "Chip8.h"

const unsigned int FONTSET_START_ADDRESS = 0x50;

Chip8::Chip8() : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
    programCounter = START_ADDRESS;

    for (unsigned int i = 0; i < FONTSET_SIZE; ++i)
    {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

void Chip8::LoadROM(char const* filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        for (long i = 0; i < size; ++i)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }
        delete[] buffer;
    }
}


void Chip8::OP_00E0()
{
    memset(video, 0, sizeof(video));
}

void Chip8::OP_00EE()
{
    --stackPointer;
    programCounter = stack[stackPointer];
}

void Chip8::OP_1NNN()
{
    uint16_t address = opcode & 0x0FFFu;

    programCounter = address;
}

void Chip8::OP_2NNN()
{
    uint16_t address = opcode & 0x0FFFu;

    stack[stackPointer] = programCounter;
    ++stackPointer;
}