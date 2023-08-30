#ifndef pepita_memory_h
#define pepita_memory_h

#include "common.h"

/**
 * @defgroup Memory Memory
 * @{
 * @brief Lower level memory operations.
 *
 */

/**
 * @brief Calculates a new capacity based on a given current capacity.
 *
 * @details This macro ensures that the capacity scales relative to the old size
 * for optimal performance. If the current capacity is zero, it will default to
 * eight elements. This strategy minimizes memory churn for very small arrays,
 * even though it might waste a few bytes on tiny chunks.
 *
 * @param capacity The current capacity.
 * @return The new capacity: either 8 or twice the current capacity.
 */
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity)*2)

/**
 * @brief Resizes an array with the given type and count, handling type size and
 * casting.
 *
 * @details This macro simplifies the call to the `reallocate()` function,
 * taking care of calculating the size of the array’s element type.
 * Additionally, it casts the resulting _void*_ back to the correct pointer
 * type.
 *
 * @param type Type of the array elements.
 * @param pointer Pointer to the old array.
 * @param oldCount Count of elements in the old array.
 * @param newCount Desired count of elements in the new array.
 * @return A pointer to the reallocated array of the specified type.
 */
#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
  (type*)reallocate(pointer, sizeof(type) * (oldCount),                        \
                    sizeof(type) * (newCount))

/**
 * @brief Deallocates memory for an array.
 *
 * @details A convenient wrapper around the `reallocate()` function to
 * specifically deallocate memory. It accomplishes this by specifying the new
 * size as zero, signaling `reallocate()` to free the associated memory.
 *
 * @param type The type of elements in the array.
 * @param pointer Pointer to the array to be deallocated.
 * @param oldCount The number of elements in the array prior to deallocation.
 */
#define FREE_ARRAY(type, pointer, oldCount)                                    \
  reallocate(pointer, sizeof(type) * (oldCount), 0)

/**
 * @brief Manages dynamic memory in pepita, including allocation, deallocation,
 * and resizing.
 *
 * The `reallocate()` function serves as a central point for all dynamic memory
 * management operations in pepita. It intelligently handles various scenarios
 * based on the old and new sizes provided.
 *
 * @details The behavior of `reallocate()` for various size parameters:
 * - When `oldSize` is 0 and `newSize` is non-zero, a new block is allocated.
 * - When `oldSize` is non-zero and `newSize` is 0, the existing block is
 * deallocated.
 * - For non-zero `oldSize` and `newSize`, if `newSize` is smaller, the function
 * shrinks the existing block.
 * - For non-zero `oldSize` and `newSize`, if `newSize` is larger, the function
 * tries to grow the block.
 *
 * Internally, deallocation is handled by calling `free()`. In other cases, the
 * function leans on the C standard library's `realloc()`. Here's how:
 * - If `oldSize` is 0, `realloc()` acts like `malloc()`.
 * - If both sizes are non-zero, `realloc()` tries to resize the block.
 * - If `newSize` is smaller, it updates the size and returns the same pointer.
 * - If `newSize` is larger and there's adjacent free memory, it grows the
 * block.
 * -If there isn't enough free space, `realloc()` allocates a new block,
 * copies the old data, frees the old block, and returns the new block's
 * pointer.
 *
 * @param pointer Pointer to the memory block to manage.
 * @param oldSize Current size of the memory block.
 * @param newSize Desired size for the memory block.
 * @return Pointer to the managed memory block. It could be the same or a new
 * location if reallocated.
 */
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

/** @} */ // end of Memory group

#endif
