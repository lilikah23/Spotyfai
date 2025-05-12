#include <stdlib.h>
#include "list.h"

struct Node {
    void *data;
    Node *next;
};

struct List {
    Node *head;
    Node *current;
};

List *list_create() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->current = NULL;
    return list;
}

void list_pushBack(List *list, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *ptr = list->head;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = newNode;
    }
}

void *list_first(List *list) {
    if (!list->head) return NULL;
    list->current = list->head;
    return list->current->data;
}

void *list_next(List *list) {
    if (!list->current || !list->current->next) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void list_clean(List *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->current = NULL;
}