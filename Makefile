#### PROJECT SETTINGS ####
# Executable name
OUTPUT = example
# Compiler used
#CXX = gcc
CXX = clang
# Compiler specific flags
#CXXFLAGS = -std=gnu99 -Wall -Wextra -Werror -Wfloat-equal -Wundef -Wshadow \
#           -Wstrict-prototypes -Wformat=2 -pedantic
CXXFLAGS = -Wall -Wextra -Werror -Wfloat-equal -Wformat=2 -Wshadow -pedantic
# Linker specific flags
LDFLAGS =
# Extension of source files used in the project
SRC_EXT = c
# Path to the source directory, relative to the makefile
SRC_PATH = .
# Path to the include directory, relative to the makefile
INC_PATH = ./include
# Path to the template definition directory, relative to the makefile
DEF_PATH = ./defs
# Path to the libs directory, relative to the makefile
LIB_PATH =
# Path to the tests directory, relative to the makefile
TEST_PATH = ./tests
# External library files
LIBS = $(wildcard $(LIB_PATH)/*.[oa])
# Add additional include paths
INCLUDES = -I$(INC_PATH)/ -I$(LIB_PATH)/ -I$(DEF_PATH)/
#### END PROJECT SETTINGS ####

# Generally should not need to edit below this line

# Shell used in this makefile
# bash is used for 'echo -en'
SHELL = /bin/bash
# Clear built-in rules
.SUFFIXES:

# Verbose option, to output compile and link commands
export V := false
export CMD_PREFIX := @
ifeq ($(V),true)
	CMD_PREFIX :=
endif

# Build and output paths
example: export SYSTEM_PATH := example
example: export BUILD_PATH := build/$(SYSTEM_PATH)
example: export BIN_PATH := bin/$(SYSTEM_PATH)
example: export BIN_NAME := $(OUTPUT)

# Find all source files in the source directory, sorted by most
# recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)')

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
DEPS = $(OBJECTS:.o=.d)

# Macros for timing compilation
TIME_FILE = $(dir $@).$(notdir $@)_time
START_TIME = date '+%s' > $(TIME_FILE)
END_TIME = read st < $(TIME_FILE) ; \
	$(RM) $(TIME_FILE) ; \
	st=$$((`date '+%s'` - $$st - 86400)) ; \
	echo `date -u -d @$$st '+%H:%M:%S'`

# Standard, non-optimized release build
.PHONY: example
example: dirs
	@echo "Beginning $@ build"
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)

# Create the directories used in the build
.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

# Removes all build files
.PHONY: clean
clean:
	@echo "Deleting symlinks"
	@$(RM) $(OUTPUT)
	@echo "Deleting directories"
	@$(RM) -r build
	@$(RM) -r bin

# Main rule, checks the executable and symlinks to the output
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Link the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CXX) $(OBJECTS) $(LIBS) $(LDFLAGS) -o $@
	@echo -en "\t Link time: "
	@$(END_TIME)

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)
