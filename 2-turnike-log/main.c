#include "stdlib.h"
#include "stdio.h"
#include "string.h"
struct Date
{
    int hour;
    int min;
};
struct LogEntry
{
    struct Date date;
    int no;
    char name[32];
    char surname[32];
};
void assignNo(struct LogEntry *ptr, char *lastptr)
{
    ptr->no = atoi(lastptr);
}
void assignName(struct LogEntry *ptr, char *lastptr)
{
    strcpy(ptr->name, lastptr);
}
void assignSurname(struct LogEntry *ptr, char *lastptr)
{

    strcpy(ptr->surname, lastptr);
}

void assignHour(struct LogEntry *ptr, char *lastptr)
{
    ptr->date.hour = atoi(lastptr);
}

void assignMin(struct LogEntry *ptr, char *lastptr)
{
    ptr->date.min = atoi(lastptr);
}
int main(int argc, char **argv)
{
    int DEBUG = 0;
    if (argc > 1)
    {
        DEBUG = 1;
    }
    char input[256];
    if (DEBUG)
    {
        strcpy(input, "150202175-Siber-Ninja-8-5");
    }
    else
    {
        fgets(input, 256, stdin);
        input[strlen(input) - 1] = '\0';
    }
    printf("RAW INPUT LOG=|%s|\n", input);

    // parsing

    char *last_ptr = input;
    printf("KEYWORDS:\n");
    last_ptr = strtok(last_ptr, "-");
    int i = 0;
    struct LogEntry entry;
    while (last_ptr != NULL)
    {
        switch (i)
        {
        case 0:
            // no
            assignNo(&entry, last_ptr);
            break;
        case 1:
            assignName(&entry, last_ptr);
            // name
            break;
        case 2:
            assignSurname(&entry, last_ptr);
            // surname
            break;

        case 3:
            // hour
            assignHour(&entry, last_ptr);
            break;
        case 4:
            // min
            assignMin(&entry, last_ptr);
            break;
        }
        printf("|%s|\n", last_ptr);
        last_ptr = strtok(NULL, "-");
        i++;
    }
    char output[256];
    sprintf(output, "[%02d:%02d] Giren: %.3s | No: %d", entry.date.hour, entry.date.min, entry.name, entry.no);
    fputs(output, stdout);
}