BUILD = build
CMAKE = cmake
MAKE = make
TARGET = main

all: run

init:
	@mkdir -p $(BUILD)
	@$(CMAKE) . -B $(BUILD)

build:
	@cd $(BUILD) && $(MAKE)
.PHONY: build

run: build
	@./$(BUILD)/src/$(TARGET)

clean:
	@cd $(BUILD) && $(MAKE) clean

