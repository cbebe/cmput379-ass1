# https://r4nd0m6uy.ch/the-quest-to-the-perfect-makefile.html

PROJECT             = shell379
BUILD_DIR           ?= build

# Application sources and artifacts
APP_BIN             = $(PROJECT)
APP_SOURCES         = src/ProcessTable.cpp \
											src/Process.cpp \
											src/InputParser.cpp
APP_MAIN            = src/main.cpp
APP_OBJS            = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(APP_SOURCES) $(APP_MAIN))

# Generated dependency files
DEPS                = $(APP_OBJS:.o=.d)

# Compiler options
COMMON_CFLAGS       = -Wall -Wextra -MMD

# Debug/Release mode
ifneq ($(DEBUG),)
  COMMON_CFLAGS     += -g
  BUILD_DIR         := $(BUILD_DIR)/debug
else
  COMMON_CFLAGS     += -DNDEBUG -O3
  BUILD_DIR         := $(BUILD_DIR)/release
endif

CFLAGS              += $(COMMON_CFLAGS)
CXXFLAGS            += $(COMMON_CFLAGS) -std=c++14

# Silence make
ifneq ($(V),)
  SILENCE           =
else
  SILENCE           = @
endif

# Fancy output
SHOW_COMMAND        := @printf "%-15s%s\n"
SHOW_CXX            := $(SHOW_COMMAND) "[ $(CXX) ]"
SHOW_CLEAN          := $(SHOW_COMMAND) "[ CLEAN ]"
SHOW_GEN            := $(SHOW_COMMAND) "[ GEN ]"

##############################################################################################
# Default target and help message
##############################################################################################
DEFAULT_TARGET =  $(APP_BIN)

all: $(DEFAULT_TARGET) runner sleeper forker
.PHONY: all

# Take care of compiler generated depedencies
-include $(DEPS)

runner: $(BUILD_DIR)/runner.o
	$(SHOW_CXX) $@
	$(SILENCE) $(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/runner.o: src/runner.cpp
	$(SHOW_CXX) $@
	$(SILENCE)$(CXX) $(CXXFLAGS) -c $< -o $@

sleeper: $(BUILD_DIR)/sleeper.o
	$(SHOW_CXX) $@
	$(SILENCE) $(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/sleeper.o: src/sleeper.cpp
	$(SHOW_CXX) $@
	$(SILENCE)$(CXX) $(CXXFLAGS) -c $< -o $@

forker: $(BUILD_DIR)/forker.o
	$(SHOW_CXX) $@
	$(SILENCE) $(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/forker.o: src/forker.cpp
	$(SHOW_CXX) $@
	$(SILENCE)$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(APP_BIN)

##############################################################################################
# Application
##############################################################################################
$(APP_BIN): $(APP_OBJS)
	$(SHOW_CXX) $@
	$(SILENCE)$(CXX) -o $@ $(APP_OBJS)

$(BUILD_DIR)/%.o: %.cpp
	$(SHOW_CXX) $@
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CXX) $(CXXFLAGS) -c $< -o $@

##############################################################################################
# Cleanup
##############################################################################################
clean:
	$(SHOW_CLEAN) $(BUILD_DIR)
	$(SILENCE)rm -rf $(BUILD_DIR) 
	$(SHOW_CLEAN) $(APP_BIN) 
	$(SILENCE)rm $(APP_BIN) 
	$(SHOW_CLEAN) runner 
	$(SILENCE)rm runner
	$(SHOW_CLEAN) sleeper
	$(SILENCE)rm sleeper
	$(SHOW_CLEAN) forker
	$(SILENCE)rm forker
.PHONY: clean
