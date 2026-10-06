#!/bin/bash

set -e

gcc -Wall -Wextra main.c -o main $(pkg-config --cflags --libs sdl3) -lm
