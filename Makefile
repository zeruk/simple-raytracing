CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TEST_SRCS = $(TEST_DIR)/test_main.cpp
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Executable names
TARGET = $(BIN_DIR)/raytracer
TEST_TARGET = $(BIN_DIR)/test_raytracer

# Run
run: $(TARGET)
	./$(TARGET)

# Test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Rule to build the main program
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files from source files in src
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build tests
$(TEST_TARGET): $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to build object files from source files in tests
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
