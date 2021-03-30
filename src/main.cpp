#include <chrono>
#include <iostream>
#include "Chip8.h"
#include "Platform.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage:" << argv[0] << " <Scale> <Delay> <ROM>\n";
        std::exit(EXIT_FAILURE);
    } 

    int videoToScale = std::stoi(argv[1]);
    int cycleDelay = std::stoi(argv[2]);

    const char* romFileName = argv[3];

    Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoToScale, VIDEO_HEIGHT * videoToScale, VIDEO_WIDTH, VIDEO_HEIGHT);

    Chip8 chip8;
    chip8.LoadROM(romFileName);

    int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = platform.ProcessInput(chip8.keypad);

        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (deltaTime > cycleDelay)
        {
            lastCycleTime = currentTime;

            chip8.Cycle();

            platform.Update(chip8.video, videoPitch);
        }
    }

    return 0;
}

