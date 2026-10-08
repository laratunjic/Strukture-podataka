#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[30];
    char prezime[30];
    int bodovi;
} _student;

int main() {
    FILE* fp;
    _student* studenti;
    int n = 0, i;
    int max_br_bodova = 30;
    float relativni;

    fp = fopen("dat.txt", "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    while (!feof(fp))
        if (fgetc(fp) == '\n')
            n++;

    studenti = malloc(n * sizeof(_student));

    if (studenti == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        fclose(fp);
        return 1;
    }

    rewind(fp);

    for (i = 0; i < n; i++)
        fscanf(fp, "%s %s %d",
            studenti[i].ime,
            studenti[i].prezime,
            &studenti[i].bodovi);

    for (i = 0; i < n; i++) {
        relativni = (float)studenti[i].bodovi / max_br_bodova * 100;

        printf("%s %s - %d bodova - %.2f%%\n",
            studenti[i].ime,
            studenti[i].prezime,
            studenti[i].bodovi,
            relativni);
    }

    free(studenti);
    fclose(fp);

    return 0;
}