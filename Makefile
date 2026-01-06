# =========================
# Configurazione progetto
# =========================

PROJECT   := mylib
CC        := gcc
CFLAGS    := -Wall -Wextra -Wpedantic -O2
INCLUDES  := -Iinclude
LIBS      := $(shell pkg-config --libs libxml-2.0)
CFLAGS   += $(shell pkg-config --cflags libxml-2.0)

SRC_DIR   := ./
BUILD_DIR := _build
DOCS_DIR  := docs

SRCS      := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET    := $(BUILD_DIR)/$(PROJECT)

# =========================
# Target principali
# =========================

.PHONY: all build run docs clean clean-docs

all: build

# Build binario
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# =========================
# Run
# =========================

run: build
	./$(TARGET)

# =========================
# Documentazione (Doxygen)
# =========================

docs:
	doxygen Doxyfile

clean-docs:
	rm -rf $(DOCS_DIR)

# =========================
# Pulizia
# =========================

clean:
	rm -rf $(BUILD_DIR) $(DOCS_DIR)

