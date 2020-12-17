#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "student.h"

void to_capital(char *str) {
    int i;
    str[0] = toupper(str[0]);
    for (i=1; i < strlen(str); i++) str[i] = tolower(str[i]);
}

float parse_grade(char *x) {
    float num = -1;
    sscanf(x, "%f", &num);
    num = fabs(num);
    if(strchr(x, '+')) num += 0.25;
    if(strchr(x, '-')) num -= 0.25;
    if((num>=2 && num<=5) || num==0 || num==6) return num;
    return -1;
}

int student_cmp(const void *_a, const void *_b) {
    int result;
    Student *a = *(Student**)_a;
    Student *b = *(Student**)_b;

    result = strcmp(a->first_name, b->first_name);
    if (result != 0) return result;
    result = strcmp(a->last_name, b->last_name);
    return result;
}
