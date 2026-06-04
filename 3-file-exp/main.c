#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#define FILE_PATH "./transactions.csv"
#define BYTES_PER_COLUMN 64
#define MAX_COLUMNS 10
struct ApplicationMemory
{
	char *row_data;
	char *column_names;
	int column_count;
	int row_count;
};
void printStringArray(char *pointer)
{
	int i = 0;

	while (1)
	{
		if (pointer[0] == '\0')
		{
			break;
		}

		printf("%d: %s\n", i, pointer);
		pointer = pointer + BYTES_PER_COLUMN;
		i++;
	}
}
int loadFile(FILE *stream, struct ApplicationMemory *app)
{
	fseek(stream, 0, SEEK_SET);
	app->column_names = malloc(BYTES_PER_COLUMN * MAX_COLUMNS);
	char *buffer = malloc(BYTES_PER_COLUMN * MAX_COLUMNS);
	if (!buffer)
	{
		exit(1);
	}
	if (!app->column_names)
	{
		exit(1);
	}
	fgets(buffer, BYTES_PER_COLUMN * MAX_COLUMNS, stream);
	char *reader = buffer;
	for (int i = 0; i < MAX_COLUMNS; i++)
	{
		reader = strtok(i == 0 ? reader : NULL, ",");
		if (!reader)
		{
			app->column_count = i;
			break;
		}
		reader[strcspn(reader, "\n")] = '\0';
		strcpy(app->column_names + BYTES_PER_COLUMN * i, reader);
	}
	printf("Found columns in %s:\n", FILE_PATH);
	printStringArray(app->column_names);
	int row = 0;
	memset(buffer, 0, BYTES_PER_COLUMN * MAX_COLUMNS);
	app->row_data = malloc(BYTES_PER_COLUMN * MAX_COLUMNS);
	while (buffer)
	{
		memset(buffer, 0, BYTES_PER_COLUMN * MAX_COLUMNS);
		fgets(buffer, MAX_COLUMNS * BYTES_PER_COLUMN, stream);
		if (strcmp(buffer, "") == 0)
		{
			break;
		}
		row++;
		app->row_count = row;
		app->row_data = realloc(app->row_data, row * MAX_COLUMNS * BYTES_PER_COLUMN);
		char *reader = buffer;
		for (int i = 0; i < app->column_count; i++)
		{
			reader = strtok(i == 0 ? buffer : NULL, ",");

			reader[strcspn(reader, "\n")] = '\0';
			strcpy(app->row_data + (row - 1) * BYTES_PER_COLUMN * app->column_count + i * BYTES_PER_COLUMN, reader);
		}
	}
	printf("Loaded %d rows, total size: %d bytes.", app->row_count, app->row_count * app->column_count * BYTES_PER_COLUMN);
	return 0;
}
void cleanBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
	}
}
char *getColumnNameFromIndex(struct ApplicationMemory *app, int index)
{
	if (index + 1 > app->column_count)
	{
		return NULL;
	}
	return app->column_names + index * BYTES_PER_COLUMN;
}
void printEntry(struct ApplicationMemory *app, char *entry)
{
	printf("|");
	for (int i = 0; i < app->column_count; i++)
	{
		printf("%s|", entry + i * BYTES_PER_COLUMN);
	}
}
void mainLoop(FILE *stream, struct ApplicationMemory *app)
{
	int RUNNING = 1;
	int result_count = 0;
	char *results = malloc(app->column_count * BYTES_PER_COLUMN);
	while (RUNNING)
	{
		printf("\n\n");
		printf("[0]: Exit\n");
		for (int i = 0; i < app->column_count; i++)
		{
			printf("[%d]: Search in column '%s'\n", i + 1, app->column_names + i * BYTES_PER_COLUMN);
		}
		int ACTION_KEY;
		printf("\nSelect action: ");
		scanf("%d", &ACTION_KEY);
		cleanBuffer();
		if (ACTION_KEY == 0)
		{
			printf("Exiting...\n");
			RUNNING = 0;
			return;
		}
		int search_column = ACTION_KEY - 1;
		char search_kwd[BYTES_PER_COLUMN];
		printf("Search in '%s': ", app->column_names + search_column * BYTES_PER_COLUMN);
		fgets(search_kwd, BYTES_PER_COLUMN, stdin);

		// search
		search_kwd[strcspn(search_kwd, "\n")] = '\0';
		int prefix_index = strcspn(search_kwd, "\%");
		char *prefix_exists = strchr(search_kwd, '%');
		printf("\nSearching: %d|%s|\n", prefix_index, search_kwd);
		search_kwd[strcspn(search_kwd, "\%")] = '\0';
		result_count = 0;
		free(results);
		results = malloc(app->column_count * BYTES_PER_COLUMN);
		for (int row = 0; row < app->row_count; row++)
		{
			char *row_data = app->row_data + row * BYTES_PER_COLUMN * app->column_count;
			char *column_data = row_data + search_column * BYTES_PER_COLUMN;
			if (prefix_exists == NULL ? (strcmp(search_kwd, column_data) == 0) : (memcmp(search_kwd, column_data, prefix_index) * sizeof(char)) == 0)
			{
				memcpy(results + result_count * app->column_count * BYTES_PER_COLUMN, row_data, app->column_count * BYTES_PER_COLUMN);
				result_count += 1;
				results = realloc(results, (result_count + 1) * app->column_count * BYTES_PER_COLUMN);
			}
		}
		printf("Found %d results.", result_count);
		for (int i = 0; i < 25; i++)
		{
			if (i + 1 > result_count)
			{
				break;
			}
			printf("\n[%d]:", i);
			printEntry(app, results + i * BYTES_PER_COLUMN * app->column_count);
			printf("\n");
		}
	}
}
int main(int argc, char **argv)
{
	int DEBUG = 0;
	if (argc > 1 && strcmp(argv[1], "--dbg") == 0)
	{
		DEBUG = 1;
	}
	struct ApplicationMemory *app = malloc(sizeof(struct ApplicationMemory));
	FILE *dosya = fopen(FILE_PATH, "r");
	if (!dosya)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	loadFile(dosya, app);
	mainLoop(dosya, app);
	return 0;
}