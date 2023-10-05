#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int rows;
    int cols;
    int** data;
};

struct Matrix* createMatrix(int rows, int cols) {
    struct Matrix* mat = (struct Matrix*)malloc(sizeof(struct Matrix));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error for matrix.\n");
        exit(1);
    }

    mat->rows = rows;
    mat->cols = cols;

    mat->data = (int**)malloc(sizeof(int*) * rows);
    if (mat->data == NULL) {
        fprintf(stderr, "Memory allocation error for matrix data.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        mat->data[i] = (int*)malloc(sizeof(int) * cols);
        if (mat->data[i] == NULL) {
            fprintf(stderr, "Memory allocation error for matrix row data.\n");
            exit(1);
        }
    }

    return mat;
}

void deleteMatrix(struct Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void resizeMatrix(struct Matrix* mat, int newRows, int newCols) {
    int** newData = (int**)malloc(sizeof(int*) * newRows);
    if (newData == NULL) {
        fprintf(stderr, "Memory allocation error for new matrix data.\n");
        exit(1);
    }

    for (int i = 0; i < newRows; i++) {
        newData[i] = (int*)malloc(sizeof(int) * newCols);
        if (newData[i] == NULL) {
            fprintf(stderr, "Memory allocation error for new matrix row data.\n");
            exit(1);
        }
    }

    int minRows = (mat->rows < newRows) ? mat->rows : newRows;
    int minCols = (mat->cols < newCols) ? mat->cols : newCols;

    for (int i = 0; i < minRows; i++) {
        for (int j = 0; j < minCols; j++) {
            newData[i][j] = mat->data[i][j];
        }
        free(mat->data[i]);
    }
    free(mat->data);

    mat->data = newData;
    mat->rows = newRows;
    mat->cols = newCols;
}

int numRows(struct Matrix* mat) {
    return mat->rows;
}

int numCols(struct Matrix* mat) {
    return mat->cols;
}

void setElement(struct Matrix* mat, int row, int col, int value) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        mat->data[row][col] = value;
    } else {
        fprintf(stderr, "Invalid matrix indices.\n");
    }
}

int getElement(struct Matrix* mat, int row, int col) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        return mat->data[row][col];
    } else {
        fprintf(stderr, "Invalid matrix indices.\n");
        return 0;
    }
}

void printMatrix(struct Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void saveMatrixToFile(struct Matrix* mat, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d %d\n", mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            fprintf(file, "%d ", mat->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

struct Matrix* readMatrixFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading.\n");
        return NULL;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    struct Matrix* mat = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &mat->data[i][j]);
        }
    }

    fclose(file);

    return mat;
}

struct Matrix* addMatrices(struct Matrix* mat1, struct Matrix* mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for addition.\n");
        return NULL;
    }

    struct Matrix* result = createMatrix(mat1->rows, mat1->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }

    return result;
}

struct Matrix* subtractMatrices(struct Matrix* mat1, struct Matrix* mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for subtraction.\n");
        return NULL;
    }

    struct Matrix* result = createMatrix(mat1->rows, mat1->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            result->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
        }
    }

    return result;
}

struct Matrix* multiplyMatrixByScalar(struct Matrix* mat, int scalar) {
    struct Matrix* result = createMatrix(mat->rows, mat->cols);

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            result->data[i][j] = mat->data[i][j] * scalar;
        }
    }

    return result;
}

struct Matrix* multiplyMatrices(struct Matrix* mat1, struct Matrix* mat2) {
    if (mat1->cols != mat2->rows) {
        fprintf(stderr, "Matrix dimensions do not match for multiplication.\n");
        return NULL;
    }

    struct Matrix* result = createMatrix(mat1->rows, mat2->cols);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < mat1->cols; k++) {
                result->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }

    return result;
}

int main() {
    struct Matrix* mat1 = createMatrix(3, 3);
    struct Matrix* mat2 = createMatrix(3, 3);

    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            setElement(mat1, i, j, i * mat1->cols + j);
            setElement(mat2, i, j, i * mat2->cols + j);
        }
    }

    printf("Matrix 1:\n");
    printMatrix(mat1);

    printf("\nMatrix 2:\n");
    printMatrix(mat2);

    struct Matrix* sum = addMatrices(mat1, mat2);
    if (sum != NULL) {
        printf("\nMatrix Sum:\n");
        printMatrix(sum);
        deleteMatrix(sum);
    }

    struct Matrix* difference = subtractMatrices(mat1, mat2);
    if (difference != NULL) {
        printf("\nMatrix Difference:\n");
        printMatrix(difference);
        deleteMatrix(difference);
    }

    struct Matrix* scaledMatrix = multiplyMatrixByScalar(mat1, 2);
    if (scaledMatrix != NULL) {
        printf("\nMatrix Scaled by 2:\n");
        printMatrix(scaledMatrix);
        deleteMatrix(scaledMatrix);
    }

    struct Matrix* product = multiplyMatrices(mat1, mat2);
    if (product != NULL) {
        printf("\nMatrix Product:\n");
        printMatrix(product);
        deleteMatrix(product);
    }

    saveMatrixToFile(mat1, "matrix.txt");
    struct Matrix* loadedMatrix = readMatrixFromFile("matrix.txt");
    if (loadedMatrix != NULL) {
        printf("\nLoaded Matrix:\n");
        printMatrix(loadedMatrix);
        deleteMatrix(loadedMatrix);
    }



    deleteMatrix(mat1);
    deleteMatrix(mat2);

    return 0;
}
