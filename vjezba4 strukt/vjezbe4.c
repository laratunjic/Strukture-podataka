#include <stdio.h>
#include <stdlib.h>

typedef struct _Polinom* Position;

typedef struct _Polinom {
    int koef;
    int eksponent;
    Position next;
} Polinom;

Position createElement(int koef, int eksponent)
{
    Position novi = (Position)malloc(sizeof(Polinom));

    if (novi == NULL)
        return NULL;

    novi->koef = koef;
    novi->eksponent = eksponent;
    novi->next = NULL;

    return novi;
}

void insertSorted(Position head, int koef, int eksponent)
{
    Position p = head;
    Position novi;

    while (p->next != NULL && p->next->eksponent > eksponent)
        p = p->next;

    if (p->next != NULL && p->next->eksponent == eksponent) {
        p->next->koef += koef;
        return;
    }

    novi = createElement(koef, eksponent);

    if (novi == NULL)
        return;

    novi->next = p->next;
    p->next = novi;
}

void readPolynomial(FILE* fp, Position head)
{
    char red[256];
    char* p;
    int koef, eksponent, procitano;

    if (fgets(red, sizeof(red), fp) == NULL)
        return;

    p = red;

    while (sscanf(p, "%d %d%n", &koef, &eksponent, &procitano) == 2) {
        insertSorted(head, koef, eksponent);
        p += procitano;
    }
}

void printPolynomial(Position head)
{
    Position p = head->next;

    while (p != NULL) {
        if (p->koef != 0)
            printf("%dx^%d ", p->koef, p->eksponent);

        p = p->next;
    }

    printf("\n");
}

void addPolynomial(Position rezultat, Position p, Position q)
{
    p = p->next;
    q = q->next;

    while (p != NULL) {
        insertSorted(rezultat, p->koef, p->eksponent);
        p = p->next;
    }

    while (q != NULL) {
        insertSorted(rezultat, q->koef, q->eksponent);
        q = q->next;
    }
}

void multiplyPolynomial(Position rezultat, Position p, Position q)
{
    Position a = p->next;
    Position b;

    while (a != NULL) {
        b = q->next;

        while (b != NULL) {
            insertSorted(rezultat, a->koef * b->koef, a->eksponent + b->eksponent);

            b = b->next;
        }

        a = a->next;
    }
}

void freePolynomial(Position head)
{
    Position p;

    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}

int main()
{
    FILE* fp;
    Polinom P = { 0, 0, NULL };
    Polinom Q = { 0, 0, NULL };
    Polinom zbroj = { 0, 0, NULL };
    Polinom umnozak = { 0, 0, NULL };

    fp = fopen("polinomi.txt", "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return 1;
    }

    readPolynomial(fp, &P);
    readPolynomial(fp, &Q);

    fclose(fp);

    printf("Prvi polinom: ");
    printPolynomial(&P);

    printf("Drugi polinom: ");
    printPolynomial(&Q);

    addPolynomial(&zbroj, &P, &Q);

    printf("Zbroj polinoma: ");
    printPolynomial(&zbroj);

    multiplyPolynomial(&umnozak, &P, &Q);

    printf("Umnozak polinoma: ");
    printPolynomial(&umnozak);

    freePolynomial(P.next);
    freePolynomial(Q.next);
    freePolynomial(zbroj.next);
    freePolynomial(umnozak.next);

    return 0;
}