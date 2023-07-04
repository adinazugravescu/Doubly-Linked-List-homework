#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tema1.h"
int main (void) {
    List* List = createList();  ///tape
    TStack* stackU = inits();   ///UNDO stack
    TStack* stackR = inits();   ///REDO stack
    TQueue* queue = initq();    ///EXECUTE queue
    char inputCharacters[256]; 
    char input_filename[] = "tema1.in";
    char output_filename[] = "tema1.out";
    int n;
    FILE *outFile = fopen(output_filename, "wt");
    FILE* inFile = fopen(input_filename, "rt");
    if (inFile == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", input_filename);
        return -1;
    }
    if (outFile == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", output_filename);
        return -1;
    }
    fscanf(inFile, "%d", &n);
    while (fgets(inputCharacters, 256, inFile) != NULL) {
        if (strlen(inputCharacters) < 2)
            continue;
        if (strncmp(inputCharacters, "EXECUTE", 7) !=  0) {
            if (strncmp(inputCharacters, "UNDO", 4) != 0 && strncmp(inputCharacters, "REDO", 4) != 0 && strncmp(inputCharacters, "SHOW", 4) != 0) {
                queue = enqueue(queue, inputCharacters);    //UPDATE operations will be added to a queue
                continue;
            }
           /// else{ } UNDO sI REDO + SHOW SHOWCURRENT
           else {
                if (strncmp(inputCharacters, "SHOW", 4) == 0) {
                    if (inputCharacters[4] == '_')
                        show_current(List, outFile);
                    else
                        show(List, outFile);
                    continue;
                }
                else {
                    if (strncmp(inputCharacters, "UNDO", 4) == 0) {
                        ListNode* aux = top(stackU);
                        stackU = pop(stackU);
                        stackR = push(stackR, List->deget);
                        List->deget = aux;
                        continue;
                    }
                    if (strncmp(inputCharacters, "REDO", 4) == 0) {
                        ListNode* aux = top(stackR);
                        stackR = pop(stackR);
                        stackU = push(stackU, List->deget);
                        List->deget = aux;
                        continue;
                    }
                }
           }
        }
        else { ///EXECUTE
            char comm[256];  
            strcpy(comm, queue->head->com);
            queue = dequeue(queue);
            if (strncmp(comm, "MOVE_LEFT", 9) == 0 && comm[9] != '_') {
                ListNode* temp = List->deget;
                if (List->deget->prev == List->sentinel)
                    continue;
                move_left(List);
                stackU = push(stackU, temp);
                continue;
            }
            if (strncmp(comm, "MOVE_RIGHT", 10) == 0 && comm[10] != '_') {
                ListNode* temp = List->deget;
                move_right(List);
                stackU = push(stackU, temp);
                continue;
            }
            if (strncmp(comm, "MOVE_LEFT_CHAR", 14) == 0) {
                char e = comm[15];
                move_left_char(List, e, outFile);
                continue;
            }
            if (strncmp(comm, "MOVE_RIGHT_CHAR", 15) == 0) {
                char e = comm[16];
                move_right_char(List, e);
                continue;
            }
            if (strncmp(comm, "WRITE", 5) == 0) {
                char e = comm[6];
                write(List, e);
                stackU = freeStack(stackU);
                stackR = freeStack(stackR);
                continue;
            }
            if (strncmp(comm, "INSERT_LEFT", 11) == 0){
                char e = comm[12];
                insert_left(List, e, outFile);
                continue;
            }
            if (strncmp(comm, "INSERT_RIGHT", 12) == 0) {
                char e = comm[13];
                insert_right(List, e);
                continue;
            }
        }
    }
    freeL(List);
    stackU = freeStack(stackU);
    free(stackU);
    stackR = freeStack(stackR);
    free(stackR);
    free(queue);
    fclose(inFile);
    fclose(outFile);
}
