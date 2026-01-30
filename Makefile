CC := clang
FLAGS := -std=c23 -Wall -Wextra -Werror -Wpedantic
BUILD_LOC := build
SRC_LOC := src
INCLUDE_LOC := include
TEST_LOC := test
BIN_LOC := bin
EXEC := vm

OBJ_FILES := $(BUILD_LOC)/instruction.o

# 1st 4 vals should be 8-bit base-16 values, 5th same value as 32-bit value arranged in little-endian
TEST_VALS1 := 4a 51 01 9f 9f01514a
# 1st some base-10 int between 1 and 31, version of last 32-bit val shifted left by 32 - 1st val and sign-extended
TEST_VALS2 := 12 fffff9f0
# Uses 1st val as base, checks for opcode, rd, funct3, rs1, rs2, and funct7
TEST_VALS3 := 4a 2 5 2 10 4f
# Uses 1st val as base, check for imm vals for i, s, b, u, j
TEST_VALS4 := fffff9f0 fffff9e2 fffff1e2 9F015000 fff151f0

all: $(BIN_LOC)/$(EXEC)

$(BIN_LOC)/$(EXEC): vm_main.c $(OBJ_FILES)
	$(CC) $(FLAGS) $^ -o $@

test_inst: $(BUILD_LOC)/instruction.o $(BUILD_LOC)/test_inst.o
	$(CC) $(FLAGS) $^ -o $(BIN_LOC)/$@
	./$(BIN_LOC)/$@ $(TEST_VALS1) $(TEST_VALS2) $(TEST_VALS3) $(TEST_VALS4)

$(BUILD_LOC)/%.o: $(SRC_LOC)/%.c
	$(CC) $(FLAGS) -c $^ -o $@

$(BUILD_LOC)/%.o: $(TEST_LOC)/%.c
	$(CC) $(FLAGS) -c $^ -o $@


.PHONY: clean build

build:
	mkdir $(BUILD_LOC) $(BIN_LOC)

clean:
	rm -rf $(BUILD_LOC) $(BIN_LOC)
