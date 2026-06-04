#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#define FILE_PATH "./transactions.csv"
#define BYTES_PER_COLUMN 256
#define MAX_COLUMNS 10
struct DataRow
{
	int *fields;
};
struct ApplicationMemory
{
	int *row_data;
	int *column_names;
};

int loadFile(FILE *stream, struct ApplicationMemory *app)
{
	fseek(stream, 0, SEEK_SET);
	char *read = malloc(BYTES_PER_COLUMN * MAX_COLUMNS);
	if (!read)
	{
		exit(1);
	}
	fgets(read, BYTES_PER_COLUMN * MAX_COLUMNS, stream);
	printf("Column row: %s", read);
	return 0;
}

int main(int argc, char **argv)
{
	int DEBUG = 0;
	if (argc > 1 && strcmp(argv[1], "--dbg") == 0)
	{
		DEBUG = 1;
	}
	struct ApplicationMemory *app = {0};
	FILE *dosya = fopen(FILE_PATH, "r");
	if (!dosya)
	{
		printf("Dosya acilamadi");
		exit(1);
	}
	loadFile(dosya, app);
	return 0;
}