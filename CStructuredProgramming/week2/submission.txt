// importing dependencies
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// defining macro facilities
#define SIZE 10
#define DEPT_SIZE 5
#define MIN_SALARY 20000
#define MAX_SALARY 120000
#define SOCIAL_SECURITY_DIGITS 5


// abstract data types
typedef enum dept {
    HR,
    SALES,
    RESEARCH,
    SOFTWARE,
    EXECUTIVE
} dept;
typedef struct employee {
    dept department;
    int salary;
    unsigned int social_security;
} employee;


// print methods
void print_dept(dept d) {
    switch (d) {
        case HR: printf("HR\t"); break;
        case SALES: printf("Sales"); break;
        case RESEARCH: printf("Research"); break;
        case SOFTWARE: printf("Software"); break;
        case EXECUTIVE: printf("Executive"); break;
        default: printf("error: not a department");
    }
}
void print_array(int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
}
void print_data(employee e) {
    printf("department: "); print_dept(e.department);
    printf("\tsalary: $%d\t\tsocial security: %d\n", e.salary, e.social_security);
}


// random data generators
int randint(int min, int max) {
    return (rand() % (max - min)) + min;
}
void generate_rand_array(int array[], int size, int min, int max) {
    int i;
    for (i = 0; i < size; i++) {
        array[i] = randint(min, max);
    }
}
void generate_employees(employee employees[], int salaries[]) {
    int i;
    for (i = 0; i < SIZE; i++) {
        employees[i].department = randint(0, DEPT_SIZE);
        employees[i].salary = salaries[employees[i].department] + randint(0, 20000);
        employees[i].social_security = randint(pow(10, SOCIAL_SECURITY_DIGITS - 1), pow(10, SOCIAL_SECURITY_DIGITS));
    }
}


// main method
int main() {
    srand(clock());
    employee company[SIZE];
    int salary[DEPT_SIZE];
    int i;
    generate_rand_array(salary, DEPT_SIZE, MIN_SALARY, MAX_SALARY);
    generate_employees(company, salary);
    for (i = 0; i < SIZE; i++) {
        print_data(company[i]);
    }
    return 0;
}
