#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee {
    int id;
    char name[12];
    int age;
    float salary;
} employee_t;

void emp_info(employee_t emp)
{
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %.2f\n\n", emp.salary);
}

int emp_aveage_age(employee_t emp[], int n)
{
    int sum = 0;

    if (n <= 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }

    return sum / n;
}

void emp_writefile(employee_t emp[], int n)
{
    FILE *fp = fopen("employee.bin", "wb");

    if (fp == NULL) {
        perror("Cannot open employee.bin for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (fwrite(&emp[i], sizeof(employee_t), 1, fp) != 1) {
            fprintf(stderr, "Cannot write employee data.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    if (fclose(fp) != 0) {
        perror("Cannot close employee.bin after writing");
        exit(EXIT_FAILURE);
    }
}

void emp_readfile(employee_t emp[], int n)
{
    FILE *fp = fopen("employee.bin", "rb");

    if (fp == NULL) {
        perror("Cannot open employee.bin for reading");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (fread(&emp[i], sizeof(employee_t), 1, fp) != 1) {
            fprintf(stderr, "Cannot read employee data.\n");
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        printf("[%d] %d %s\n", i, emp[i].id, emp[i].name);
    }

    if (fclose(fp) != 0) {
        perror("Cannot close employee.bin after reading");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    employee_t emp[3] = {0};
    employee_t read_emp[3] = {0};

    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000.0f;
    strcpy(emp[0].name, "IU");

    emp[1].id = 2;
    emp[1].age = 26;
    emp[1].salary = 36000.0f;
    strcpy(emp[1].name, "taylor");

    emp[2].id = 3;
    emp[2].age = 31;
    emp[2].salary = 90000.0f;
    strcpy(emp[2].name, "swift");

    emp_writefile(emp, 3);
    emp_readfile(read_emp, 3);

    printf("\n");
    for (int i = 0; i < 3; i++) {
        emp_info(read_emp[i]);
    }

    printf("Average age: %d\n", emp_aveage_age(read_emp, 3));

    return 0;
}
