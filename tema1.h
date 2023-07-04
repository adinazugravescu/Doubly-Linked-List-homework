#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _tema_1_h
#define _tema_1_h

//element of a doubly linked list
typedef struct ListNode {
    char elem;
    struct ListNode* prev;
    struct ListNode* next;
}ListNode;

typedef struct List {       //list = tape
    ListNode* sentinel;     //list's sentinel
    ListNode* deget;    //current(finger) position
}List;

//create and alloc a node
ListNode *createNode(char elem) {
	ListNode* node = (ListNode *)malloc(sizeof(struct ListNode));
	node->elem=elem;
	node->next=NULL;
	node->prev=NULL;
	return node;
}

//create and alloc a list - empty sentinel and one # node
List* createList(void) {
    ListNode* sentinel = calloc (1,sizeof(struct ListNode));
    ListNode* tmp = createNode ('#');
    tmp->prev = sentinel;
    sentinel->next = tmp;
	List* List = malloc(sizeof(struct List));
    List->sentinel = sentinel;
	List->deget = sentinel->next;
	return List;
}

//OPERATIONS

///UPDATE
void move_left (List* List) {
    if (List->deget->prev == List->sentinel) {
        return;
    }
    List->deget = List->deget->prev;
    return;
}

void move_right (List* List) {
    if (List->deget->next == NULL) {    //if node->next is NULL , create a # node ; puts current on the next
        ListNode* tmp = createNode('#');
        tmp->prev = List->deget;
        List->deget->next = tmp;
        List->deget = tmp;
        return;
    }
    List->deget = List->deget->next;
    return;
}

void move_left_char (List* List , char elem, FILE* file) {  //current moves on the first left elem; ERROR if that part of the list does not 
    ListNode* iter = List->deget;                           //contain elem
    while (iter != List->sentinel) {
        if ( iter->elem == elem ) {
            List->deget = iter;
            return;
        }
        iter = iter->prev;
    }
    fprintf(file, "ERROR\n");
    return;
}

void move_right_char (List* List , char elem) {     //similar to move_left_char;if it does not find elem , it creates a # node that becomes current
    ListNode* iter = List->deget;
    while (iter->next != NULL) {
        if ( iter->elem == elem) {
            List->deget = iter;
            return;
        }
        iter = iter->next;
    }
    if ( iter->elem == elem ) {
            List->deget = iter;
            return;
    } else {
        ListNode* tmp = createNode('#');
        iter->next = tmp;
        tmp->prev = iter;
        List->deget = tmp;
        return;
    }
}

void write (List* List , char elem) {   //overwrites the value of the current element
    List->deget->elem = elem;
    return;
}
//character insertion to the left / right of the current(finger) position
void insert_left (List* List , char elem ,FILE* file) {
    if (List->deget->prev == List->sentinel) {
        fprintf(file, "ERROR\n");
        return;
    }
    ListNode* node = createNode(elem);
    ListNode* st = List->deget->prev;
    st->next = node;
    node->prev = st;
    node->next = List->deget;
    List->deget->prev = node;
    List->deget = node;
    return;
}

void insert_right (List* List , char elem ) {
    ListNode* node = createNode(elem);
    if (List->deget->next == NULL) {
        List->deget->next = node;
        node->prev = List->deget;
        List->deget = node;
        return;
    }
    ListNode* dr = List->deget->next;
    List->deget->next = node;
    node->prev = List->deget;
    node->next = dr;
    dr->prev = node;
    List->deget = node;
    return;
}
/// QUERY
void show_current (List* List, FILE* file) {
    fprintf(file, "%c\n", List->deget->elem);
    return;
}

void show (List* List, FILE* file) {    //Display tape content
    ListNode* iter = List->sentinel->next;
    while (iter != NULL) {
        if (iter == List->deget) {
            fprintf(file, "|%c|", iter->elem);
        } else {
            fprintf(file, "%c", iter->elem);
        }
        iter = iter->next;
    }
    fprintf(file, "\n");
    return;
}
void freeL (List* List) {
    if (List == NULL)
        return;
    ListNode* tmp, *iter;
    iter = List->sentinel->next;
    while (iter != NULL){
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }
    free(List->sentinel);
    free(List);
}
/// UNDO REDO
typedef struct stack {
    ListNode* adrNode;
    struct stack *next;
}TStack;

TStack* initS (ListNode* node) {
    TStack* s = malloc(sizeof(struct stack));
    s->adrNode = node;
    s->next = NULL;
    return s;
}

int isEmpty(TStack* s) {
    return s == NULL;
}

TStack* push (TStack* s, ListNode* node) {
    if (isEmpty(s))
        return initS(node);
    TStack* top = initS(node);
    top->next = s;
    return top;
}
TStack* pop (TStack* s) {
    if (isEmpty(s))
        return s;
    TStack* tmp = s;
    s = s->next;
    free(tmp);
    return s;
}
ListNode* top (TStack* s) {
    if (isEmpty(s))
        exit(1);
    return s->adrNode;
}
TStack* freeStack(TStack* s) {
    while (!isEmpty(s))
        s = pop(s);
    return NULL;
}
TStack* inits() {
    return NULL;
}
///QUEUE
typedef struct node {
    char com[256];
    struct node* next;
}Node;

typedef struct queue {
    Node *head, *tail;
    int size;
}TQueue;

Node *initNode(char data[256]) {
    Node *node = malloc(sizeof(struct node));
    strcpy(node->com , data);
    node->next = NULL;
    return node;
}

Node *freeNode(Node *node) {
    if (node)
        free(node);
    return NULL;
}

TQueue* initQueue(char data[256]) {
    TQueue* queue = malloc(sizeof(struct queue));
    queue->head = queue->tail = initNode(data);
    queue->size = 1;
    return queue;
}
TQueue* initq() {
    return NULL;
}
int isQEmpty(TQueue* queue) {
    return queue == NULL || queue->head == NULL || queue->size == 0;
}

TQueue* enqueue (TQueue* queue, char data[256]) {
    Node* node;
    if (isQEmpty(queue)) {
        if  (queue == NULL)
            return initQueue(data);
        free(queue);
        return initQueue(data);
    }
    node = initNode(data);
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return queue;
}

TQueue* dequeue (TQueue* queue) {
    Node* tmp;
    if (!(isQEmpty(queue))) {
        tmp = queue->head;
        queue->head = queue->head->next;
        tmp = freeNode(tmp);
        queue->size--;
    }
    return queue;
}

char* front (TQueue* queue) {
    if (!isQEmpty(queue)) {
        return queue->head->com;
    }
    else
        exit(1);
}

TQueue* freeQueue (TQueue* queue) {
    while (!isQEmpty(queue)) {
        queue = dequeue(queue);
    }
    if(queue)
        free(queue);
    return NULL;
}

#endif
