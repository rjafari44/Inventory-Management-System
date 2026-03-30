.PHONY: all clean

GCC         := g++
GCC_VERSION := -std=c++17
SRC_DIR     := ./src
SRC         := $(wildcard $(SRC_DIR)/*.cpp)
EXEC        := test

all:
	$(GCC) $(GCC_VERSION) -Iinclude $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC)
