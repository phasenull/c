#include "stdlib.h"
#include "stdio.h"
#include "string.h"
struct Date
{
    int year;
    int month;
    int day;
};
struct RadiatedPacket
{
    struct Date created_at;
    float x_koor;
    float y_koor;
    char sektor_adi[64];
};
char delimeters[] = "-*#! ";
int main(int argc, char **argv)
{
    int DEBUG = 0;
    if (argc > 1)
    {
        DEBUG = 1;
    }
    struct RadiatedPacket gelen_veriler;
    memset(&gelen_veriler, 0, sizeof(struct RadiatedPacket));
    char input[256];
    if (!DEBUG)
    {
        printf("Radyasyonlu mesajı giriniz: ");
        fgets(input, 256, stdin);
        input[strlen(input) - 1] = '\0';
    }
    else
    {
        strcpy(input, "!!12.04.2026**ANOMALI##Sektor_Alfa**45.3216!!89.1239##");
    }
    printf("Girilen metin: |%s|\n", input);
    char *result = strstr(input, "ANOMALI");
    if (result == NULL)
    {
        printf("Sinyal temiz, isleme gerek yok.\n");
        return 0;
    }
    else
    {
        printf("RESULT=%s\n", result);
    }

    char *last_read = strtok(input, delimeters);
    printf("KEYWORDS:\n");
    char keywords[64][64];
    int i = 0;
    while (last_read != NULL)
    {
        strcpy(keywords[i], last_read);
        printf("|%s|\n", last_read);
        last_read = strtok(NULL, delimeters);
        i++;
    }
    sscanf(keywords[0], "%d.%d.%d", &gelen_veriler.created_at.day, &gelen_veriler.created_at.month, &gelen_veriler.created_at.year);
    strcpy(gelen_veriler.sektor_adi, keywords[2]);
    gelen_veriler.x_koor = atof(keywords[3]);
    gelen_veriler.y_koor = atof(keywords[4]);
    printf("DATE=%d %d %d\n", gelen_veriler.created_at.day, gelen_veriler.created_at.month, gelen_veriler.created_at.year);
    printf("|%-13s|", "Tarih");
    printf("%-13s|", "Sektor Adi");
    printf("%-13s|", "X Koor");
    printf("%-13s|", "Y Koor");
    char formatted_tarih[32];
    sprintf(formatted_tarih, "%02d.%02d.%04d", gelen_veriler.created_at.day, gelen_veriler.created_at.month, gelen_veriler.created_at.year);
    printf("\n|%-13s|", formatted_tarih);
    printf("%-13s|", gelen_veriler.sektor_adi);
    printf("%-13.2f|", gelen_veriler.x_koor);
    printf("%-13.2f|", gelen_veriler.y_koor);
}