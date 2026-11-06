#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Element* Position;

typedef struct _Element {
    int broj;
    Position next;
} Element;

Position createElement(int broj)
{
    Position novi = (Position)malloc(sizeof(Element));

    if (novi == NULL)
        return NULL;

    novi->broj = broj;
    novi->next = NULL;

    return novi;
}

int push(Position Head, int broj)
{
    Position novi = createElement(broj);

    if (novi == NULL)
        return 0;

    novi->next = Head->next;
    Head->next = novi;

    return 1;
}

int pop(Position Head, int* broj)
{
    Position temp = Head->next;

    if (temp == NULL)
        return 0;

    *broj = temp->broj;
    Head->next = temp->next;

    free(temp);

    return 1;
}

int main()
{
    FILE* fp = fopen("izraz.txt", "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return 1;
    }

    Element Head;
    Head.next = NULL;

    char izraz[100];
    int a, b, broj;

    while (fscanf(fp, "%s", izraz) == 1) {

        if (sscanf(izraz, "%d", &broj) == 1) {
            push(&Head, broj);
        }
        else {
            pop(&Head, &b);
            pop(&Head, &a);

            switch (izraz[0]) {
            case '+':
                broj = a + b;
                break;

            case '-':
                broj = a - b;
                break;

            case '*':
                broj = a * b;
                break;

            case '/':
                broj = a / b;
                break;
            }

            push(&Head, broj);
        }
    }

    pop(&Head, &broj);

    printf("Rezultat je: %d\n", broj);

    fclose(fp);

    return 0;
}