#!/bin/bash

gcc main.c \
    source/*.c \
    -Iinclude \
    -o tetorisu-linux \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lenet
