#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    int size;
    int capacity;
} ArrayList;

ArrayList* createArrayList() {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    if (list == NULL) {
        printf("Failed to allocate memory for ArrayList\n");
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->capacity = 10;
    list->array = (int*)malloc(list->capacity * sizeof(int));
    if (list->array == NULL) {
        printf("Failed to allocate memory for array\n");
        exit(EXIT_FAILURE);
    }
    return list;
}

void add(ArrayList* list, int item) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
        if (list->array == NULL) {
            printf("Failed to allocate memory for array\n");
            exit(EXIT_FAILURE);
        }
    }
    list->array[list->size] = item;
    list->size++;
}

void insert(ArrayList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Invalid index for insertion: %d\n", index);
        return;
    }

    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
        if (list->array == NULL) {
            printf("Failed to allocate memory for array\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = list->size; i > index; i--) {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = item;
    list->size++;
}

int size(ArrayList* list) {
    return list->size;
}

void removeItem(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for removal: %d\n", index);
        return;
    }

    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

void set(ArrayList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for modification: %d\n", index);
        return;
    }
    list->array[index] = item;
}

int get(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for retrieval: %d\n", index);
        return -1;
    }
    return list->array[index];
}

void display(ArrayList* list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

void freeArrayList(ArrayList* list) {
    free(list->array);
    free(list);
}

int main() {
    ArrayList* list = createArrayList();

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

    freeArrayList(list);

    return 0;
}
