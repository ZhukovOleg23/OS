#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateNumber() {
    return rand() % 10;
}

int containsSeven(int *numbers, int length) {
    for (int i = 0; i < length; i++) {
        if (numbers[i] == 7) {
            return 1;
        }
    }
    return 0;
}

int allNumbersAreSeven(int *numbers, int length) {
    for (int i = 1; i < length; i++) {
        if (numbers[i] != numbers[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    srand(time(NULL));

    int bet;
    int length;
    int option;

    while(1){

        printf("Choose an option:\n");
        printf("1. Play\n");
        printf("2. View balance\n");
        printf("3. Exit\n");

        scanf("%d", &option);

        switch (option){
            case 1:
            {

                printf("Enter your bet: ");
                scanf("%d", &bet);

                printf("Enter the length of the sequence of numbers: ");
                while(1) {
                    if (scanf("%d", &length) != 1) {
                        printf("Invalid length of the sequence of numbers. Try again!\n");
                        getchar();
                    } else if (length < 1) {
                        printf("Invalid length of the sequence of numbers (minimum 1). Try again!\n");
                    } else {
                        break;
                    }
                }

                int numbers[length];

                for (int i = 0; i < length; i++) {
                    numbers[i] = generateNumber();
                }

                printf("Your numbers: ");
                for (int i = 0; i < length; i++) {
                    printf("%d ", numbers[i]);
                }
                printf("\n");

                if (containsSeven(numbers, length)) {
                    printf("You won! Your bet is returned\n");
                } else if (allNumbersAreSeven(numbers, length)) {
                    if (numbers[0] == 7) {
                        printf("You won! Your bet is tripled (x3)\n");
                        bet *= 3;
                    } else {
                        printf("You won! Your bet is doubled (x2)\n");
                        bet *= 2;
                    }
                } else {
                    int sameCount = 0;
                    for (int i = 0; i < length; i++) {
                        for (int j = i + 1; j < length; j++) {
                            if (numbers[i] == numbers[j]) {
                                sameCount++;
                            }
                        }
                    }
                    if (sameCount >= length / 3) {
                        printf("You won! Your bet is returned\n");
                    } else {
                        printf("You lost, he-he-he. Your bet is forfeited.\n");
                    }
                }
                break;
            }

            case 2:
                printf("Your winnings: %d\n", bet);
            break;

            case 3:
                exit(0);
        }

    }

}
