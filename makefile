CXX ?= g++

INCLUDE_DIR := include
TEST_DIR := tests
BUILD_ROOT := build
MODE ?= release

STD := -std=c++23
WARNFLAGS := \
  -pedantic-errors \
  -Wall -Wextra -Wpedantic \
  -Wshadow \
  -Wformat=2 \
  -Wfloat-equal \
  -Wlogical-op \
  -Wshift-overflow=2 \
  -Wnon-virtual-dtor \
  -Wold-style-cast \
  -Wcast-qual \
  -Wuseless-cast \
  -Wno-sign-promotion \
  -Wcast-align \
  -Wunused \
  -Woverloaded-virtual \
  -Wconversion \
  -Wmisleading-indentation \
  -Wduplicated-cond \
  -Wduplicated-branches \
  -Wnull-dereference \
  -Wno-conversion \
  -Wformat-overflow \
  -Wformat-truncation \
  -Wdouble-promotion \
  -Wundef

BASEDEFS := -DLOCAL
INCLUDES := -I$(INCLUDE_DIR)

RELFLAGS := -O2 -DNDEBUG
DBGFLAGS := \
  -O0 -g3 \
  -fsanitize=address,undefined \
  -fsanitize=float-divide-by-zero \
  -fsanitize=float-cast-overflow \
  -fno-sanitize-recover=all \
  -fstack-protector-all \
  -fstack-usage \
  -fno-omit-frame-pointer \
  -fno-inline \
  -ffunction-sections \
  -D_GLIBCXX_DEBUG \
  -D_GLIBCXX_DEBUG_PEDANTIC

DBG_LDFLAGS := \
  -fsanitize=address,undefined \
  -fsanitize=float-divide-by-zero \
  -fsanitize=float-cast-overflow

CXXFLAGS := $(STD) $(WARNFLAGS) $(INCLUDES) $(BASEDEFS)
ifeq ($(MODE),debug)
  CXXFLAGS += $(DBGFLAGS)
  LDFLAGS += $(DBG_LDFLAGS)
else
  CXXFLAGS += $(RELFLAGS)
endif

BUILD_DIR := $(BUILD_ROOT)/$(MODE)
TEST_SRC := $(wildcard $(TEST_DIR)/*.cc)
TEST_OBJ := $(patsubst $(TEST_DIR)/%.cc,$(BUILD_DIR)/$(TEST_DIR)/%.o,$(TEST_SRC))
TEST_EXE := $(BUILD_DIR)/test_bmath

.PHONY: all release debug test clean distclean flags .TEST

all: release

release:
	$(MAKE) MODE=release .TEST

debug:
	$(MAKE) MODE=debug .TEST

test: .TEST

.TEST: $(TEST_EXE)
	./$(TEST_EXE)

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_EXE): $(TEST_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

flags:
	@{ \
	  printf "%s\n%s\n%s\n" $(STD) $(INCLUDES) $(WARNFLAGS) $(BASEDEFS) \
	  [ "$(MODE)" = "debug" ] && printf "%s\n" $(DBGFLAGS) || printf "%s\n" $(RELFLAGS) \
	} > compile_flags.txt

clean:
	@rm -rf "$(BUILD_DIR)"

distclean:
	@rm -rf "$(BUILD_ROOT)" compile_flags.txt

