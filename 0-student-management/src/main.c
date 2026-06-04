#include "stdio.h"
#include "lib/application.h"
typedef enum
{
    ACTION_RETURN = 0,
    ACTION_STUDENT_READ = 1,
    ACTION_STUDENT_WRITE = 2,
    ACTION_STUDENT_QUERY = 3,
} ACTIONS;

char *DESCRIPTIONS[] = {
    "Go back",
    "Read student",
    "Write student",
    "Query student"};
char *getActionDescriptionFromAction(ACTIONS action)
{
    return DESCRIPTIONS[action];
}
void printActionsList()
{
    for (int i = 0; i < 4; i++)
    {
        printf("[%d]: %s\n", DESCRIPTIONS[i]);
    }
}
int main()
{
    ApplicationState state = {
        .state = STATE_MAIN_MENU};

    while (1)
    {
        int action;
        printf(getStateDescriptionFromState(state.state));
        printf("> ");
        scanf("%d", &action);
    }
}