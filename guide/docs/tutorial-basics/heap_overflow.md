# Heap Overflow

## Introduction

A **heap overflow** is a severe memory management vulnerability that occurs when a program writes more data to a memory block than what has been allocated in the heap. The heap is a dynamically allocated memory region used for managing variables, data structures, and objects at runtime. Unlike stack memory—which is limited and automatically managed—heap memory must be explicitly allocated and freed by the programmer, making it more susceptible to overflows and related vulnerabilities.

---

## Memory Allocation Basics

### Key Characteristics of Heap Memory
- **Dynamic Memory Use**: Functions like `malloc()` in C or `new` in C++ allocate memory on the heap.
- **Persistence Beyond Function Scope**: Heap memory persists beyond the lifetime of a single function, making it suitable for large, variable-sized, or long-lived data structures.
- **Manual Management**: Developers must manually allocate and free heap memory, increasing the risk of misuse and errors.

---

## What is a Heap Overflow?

A **heap overflow** occurs when a program writes beyond the allocated memory boundaries in the heap. This can lead to severe issues such as memory corruption, unpredictable behavior, or exploitation by attackers.

### Common Causes
1. **Incorrect Buffer Size Management**: Allocating a smaller buffer than required.
2. **Lack of Boundary Checks**: Failing to validate the size of user input.
3. **Excessive Input Data**: Allowing user input to exceed expected limits without proper validation.

### Consequences of a Heap Overflow
- Overwriting critical program data or code.
- Triggering unexpected behavior, including application crashes.
- Exploitation by attackers to execute malicious code or gain unauthorized access.

---

## Visual Representation

You can use the following image to understand the concept of heap overflow better:

![Docusaurus logo](/img/heap_overflow.jpg)
