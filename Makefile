CC=clang
CFLAGS=-O3 -Wall -Wextra -I. $(shell pkg-config --cflags raylib)
LDFLAGS=-lm $(shell pkg-config --libs raylib) -ldl -lglfw -lpthread

SOURCES=main.c drawing.c game.c menu.c music.c
OBJECTS=$(SOURCES:%.c=build/%.o)
BUILD_DIR=build
EXECUTABLE=$(BUILD_DIR)/mygame

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

.PHONY clean all
