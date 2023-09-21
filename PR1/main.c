#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    char name[30];
    char surname[30];
    int age;
};

int main() {
    int numberOfStudents = 0;
    int maxStudents = 0;

    while (1){
        printf("How many students are in your group?\n");
        if(scanf("%d", &numberOfStudents) != 1){
            printf("Invalid number of students. Try again!\n");
            getchar();
        }else if (numberOfStudents <= 0) {
            printf("Invalid number of students. Try again!\n");
        }else{
            break;
        }
    }

    struct Student *students = (struct Student *)malloc(numberOfStudents * sizeof(struct Student));


    while (1) {
        printf("Choose an option:\n");
        printf("1. Add a student\n");
        printf("2. View students\n");
        printf("3. Exit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (numberOfStudents > maxStudents) {
                    printf("Enter student name: ");
                    scanf("%s", students[maxStudents].name);
                    printf("Enter student surname: ");
                    scanf("%s", students[maxStudents].surname);
                    printf("Enter student age: ");
                    scanf("%d", &students[maxStudents].age);
                    maxStudents++;
                } else {
                    printf("Student collection is full!\n");
                }
                break;

            case 2:
                printf("List of students:\n");
                for (int i = 0; i < numberOfStudents; i++) {
                    printf("Name: %s,Surname: %s Age: %d\n", students[i].name, students[i].surname, students[i].age);
                }
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid option. Please try again.\n");
        }

    }

}
