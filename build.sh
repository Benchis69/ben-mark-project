#!/bin/bash

set -e

gcc -Wall -Wextra main.c load-image.c -o main $(pkg-config --cflags --libs sdl3) -lm
