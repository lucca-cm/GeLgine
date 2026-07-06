CXX := clang++

CXXFLAGS := -std=c++17 -Wall -Wextra \
-Iinclude -I/opt/homebrew/include

LDFLAGS := -L/opt/homebrew/lib \
-lglfw -framework OpenGL

SRC_CPP := $(wildcard src/*.cc)
SRC_C := $(wildcard src/*.c)

OBJ := $(patsubst src/%.cc,build/%.o,$(SRC_CPP)) \
       $(patsubst src/%.c,build/%.o,$(SRC_C))

TARGET := app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.cc
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.c
	@mkdir -p build
	clang -std=c11 -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean