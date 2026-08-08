#!/bin/bash

gcc main.c \
    source/*.c \
    -Iinclude \
    -o run \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lenet
