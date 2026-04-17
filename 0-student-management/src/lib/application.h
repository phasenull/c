typedef enum
{
    MAIN_MENU = 0,
    STUDENT_READ = 1,
    STUDENT_WRITE = 2,
    STUDENT_QUERY = 4,
    PROCESSING = 99,
} APPLICATION_STATE;
typedef struct
{
    APPLICATION_STATE state;
    void *memory;
} ApplicationState;