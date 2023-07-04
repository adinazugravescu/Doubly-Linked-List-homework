# Doubly-Linked-List-homework
1.

A magical tape is implemented and used by David to efficiently store and manipulate data in terms of memory. The tape is indexed and can contain different characters at each position. Additionally, David can move his finger left or right on the tape until a certain symbol is reached. The magic tape is considered infinite on the right side and limited on the left side. The special characters "#" and "|" are used to indicate the position and symbol marked by the finger. The tape is represented as a doubly linked list with a sentinel and can be extended to the right.

2.

Presentation of possible operations:
There are several operations that can be performed by David. These operations are divided into the following categories: UPDATE, QUERY, UNDO/REDO, EXECUTE. We will now present each category separately, specifying their particularities and the included operations for each.

2.1. UPDATE

It is important to note that these operations are not executed directly. When encountering such a command, it is added to a queue.
The possible UPDATE operations are:

• Move the finger one position to the left/right: "MOVE_LEFT" or "MOVE_RIGHT". If we are at the first position and encounter the "MOVE_LEFT" operation, nothing happens. However, if we are at the last position and encounter "MOVE_RIGHT," we move the finger one position to the right, and the corresponding cell is filled with the character "#".

• Move left/right until the first character equal to a certain symbol is found: "MOVE_LEFT_CHAR <C>", "MOVE_RIGHT_CHAR <C>", where <C> is a character. The search starts from the current position of the finger.
In the case of "MOVE_LEFT_CHAR <C>", if we reach the left edge of the tape and the searched character is not found, an ERROR message is displayed, and the position of the finger remains unchanged.
In the case of "MOVE_RIGHT_CHAR <C>", if we reach the right end of the tape containing characters and the searched character is not found, a "#" is inserted at the end, and the position of the finger will be on the inserted "#".

• Update the current character: "WRITE <C>"

• Insert a character to the left/right of the finger's position (involves insertion and moving the finger to the newly inserted position): "INSERT_LEFT <C>", "INSERT_RIGHT <C>". If the finger is at the first position, it is not possible to insert to the left - an ERROR message is displayed, and the tape remains unchanged, and the position of the finger remains unaltered.

2.2. QUERY

These operations are executed directly when encountered.

• Determine character at the finger's position: "SHOW_CURRENT"

• Display tape content: "SHOW". The character at the finger's position will be placed between |. For example, abc|d|e signifies that the finger is on the character d.

2.3. UNDO/REDO

For each of the UNDO/REDO operations, a stack/command will be used, which will be implemented based on a list.
The UNDO/REDO operations allow the cancellation of the last applied operation and the restoration of the last applied operation, respectively.
It is guaranteed that the UNDO/REDO operations will only be given for the "MOVE_LEFT" and "MOVE_RIGHT" operations. They will not be given for the "WRITE <C>", "INSERT_LEFT <C>", and "INSERT_RIGHT <C>" operations. No additional checks need to be performed to verify this (it is guaranteed that the UNDO/REDO operations will not modify the tape).

2.4. EXECUTE

For the EXECUTE command, a queue will be used, implemented based on a list.
To make things more interesting, the UPDATE operations will not be executed as they are read. Instead, they will be added to a queue. In the tests, the list of queries will include interleaved EXECUTE commands. An EXECUTE command will take the first available UPDATE operation from the queue and execute it. Until an EXECUTE command is given, the tape remains in its original state ("#").





The implementation of the assignment is done using 2 source files (a header file and a file containing the main function) and a Makefile used for compiling the sources, creating the executable, running it, and deleting it.

The header file, "tema1.h," contains the definition of structures (for the tape, a doubly linked list with a sentinel node and a "finger" aka the current node, for the stack - TStack, and for the queue - TQueue), as well as several functions:
-> functions that will implement the operations required (UPDATE, QUERY, UNDO/DO, EXECUTE);
-> functions for processing abstract data types (for the doubly linked list, we have a function for creating a node in the list, one for initializing this particular type of list, and one for deallocating memory; for the stack, we have functions for initialization, checking if the stack is empty, inserting a new element, removing from the stack, and deallocating memory; for the queue, we have functions for initialization and freeing a node, initializing the queue, checking if it is empty, adding and removing elements, finding the first value, and freeing memory).

In "tema1.c," the tape will be represented by the List variable, the stack for UNDO operations by stackU, the stack for REDO operations by stackR, and the queue for EXECUTE operations by the queue variable. By reading from the "tema1.in" file, we first have the number of operations in the variable n, then we read each line containing a command into an inputCharacters variable, based on which multiple tape operations will be performed. If the command is not of type EXECUTE, we handle two cases: the UPDATE type, which will be added to the queue, and the on-spot execution case, which involves two variants - QUERY and UNDO/REDO. QUERY results in calling the show and show_current functions, while UNDO and REDO involve filling and emptying the stacks with the addresses of the current last node, according to the requirements. If the command is of type EXECUTE, then we sequentially perform the UPDATE operations by calling the implemented functions for them in tema1.h. Finally, we deallocate the list and close the input and output files.
