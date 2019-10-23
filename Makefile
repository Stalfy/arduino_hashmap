# Directories.
SRC_DIR   = src
TEST_DIR  = test
RELEASE_DIR  = HashMap

BUILD_DIR = build
SRC_BUILD_DIR = $(BUILD_DIR)/$(SRC_DIR)
TEST_BUILD_DIR = $(BUILD_DIR)/$(TEST_DIR)

# Compiler.
CC++ = g++

# Flags.
C_FLAGS = -Wall -fPIC -m64 -O3 -std=c++14
L_FLAGS = -Wall -fPIC -m64

# Catch test framework specific.
CATCH_SINGLE_INCLUDE = $(TEST_DIR)/
CATCH_FLAGS          = --reporter compact --success

# Sources.
SRC = $(wildcard $(SRC_DIR)/*.cpp)

TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(SRC_BUILD_DIR)/%.o,$(SRC)) \
           $(patsubst $(TEST_DIR)/%.cpp,$(TEST_BUILD_DIR)/%.o,$(TEST_SRC))

# Macros.
RM 		= rm -r
MKDIR_P = mkdir -p

# Executables.
TEST_EXE = catchmain

release:
	cp $(SRC_DIR)/hashmap.cpp $(RELEASE_DIR)/hashmap.cpp
	cp $(SRC_DIR)/hashmap.hpp $(RELEASE_DIR)/hashmap.hpp
	sed -i '/^\#define HASHMAP_HPP_/a \\n\#include \"Arduino.h\"' $(RELEASE_DIR)/hashmap.hpp
	zip $(RELEASE_DIR).zip $(RELEASE_DIR)/*

test: $(TEST_EXE)
	./$(TEST_EXE) $(CATCH_FLAGS)

clean:
	$(RM) $(BUILD_DIR)

$(TEST_EXE): $(TEST_OBJ)
	$(CC++) $(L_FLAGS) -I $(CATCH_SINGLE_INCLUDE) -o $(TEST_EXE) $^

$(SRC_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CC++) $(C_FLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CC++) $(C_FLAGS) -I $(SRC_DIR) -c $< -o $@
