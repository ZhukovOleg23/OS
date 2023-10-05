#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("The size of the array should be larger 0.\n");
        return 1;
    }

    double arr[n];
    printf("Enter %d real numbers separated by a space: ", n);

    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double average = sum / n;

    int count = 0;

    double sum_after_negative = 0;

    int found_negative = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count++;
        }

        if (found_negative) {
            sum_after_negative += fabs(arr[i]);
        }

        if (arr[i] < 0) {
            found_negative = 1;
        }
    }

    printf("The number of elements greater than the average value: %d\n", count);
    printf("The sum of the moduli of the elements after the first negative element: %.2lf\n", sum_after_negative);

    return 0;
}
