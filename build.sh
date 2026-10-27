#!/bin/bash

set -e

gcc -Wall -Wextra main.c ./src/load-image.c ./src/start-screen.c ./src/load-menu.c -o main $(pkg-config --cflags --libs sdl3) -lSDL3_ttf -lm
