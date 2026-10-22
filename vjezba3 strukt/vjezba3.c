#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person* Position;

typedef struct _Person {
    char name[30];
    char lastN[30];
    int year;
    Position next;
} Person;

int insertAfter(Position p, Position newP) {
    if (p == NULL || newP == NULL)
        return 0;

    newP->next = p->next;
    p->next = newP;

    return 1;
}

int insertBegin(Position Head) {
    Position newPerson;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    printf("Unesi ime, prezime i godinu rodjenja: ");
    scanf("%29s %29s %d", newPerson->name, newPerson->lastN, &newPerson->year);

    insertAfter(Head, newPerson);

    return 1;
}

int printlist(Position p) {
    p = p->next;

    while (p != NULL) {
        printf("%s %s %d\n", p->name, p->lastN, p->year);

        p = p->next;
    }

    return 1;
}

int insertEnd(Position Head) {
    Position p = Head;
    Position newPerson;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    printf("Unesi ime, prezime i godinu rodjenja: ");
    scanf("%29s %29s %d", newPerson->name, newPerson->lastN, &newPerson->year);

    newPerson->next = NULL;

    while (p->next != NULL)
        p = p->next;

    insertAfter(p, newPerson);

    return 1;
}

Position findLastname(char* prezime, Position Head) {
    Position p;

    for (p = Head->next; p != NULL; p = p->next) {
        if (strcmp(p->lastN, prezime) == 0)
            return p;
    }

    return NULL;
}

int deletePerson(char* prezime, Position Head) {
    Position p = Head;
    Position zaBrisanje;

    while (p->next != NULL && strcmp(p->next->lastN, prezime) != 0) {
        p = p->next;
    }

    if (p->next == NULL)
        return 0;

    zaBrisanje = p->next;
    p->next = zaBrisanje->next;

    free(zaBrisanje);

    return 1;
}

int insertAfterPerson(Position Head, char* prezime) {
    Position p = findLastname(prezime, Head);
    Position newPerson;

    if (p == NULL)
        return 0;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    printf("Unesi ime, prezime i godinu rodjenja: ");
    scanf("%29s %29s %d", newPerson->name, newPerson->lastN, &newPerson->year);

    insertAfter(p, newPerson);

    return 1;
}

int insertBeforePerson(Position Head, char* prezime) {
    Position p = Head;
    Position newPerson;

    while (p->next != NULL && strcmp(p->next->lastN, prezime) != 0) {
        p = p->next;
    }

    if (p->next == NULL)
        return 0;

    newPerson = (Position)malloc(sizeof(Person));

    if (newPerson == NULL)
        return 0;

    printf("Unesi ime, prezime i godinu rodjenja: ");
    scanf("%29s %29s %d", newPerson->name, newPerson->lastN, &newPerson->year);

    insertAfter(p, newPerson);

    return 1;
}

int sortList(Position Head) {
    Position p, q;
    char tempName[30];
    char tempLastN[30];
    int tempYear;

    for (p = Head->next; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (strcmp(p->lastN, q->lastN) > 0) {
                strcpy(tempName, p->name);
                strcpy(tempLastN, p->lastN);
                tempYear = p->year;

                strcpy(p->name, q->name);
                strcpy(p->lastN, q->lastN);
                p->year = q->year;

                strcpy(q->name, tempName);
                strcpy(q->lastN, tempLastN);
                q->year = tempYear;
            }
        }
    }

    return 1;
}

int writeToFile(Position Head) {
    FILE* fp;
    Position p;

    fp = fopen("osobe.txt", "w");

    if (fp == NULL)
        return 0;

    for (p = Head->next; p != NULL; p = p->next) {
        fprintf(fp, "%s %s %d\n", p->name, p->lastN, p->year);
    }

    fclose(fp);

    return 1;
}

int readFromFile(Position Head) {
    FILE* fp;
    Position p = Head;
    Position newPerson;

    fp = fopen("osobe.txt", "r");

    if (fp == NULL)
        return 0;

    while (p->next != NULL)
        p = p->next;

    while (1) {
        newPerson = (Position)malloc(sizeof(Person));

        if (newPerson == NULL) {
            fclose(fp);
            return 0;
        }

        if (fscanf(fp, "%29s %29s %d", newPerson->name, newPerson->lastN, &newPerson->year) != 3) {
            free(newPerson);
            break;
        }

        newPerson->next = NULL;
        insertAfter(p, newPerson);
        p = newPerson;
    }

    fclose(fp);

    return 1;
}

int main(void) {
    Person Head = { "", "", 0, NULL };
    int izbor;
    char prezime[30];
    Position pronadjena;

    do {
        printf("\n1 - Dodaj na pocetak");
        printf("\n2 - Ispisi listu");
        printf("\n3 - Dodaj na kraj");
        printf("\n4 - Pronadji po prezimenu");
        printf("\n5 - Obrisi po prezimenu");
        printf("\n6 - Dodaj iza odredjene osobe");
        printf("\n7 - Dodaj ispred odredjene osobe");
        printf("\n8 - Sortiraj po prezimenu");
        printf("\n9 - Upisi listu u datoteku");
        printf("\n10 - Procitaj listu iz datoteke");
        printf("\n0 - Izlaz");
        printf("\nOdabir: ");

        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            insertBegin(&Head);
            break;

        case 2:
            printlist(&Head);
            break;

        case 3:
            insertEnd(&Head);
            break;

        case 4:
            printf("Unesi prezime: ");
            scanf("%29s", prezime);

            pronadjena = findLastname(prezime, &Head);

            if (pronadjena != NULL) {
                printf("%s %s %d\n",
                    pronadjena->name,
                    pronadjena->lastN,
                    pronadjena->year);
            }
            else {
                printf("Osoba nije pronadjena.\n");
            }
            break;

        case 5:
            printf("Unesi prezime za brisanje: ");
            scanf("%29s", prezime);

            if (deletePerson(prezime, &Head))
                printf("Osoba je obrisana.\n");
            else
                printf("Osoba nije pronadjena.\n");
            break;

        case 6:
            printf("Iza kojeg prezimena zelis dodati osobu: ");
            scanf("%29s", prezime);

            if (insertAfterPerson(&Head, prezime))
                printf("Osoba je dodana.\n");
            else
                printf("Osoba nije pronadjena ili nema memorije.\n");
            break;

        case 7:
            printf("Ispred kojeg prezimena zelis dodati osobu: ");
            scanf("%29s", prezime);

            if (insertBeforePerson(&Head, prezime))
                printf("Osoba je dodana.\n");
            else
                printf("Osoba nije pronadjena ili nema memorije.\n");
            break;

        case 8:
            sortList(&Head);
            printf("Lista je sortirana.\n");
            break;

        case 9:
            if (writeToFile(&Head))
                printf("Lista je upisana u datoteku.\n");
            else
                printf("Greska pri otvaranju datoteke.\n");
            break;

        case 10:
            if (readFromFile(&Head))
                printf("Lista je procitana iz datoteke.\n");
            else
                printf("Greska pri citanju datoteke ili alokaciji memorije.\n");
            break;

        case 0:
            break;

        default:
            printf("Pogresan odabir.\n");
        }

    } while (izbor != 0);

    while (Head.next != NULL) {
        Position p = Head.next;
        Head.next = p->next;
        free(p);
    }

    return 0;
}