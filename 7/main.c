#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "student.h"

int main(int argc, char *argv[]) {
    int group_len = 0;
    int group_size = 0;
    Student **group = NULL;
    char *line_v = NULL;
    int i;
    int j;

    if (argc == 1) {
        fprintf(stderr, "Błąd, brak argumentów\n");
        exit(1);
    }

    for (i=1; i<argc; i++) {
        FILE* fptr = fopen(argv[i], "r");
        if (fptr == NULL) exit(1);
        size_t b_size = 0;
        int line_number = 0;

        while (getline(&line_v, &b_size, fptr) != -1) {
            line_number++;
            Student *ns = malloc(sizeof(Student));
            Student *os = NULL;

            int result = sscanf(line_v, "%s %s %s", ns->first_name, ns->last_name, ns->grades[0]); 
            if (result != 3 || parse_grade(ns->grades[0]) == -1) {
                free(ns);
                fprintf(stderr, "Błąd pliku \"%s\", Pominięto wiersz ", argv[i]);
                fprintf(stderr, "%d: %s\n", line_number, strtok(line_v, "\n"));
                continue;
            }

            to_capital(&ns->first_name[0]);
            to_capital(&ns->last_name[0]);
            ns->grades_len = 1;

            int exists = 0;
            for (j=0; j<group_len; j++) if (student_cmp(&group[j], &ns) == 0) { 
                exists = 1; 
                os = group[j]; 
                break; 
            }

            if (exists && os->grades_len == 30) {
                fprintf(
                    stderr,
                    "Błąd, przekroczono dozwoloną liczbę ocen dla: \"%s %s\"\n",
                    os->first_name,
                    os->last_name
                );
                exit(1);
            }
            else if (exists) {
                strcpy(os->grades[os->grades_len], ns->grades[0]);
                os->grades_len++;
                free(ns);
            } else {
                if (group_size <= group_len) {
                    group_size += 8;
                    group = realloc(group, sizeof(Student)*(group_size));
                }
                group[group_len] = ns;
                group_len++;
            }
        }
        fclose(fptr);    
    }

    qsort(group, group_len, sizeof(struct student*), student_cmp);
    float total_sum = 0;
    int total_grades = 0;

    for (i=0; i<group_len; i++) {
        Student *s = group[i];
        float student_sum = 0;
        fprintf(stdout, "%s %s: ", s->first_name, s->last_name);

        for (j=0; j<s->grades_len; j++) {
            printf("%s ", s->grades[j]);
            student_sum += parse_grade(s->grades[j]);
        }
        printf("(%.2f)\n", student_sum/s->grades_len);
        total_sum += student_sum;
        total_grades += s->grades_len;
    }
    printf("Średnia grupy: (%.2f)\n", total_sum/total_grades);
}
