CC=clang
CFLAGS=-O3 -Wall -Wextra -Iinclude -I. $(shell pkg-config --cflags raylib)
LDFLAGS=-lm $(shell pkg-config --libs raylib) -ldl -lglfw -lpthread

BUILD_DIR=build

FILES=main.c drawing.c game.c menu.c music.c
SOURCES=$(FILES:%.c=src/%.c)
OBJECTS=$(FILES:%.c=$(BUILD_DIR)/%.o)

EXECUTABLE=$(BUILD_DIR)/mygame

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	ln -s $(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean all
