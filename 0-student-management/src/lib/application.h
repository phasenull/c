typedef enum
{
    STATE_MAIN_MENU = 0,
    STATE_STUDENT_READ = 1,
    STATE_STUDENT_WRITE = 2,
    STATE_STUDENT_QUERY = 4,
    STATE_PROCESSING = 99,
} APPLICATION_STATE;
typedef struct
{
    APPLICATION_STATE state;
} ApplicationState;
const *STATE_DESCRIPTIONS[] = {
    "~/students/",
    "~/students/read",
    "~/students/%d/write",
    "~/students/query",
    "[...]"};
char *getStateDescriptionFromState(APPLICATION_STATE state)
{
    return STATE_DESCRIPTIONS[state];
}