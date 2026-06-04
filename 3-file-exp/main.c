#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#define FILE_PATH "./transactions.csv"
#define BYTES_PER_COLUMN 32
#define MAX_COLUMNS 10
struct DataRow
{
	int *fields;
};
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
		reader = strtok(i == 0 ? reader : NULL, "|");
		if (!reader)
		{
			app->column_count = i;
			break;
		}
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
			reader = strtok(i == 0 ? buffer : NULL, "|");
			strcpy(app->row_data + (row - 1) * BYTES_PER_COLUMN * app->column_count + i * BYTES_PER_COLUMN, reader);
		}
	}
	printf("Loaded %d rows, total size: %d bytes.", app->row_count, app->row_count * app->column_count * BYTES_PER_COLUMN);
	return 0;
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
	return 0;
}