#include <stdio.h>

int findLastPoint(int points[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        if (points[i] == 0) continue;
        for (j = i + 1; j < n; j++) {
            if (points[j] == 0) continue;
            points[i] += points[j];
            points[j] = 0;
        }
    }

    for (i = 0; i < n; i++) {
        if (points[i] != 0) {
            return points[i];
        }
    }

    return -1;
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    int points[n];
    printf("Enter the masses of the points:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &points[i]);
    }

    int lastPoint = findLastPoint(points, n);
    printf("The value of the last remaining point: %d\n", lastPoint);

    return 0;
}
