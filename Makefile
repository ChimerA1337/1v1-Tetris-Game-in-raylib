CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm -lpthread -lenet

# Detect OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lGL -ldl -lrt -lX11
    TARGET = tetorisu
endif

ifeq ($(UNAME_S),Darwin)
    # macOS
    LDFLAGS += -framework Cocoa -framework OpenGL
    TARGET = tetorisu
endif

ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    TARGET = tetorisu.exe
endif

# Find all .c files in source/ and add main.c
SOURCES = main.c $(wildcard source/*.c)
INCLUDES = -Iinclude

# Default target
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) -lraylib

clean:
	rm -f $(TARGET) $(TARGET).exe *.o

.PHONY: all clean