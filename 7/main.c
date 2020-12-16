#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ERR_FOPEN "An error occurred while opening the file"

struct student {
    char first_name[30];
    char last_name[30];
    char grades[30][5];
    int grades_len;
};

void to_capital(char *str) {
    int i;
    str[0] = toupper(str[0]);
    for (i=1; i < strlen(str); i++) str[i] = tolower(str[i]);
}

int parse_grade(char *x) {
    return 0;
}

int student_cmp(const void *_a, const void *_b) {
    int result;
    struct student *a = (struct student*)_a;
    struct student *b = (struct student*)_b;
    //printf("%s %s \t %s %s \n", a->first_name, a->last_name, b->first_name, b->last_name);
    result = strcmp(a->first_name, b->first_name);
    printf("%d\n", result);
    //if (result != 0) return result;
    //result = strcmp(a->last_name, b->last_name);
    return result;
}

int main(int argc, char *argv[]) {
    struct student *group[30];
    int group_len = 0;
    char *line = NULL;

    int i;
    int j;

    for (i=1; i<argc; i++) {
        FILE* fptr = fopen(argv[i], "r");
        if (fptr == NULL) exit(1);
        size_t b_size = 0;

        while (getline(&line, &b_size, fptr) != -1) {
            struct student *ns = malloc(sizeof(struct student));
            struct student *os = NULL;
            sscanf(line, "%s %s %s", ns->first_name, ns->last_name, ns->grades[0]);
            to_capital(&ns->first_name[0]);
            to_capital(&ns->last_name[0]);
            ns->grades_len = 1;
            //printf("%s %s\n", ns->first_name, ns->last_name);

            int exists = 0;
            for (j=0; j<group_len; j++)
                if(student_cmp(group[j], ns) == 0) { exists = 1; os = group[j]; break; }

            if (exists) {
                strcpy(os->grades[os->grades_len], ns->grades[0]);
                os->grades_len++;
                free(ns);
            } else {
                group[group_len] = ns;
                group_len++;
            }
        }
        fclose(fptr);    
    }
    
    qsort(group, group_len, sizeof(struct student*), student_cmp);
    
    for (i=0; i<group_len; i++) {
        fprintf(stdout, "%s %s ", group[i]->first_name, group[i]->last_name);
        for (j=0; j<group[i]->grades_len; j++) {
            printf("%s, ", &group[i]->grades[j][0]);
        }
        printf("\n");
    }
    //fprintf(stdout, "%c", EOF);

}
