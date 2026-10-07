#!/bin/bash

set -e

gcc -Wall -Wextra main.c load-image.c start-screen.c -o main $(pkg-config --cflags --libs sdl3) -lSDL3_ttf -lm
