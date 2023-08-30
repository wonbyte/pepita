#ifndef pepita_debug_h
#define pepita_debug_h

#include "chunk.h"

/**
 * @brief Disassembles a chunk
 *
 * @details It starts by printing a header (allowing identification of the
 * chunk) and then iterates through the bytecode, disassembling each
 * instruction. The iteration method is unique: instead of incrementing the
 * offset within the loop, the offset of the next instruction is returned by
 * `disassembleInstruction()`. This approach caters to the fact that
 * instructions can have varying sizes.
 *
 * @param chunk Pointer to the chunk to be disassembled.
 * @param name Name of the chunk (used in the header for identification).
 */
void disassembleChunk(Chunk* chunk, const char* name);

/**
 * @brief Disassembles a single instruction.
 *
 * @details This function begins by printing the byte offset of the instruction,
 * indicating its location within the chunk. This offset is especially useful
 * when there's control flow, as it can be used to track jumps within the
 * bytecode.
 *
 * After printing the offset, the function fetches the opcode from the chunk at
 * the specified offset. Based on this opcode, the function then dispatches to
 * the appropriate utility function to display the instruction. If an
 * unrecognized opcode is encountered (which might indicate a compiler bug), it
 * is also printed.
 *
 * @param chunk The chunk containing the bytecode.
 * @param offset The offset within the chunk where the instruction begins.
 * @return The offset of the beginning of the next instruction.
 */
int disassembleInstruction(Chunk* chunk, int offset);

#endif
