# Implementando una Lista - Doubly Linked List in C

## Overview
A C lab assignment implementing a Double Linked List (TDA - Abstract Data Type). All core functions are fully implemented and tested.

## Files
- **list.h** - Header with struct definitions and function prototypes
- **list.c** - Full implementation of the doubly linked list
- **main.c** - Example usage with movie structs
- **test.c** - Automated test suite (60/60 score)
- **test.sh** - Shell script for compiling and running tests (uses git; run directly instead)

## Running
- **Tests:** `gcc -g test.c -Wall -o test_prog && ./test_prog`
- **Example:** `gcc main.c list.c -o main && ./main`

## Implemented Functions
- `createList()` - Creates and initializes an empty list
- `firstList()` / `nextList()` - Forward traversal
- `lastList()` / `prevList()` - Backward traversal
- `pushFront()` - Insert at head
- `pushBack()` - Insert at tail (uses pushCurrent)
- `pushCurrent()` - Insert after current node
- `popFront()` - Remove from head (uses popCurrent)
- `popBack()` - Remove from tail (uses popCurrent)
- `popCurrent()` - Remove current node and return its data
- `cleanList()` - Remove all nodes
