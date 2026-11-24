
// list/list.c
//
// Implementation for linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Allocate a new empty list
list_t *list_alloc() {
    list_t *mylist = malloc(sizeof(list_t));

    if (mylist == NULL) {
        return NULL;
    }

    mylist->head = NULL;

    return mylist;
}

// Free the entire list and all its nodes
void list_free(list_t *l) {
    if (l == NULL) {
        return;
    }

    node_t *curr = l->head;

    while (curr != NULL) {
        node_t *temp = curr;
        curr = curr->next;
        free(temp);
    }

    free(l);
}

// Print the list
void list_print(list_t *l) {
    char *str = listToString(l);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }
}

// Convert the list into a string
char *listToString(list_t *l) {
    if (l == NULL) {
        return NULL;
    }

    size_t size = 5; // Space for "NULL" and '\0'
    node_t *curr = l->head;

    // Calculate the required buffer size
    while (curr != NULL) {
        size += snprintf(NULL, 0, "%d->", curr->value);
        curr = curr->next;
    }

    char *buf = malloc(size);

    if (buf == NULL) {
        return NULL;
    }

    buf[0] = '\0';
    curr = l->head;

    // Build the string
    while (curr != NULL) {
        char tbuf[32];
        snprintf(tbuf, sizeof(tbuf), "%d->", curr->value);
        strcat(buf, tbuf);
        curr = curr->next;
    }

    strcat(buf, "NULL");

    return buf;
}

// Return the number of elements in the list
int list_length(list_t *l) {
    if (l == NULL) {
        return 0;
    }

    int count = 0;
    node_t *curr = l->head;

    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    return count;
}

// Allocate a new node
node_t *getNode(elem value) {
    node_t *mynode = malloc(sizeof(node_t));

    if (mynode == NULL) {
        return NULL;
    }

    mynode->value = value;
    mynode->next = NULL;

    return mynode;
}

// Add an element to the back
void list_add_to_back(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *newNode = getNode(value);

    if (newNode == NULL) {
        return;
    }

    if (l->head == NULL) {
        l->head = newNode;
        return;
    }

    node_t *curr = l->head;

    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = newNode;
}

// Add an element to the front
void list_add_to_front(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *newNode = getNode(value);

    if (newNode == NULL) {
        return;
    }

    newNode->next = l->head;
    l->head = newNode;
}

// Add an element at a specific index (1-based)
void list_add_at_index(list_t *l, elem value, int index) {
    if (l == NULL || index < 1 || index > list_length(l) + 1) {
        return;
    }

    if (index == 1) {
        list_add_to_front(l, value);
        return;
    }

    node_t *newNode = getNode(value);

    if (newNode == NULL) {
        return;
    }

    node_t *curr = l->head;

    for (int i = 1; i < index - 1; i++) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
}

// Remove an element from the back
elem list_remove_from_back(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1;
    }

    node_t *curr = l->head;

    if (curr->next == NULL) {
        elem value = curr->value;
        free(curr);
        l->head = NULL;
        return value;
    }

    while (curr->next->next != NULL) {
        curr = curr->next;
    }

    node_t *temp = curr->next;
    elem value = temp->value;

    curr->next = NULL;
    free(temp);

    return value;
}

// Remove an element from the front
elem list_remove_from_front(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1;
    }

    node_t *temp = l->head;
    elem value = temp->value;

    l->head = temp->next;

    free(temp);

    return value;
}

// Remove an element at a specific index (1-based)
elem list_remove_at_index(list_t *l, int index) {
    if (l == NULL || index < 1 || index > list_length(l)) {
        return -1;
    }

    if (index == 1) {
        return list_remove_from_front(l);
    }

    node_t *curr = l->head;

    for (int i = 1; i < index - 1; i++) {
        curr = curr->next;
    }

    node_t *temp = curr->next;
    elem value = temp->value;

    curr->next = temp->next;

    free(temp);

    return value;
}

// Check whether an element exists in the list
bool list_is_in(list_t *l, elem value) {
    if (l == NULL) {
        return false;
    }

    node_t *curr = l->head;

    while (curr != NULL) {
        if (curr->value == value) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}

// Return the element at a specific index (1-based)
elem list_get_elem_at(list_t *l, int index) {
    if (l == NULL || index < 1) {
        return -1;
    }

    node_t *curr = l->head;

    for (int i = 1; i < index; i++) {
        if (curr == NULL) {
            return -1;
        }

        curr = curr->next;
    }

    if (curr == NULL) {
        return -1;
    }

    return curr->value;
}

// Return the index of an element (1-based)
int list_get_index_of(list_t *l, elem value) {
    if (l == NULL) {
        return -1;
    }

    node_t *curr = l->head;
    int index = 1;

    while (curr != NULL) {
        if (curr->value == value) {
            return index;
        }

        curr = curr->next;
        index++;
    }

    return -1;
}
