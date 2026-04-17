#include "stdlib.h"
typedef struct
{
    uint32_t no;
    char firstname[40];
    char lastname[40];
} Student;

typedef struct
{
    uint32_t student_no;
    uint8_t grade;
    char subject[40];
} TestResult;