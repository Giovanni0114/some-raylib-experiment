#!/bin/sh

CFLAGS="-O3 -Wall -Wextra -I. `pkg-config --cflags raylib`"
LIBS="-lm `pkg-config --libs raylib` -ldl -lglfw -lpthread"

clang $CFLAGS -o main main.c $LIBS
