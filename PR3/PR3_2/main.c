#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void add(LinkedList* list, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

void insert(LinkedList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Invalid index for insertion: %d\n", index);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

int size(LinkedList* list) {
    return list->size;
}

void removeItem(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for removal: %d\n", index);
        return;
    }

    if (index == 0) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    list->size--;
}

void set(LinkedList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for modification: %d\n", index);
        return;
    }

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = item;
}

int get(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for retrieval: %d\n", index);
        return -1;
    }

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void display(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* list = createLinkedList();

    add(list, 1);
    add(list, 2);
    add(list, 3);

    printf("List elements: ");
    display(list);

    insert(list, 1, 4);

    printf("List elements after insertion: ");
    display(list);

    removeItem(list, 2);

    printf("List elements after removal: ");
    display(list);

    set(list, 0, 5);

    printf("List elements after modification: ");
    display(list);

    int value = get(list, 2);
    printf("Value at index 2: %d\n", value);

    int listSize = size(list);
    printf("List size: %d\n", listSize);

    freeLinkedList(list);

    return 0;
}
