Introduction
A heap overflow is a severe memory management vulnerability that occurs when a program writes more data to a memory block than allocated in the heap. The heap is a dynamically allocated memory region used for managing variables, data structures, and objects at runtime. Unlike stack memory, which is limited and automatically managed, heap memory must be explicitly allocated and freed by the programmer, making it prone to overflows and related vulnerabilities.
Memory Allocation Basics
•	Dynamic Memory Use: Functions like malloc() in C or new in C++ allocate memory on the heap.
•	Persistence Beyond Function Scope: Heap memory persists beyond the lifetime of a single function, making it suitable for large, variable-sized, or long-lived data structures.
•	Manual Management: Developers must manually allocate and free heap memory, increasing the risk of misuse.
What is a Heap Overflow?
A heap overflow occurs when a program writes beyond the allocated memory boundaries in the heap. This typically happens due to incorrect buffer size management, lack of boundary checks, or user input exceeding expected limits. The excess data spills over into adjacent memory locations, potentially overwriting important program data or code.
('static/img/heap_overflow.jpg'):