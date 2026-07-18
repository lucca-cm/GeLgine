CXX := clang++

CXXFLAGS := -std=c++17 -Wall -Wextra \
-Iinclude -I/opt/homebrew/include

LDFLAGS := -L/opt/homebrew/lib \
-lglfw -framework OpenGL

SRC_CPP := $(shell find src -name '*.cc')
SRC_C := $(shell find src -name '*.c')

OBJ := $(SRC_CPP:src/%.cc=build/%.o) \
       $(SRC_C:src/%.c=build/%.o)

TARGET := app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	clang -std=c11 -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean