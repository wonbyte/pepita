#ifndef pepita_value_h
#define pepita_value_h

#include "common.h"

typedef double Value;

/**
 * @brief Represents a pool of constant values.
 *
 * The constant pool is an array of values. The instruction to load a constant
 * looks up the value by index in that array.
 */
typedef struct {
  int capacity;  ///< The allocated capacity.
  int count;     ///< The number of elements in use.
  Value* values; ///< A list of values that appear as literals.
} ValueArray;

/**
 * @brief Initialize a new value array.
 *
 * @details The dynamic array is initialized without allocating any memory. This
 * means the raw array is not created upon initialization.
 *
 * @param chunk Pointer to the value array to be initialized.
 */
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
