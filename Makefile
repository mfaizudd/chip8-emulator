build:
	g++ main.cpp Chip8.cpp Platform.cpp -o builds/chip8 `sdl2-config --cflags --libs`

clean:
	rm builds/chip8