#ifndef pepita_chunk_h
#define pepita_chunk_h

#include "common.h"
#include "value.h"

/**
 * @defgroup Chunk Chunk
 * @{
 * @brief Group of functionalities and data structures related to bytecode
 * processing.
 *
 * @details Bytecode is an intermediate representation of code, typically used
 * as a step between source code and machine code. By converting source
 * code into bytecode, a system can then use a virtual machine or interpreter
 * to execute the bytecode directly, allowing for portability across
 * multiple platforms.
 *
 * Within this module, we define the basic structures and operations
 * that our system uses to represent and manipulate bytecode.
 */

/**
 * @brief Each instruction has a one-byte operation code (opcode).
 *
 * @details The opcode number controls what kind of instruction we’re dealing
 * with. Examples include add, subtract, look up variable, etc.
 */
typedef enum {
  OP_CONSTANT, ///< A two byte operand that specifies which constant to load.
  OP_RETURN,   ///< A one byte operand that returns from the current function.
} OpCode;

/**
 * @brief Bytecode representation as a series of instructions.
 *
 * @details This structure acts as a wrapper around an array of bytes. Since the
 * size of the array is unknown prior to compiling a chunk, it is dynamically
 * sized.
 */
typedef struct {
  uint8_t* code;        ///< A series of instructions.
  int count;            ///< The number of allocated entries actually in use.
  int capacity;         ///< The number of elements allocated.
  ValueArray constants; ///< A list of the values that appear as literals.
  int* lines; ///< Line number for the corresponding byte in the bytecode.
} Chunk;

/**
 * @brief Initialize a new chunk.
 *
 * @details The dynamic array is initialized without allocating any memory. This
 * means the raw array is not created upon initialization.
 *
 * @param chunk Pointer to the chunk to be initialized.
 */
void initChunk(Chunk* chunk);

/**
 * @brief Appends a byte to the specified chunk.
 *
 * @details This function handles the addition of a new byte to a chunk. If the
 * chunk has available space, the byte is directly appended. Otherwise, the
 * function will reallocate memory to ensure the chunk can accommodate the new
 * byte.
 *
 * If the chunk is at capacity:
 *  -# Allocate a new array with increased capacity.
 *  -# Copy contents from the old array to the new one.
 *  -# Update the chunk's capacity to the new array's capacity.
 *  -# Deallocate memory used by the old array.
 *  -# Redirect the chunk's pointer to the new array.
 *  -# Append the new byte to the new array.
 *  -# Increment the byte count in the chunk.
 *
 * @param chunk Pointer to the chunk where the byte should be added.
 * @param byte The byte to append to the chunk.
 */
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/**
 * @brief Add a new constant to a chunk.
 *
 * @param chunk Pointer to the chunk to which the constant should be added.
 * @param value The constant value to be added to the chunk.
 * @return Returns the index at which the constant was added.
 */
int addConstant(Chunk* chunk, Value value);

/**
 * @brief Deallocates memory associated with a chunk and resets its state.
 *
 * @details This function first releases all memory used by the chunk.
 * Afterwards, it calls `initChunk()` to reset and zero out the chunk's fields,
 * ensuring the chunk is left in a well-defined, empty state.
 *
 * @param chunk Pointer to the chunk to be deallocated and reset.
 */
void freeChunk(Chunk* chunk);

/** @} */ // end of Chunk group

#endif
