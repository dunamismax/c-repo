# Makefile for the c-repo monorepo
#
# This Makefile explicitly defines build rules for each application
# to ensure reliability.

# --- Configuration ---
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -g -O2
LDFLAGS :=

# --- Project Layout ---
BIN_DIR := bin
SRC_DIR := apps

# --- Application Definitions ---
APPS := calculator contact-book file-analyzer tiny-server
TARGETS := $(patsubst %,$(BIN_DIR)/%,$(APPS))

# --- Core Rules ---
.PHONY: all
all: $(TARGETS)
	@echo "\n\033[1;32mAll applications built successfully in '$(BIN_DIR)' directory.\033[0m"

# --- Explicit Application Build Rules ---

$(BIN_DIR)/calculator: $(SRC_DIR)/calculator/src/calculator.c
	@echo "[CC] Compiling calculator..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

$(BIN_DIR)/contact-book: $(SRC_DIR)/contact-book/src/contact-book.c
	@echo "[CC] Compiling contact-book..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

$(BIN_DIR)/file-analyzer: $(SRC_DIR)/file-analyzer/src/file-analyzer.c
	@echo "[CC] Compiling file-analyzer..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

$(BIN_DIR)/tiny-server: $(SRC_DIR)/tiny-server/src/tiny-server.c
	@echo "[CC] Compiling tiny-server..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -pthread $(LDFLAGS) -o $@ $<

# --- Utility Rules ---

.PHONY: clean
clean:
	@echo "[CLEAN] Removing build artifacts..."
	@rm -rf $(BIN_DIR)

.PHONY: help
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all       Build all applications (default)."
	@echo "  clean     Remove all built files."
	@echo "  help      Show this help message."
	@echo ""
	@echo "Available applications to build individually:"
	@$(foreach app,$(APPS),echo "  - make $(app)";)

# --- Individual Application Targets ---
.PHONY: $(APPS)
$(foreach app,$(APPS),$(eval $(app): $(BIN_DIR)/$(app)))