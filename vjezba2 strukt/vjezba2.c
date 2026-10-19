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
    scanf("%29s %29s %d", newPerson->name,
        newPerson->lastN, &newPerson->year);

    insertAfter(Head, newPerson);

    return 1;
}

int printlist(Position p) {
    p = p->next;

    while (p != NULL) {
        printf("%s %s %d\n",
            p->name, p->lastN, p->year);

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
    scanf("%29s %29s %d", newPerson->name,
        newPerson->lastN, &newPerson->year);

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

    while (p->next != NULL &&
        strcmp(p->next->lastN, prezime) != 0) {
        p = p->next;
    }

    if (p->next == NULL)
        return 0;

    zaBrisanje = p->next;
    p->next = zaBrisanje->next;

    free(zaBrisanje);

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