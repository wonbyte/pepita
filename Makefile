# Variables
BUILD_DIR := build
DOCS_DIR := docs
PEPITA := $(BUILD_DIR)/pepita
TESTS := $(BUILD_DIR)/Testing
CMAKE := cmake
BUILD_TYPE := Debug
SOURCES := $(wildcard src/*.c) $(wildcard include/*.h)

.DEFAULT_GOAL := all
.PHONY: all clean coverage docs format rebuild run test distclean

# Default target that builds the project
all: $(PEPITA)

# Build the executable using Ninja
$(PEPITA): $(BUILD_DIR)/build.ninja $(SOURCES)
	@$(CMAKE) --build $(BUILD_DIR) --config $(BUILD_TYPE)

# Generate the build.ninja file using CMake
$(BUILD_DIR)/build.ninja: CMakeLists.txt
	@$(CMAKE) -S . -B $(BUILD_DIR) -GNinja -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean all build files and directories
clean:
	@if [ -d $(BUILD_DIR) ]; then \
		$(CMAKE) --build $(BUILD_DIR) --target clean; \
	fi
	@$(RM) -r $(TESTS)
	@$(RM) -r $(DOCS_DIR)

# Complete cleanup
distclean:
	@$(RM) -r $(BUILD_DIR)

# Build the project and generate code coverage
coverage:
	@$(CMAKE) --build $(BUILD_DIR) --target coverage

# Generate documentation by running Doxygen after cleaning the documentation directory
docs:
	@doxygen Doxyfile

# Format the source code using clang-format
format:
	@find src include test -name '*.c' -o -name '*.h' -exec clang-format -i {} +

# Clean all build files and directories, then build the project
rebuild: clean all

# Build and run the executable
run: all
	@$(PEPITA)

# Build and run the tests
test: distclean all
	@$(CMAKE) --build $(BUILD_DIR) --target test
