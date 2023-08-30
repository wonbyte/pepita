#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);
  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

/**
 * @brief Prints the name of an opcode and returns the offset for the next byte.
 *
 * @details The function displays the given opcode name. Its primary purpose is
 * to help in disassembling and debugging the bytecode. After printing the
 * opcode name, it calculates the offset for the next instruction, assuming the
 * current instruction occupies a single byte.
 *
 * @param name The name of the opcode to print.
 * @param offset The current offset of the opcode within the chunk.
 * @return The offset for the next instruction.
 */
static int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%04d ", offset);
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }
  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
  case OP_CONSTANT: return constantInstruction("OP_CONSTANT", chunk, offset);
  case OP_RETURN: return simpleInstruction("OP_RETURN", offset);
  default: printf("Unknown opcode %d\n", instruction); return offset + 1;
  }
}
