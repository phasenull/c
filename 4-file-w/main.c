#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#define MAX_ROW_LENGTH 256
#define FILE_PATH "./scores.csv"
struct User
{
    int id;
    int score;
    char name[32];
    char surname[32];
};
struct ApplicationMemory
{
    struct User *user_list;
    int user_count;
    FILE *stream;
};
void clearBuffer()
{
    char c;
    while ((c = getchar()) && c != '\n' && c != EOF)
    {
    }
}
void reallocAppContext(struct ApplicationMemory *app)
{
    // memory errors are ignored.
    app->user_list = realloc(app->user_list, sizeof(struct User) * (app->user_count + 1));
}
void createFileIfNotExists()
{
    FILE *stream = fopen(FILE_PATH, "a");
    if (!stream)
    {
        printf("File open(r) failed.");
        exit(1);
    }
    fclose(stream);
}
void assignRowToUser(char *row, struct User *user)
{
    int read_index = 0;
    while (row)
    {
        row = strtok(read_index == 0 ? row : NULL, ",");
        switch (read_index)
        {
        case 0:
            user->id = atoi(row);
            break;

        case 1:
            user->score = atoi(row);
            break;

        case 2:
            strcpy(user->name, row);
            break;

        case 3:
            strcpy(user->surname, row);
            break;
        }
        read_index++;
    }
}
char *convertToRow(struct User user)
{
    char *buffer = malloc(MAX_ROW_LENGTH);
    sprintf(buffer, "%d,%d,%s,%s", user.id, user.score, user.name, user.surname);
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}
void loadCSV(struct ApplicationMemory *app)
{
    fseek(app->stream, 0, SEEK_SET);
    struct User *buffer = malloc(sizeof(struct User));
    char *read_buffer = malloc(MAX_ROW_LENGTH);
    memset(read_buffer, 0, MAX_ROW_LENGTH);
    while (fgets(read_buffer, MAX_ROW_LENGTH, app->stream) != NULL)
    {
        fgets(read_buffer, MAX_ROW_LENGTH, app->stream);
        printf("READ: %s\n", read_buffer);
        if (strcmp(read_buffer, "") == 0)
            return;
        assignRowToUser(read_buffer, buffer);
        memcpy(app->user_list + (app->user_count), buffer, sizeof(struct User));
        app->user_count++;
        reallocAppContext(app);
    }
}
void upsertUser(struct ApplicationMemory *app, struct User user)
{
    fseek(app->stream, 0, SEEK_SET);
    char *temp = malloc(app->user_count * MAX_ROW_LENGTH);
    temp[0] = '\0';
    int is_update = 0;
    for (int i = 0; i < app->user_count; i++)
    {
        struct User *buffer = &app->user_list[i];
        if (buffer->id == user.id)
        {
            is_update = 1;
            app->user_list[i] = user;
            printf("Updated user: %s", convertToRow(*(struct User *)(app->user_list + i)));
        }
    }
    if (!is_update)
    {
        app->user_list[app->user_count] = user;
        app->user_count++;
        reallocAppContext(app);
    }

    for (int i = 0; i < app->user_count; i++)
    {
        struct User *buffer = &app->user_list[i];
        strcat(temp, convertToRow(*buffer));
        strcat(temp, "\n");
    }
    printf("data:%s\n", temp);
    fputs(temp, app->stream);
}
void mainloop(struct ApplicationMemory *app)
{
    int IS_RUNNING = 1;
    while (IS_RUNNING)
    {
        printf("\n[0]: Exit\n");
        printf("[1]: Add user\n");
        printf("[2]: Update user\n");
        printf("[3]: Leaderboard\n");
        int ACTION_ID = 0;
        printf("Select an action:");
        scanf("%d", &ACTION_ID);
        clearBuffer();
        struct User *buffer = malloc(sizeof(struct User));
        switch (ACTION_ID)
        {
        case 0:
            IS_RUNNING = 0;
            break;
        case 1:
            printf("Add user | format: id,score,name,surname\n");
            scanf("%d,%d,%s,%s", &buffer->id, &buffer->score, buffer->name, buffer->surname);
            buffer->surname[strcspn(buffer->surname, "\n")] = '\0';
            clearBuffer();
            printf("User Input: %s\n", convertToRow(*buffer));
            upsertUser(app, *buffer);
            break;
        case 3:
            for (int i = 0; i < app->user_count; i++)
            {
                printf("\n[#%d]: %s", i, convertToRow(*(app->user_list + i)));
            }
            break;
        default:
            break;
        }
    }
    return;
}
int main(int argc, char **argv)
{
    struct ApplicationMemory *app = malloc(sizeof(struct ApplicationMemory));
    createFileIfNotExists();
    FILE *stream = fopen(FILE_PATH, "r+");
    if (!stream)
    {
        printf("File open(r+) failed.");
        exit(1);
    }
    app->stream = stream;
    app->user_count = 0;
    app->user_list = malloc(sizeof(struct User));
    int DEBUG = 0;
    if (argc > 1 && strcmp(argv[1], "--dbg") == 0)
    {
        DEBUG = 1;
    }
    loadCSV(app);
    printf("Loaded %d users!\n", app->user_count);
    mainloop(app);
    fclose(app->stream);
}