#ifndef TYPE_STUDENT
#define TYPE_STUDENT

typedef struct Student {
    char first_name[30];
    char last_name[30];
    char grades[30][5];
    int grades_len;
} Student;

#endif
