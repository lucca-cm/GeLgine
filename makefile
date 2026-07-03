CXX := clang++
#CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Linux
# LDFLAGS := -lGLEW -lglfw -lGL

# macOS
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib -lGLEW -lglfw -framework OpenGL

SRC := $(wildcard src/*.cc)
OBJ := $(patsubst src/%.cc,build/%.o,$(SRC))

TARGET := app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.cc
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean