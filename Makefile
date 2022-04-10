SRC_FILES = $(wildcard *.cpp)
LD_FLAGS  = -lpthread -lSDL2
CXX_FLAGS = -Ofast -march=native -std=c++11

.PHONY: main
main: $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) $(LD_FLAGS) -o main $(SRC_FILES)