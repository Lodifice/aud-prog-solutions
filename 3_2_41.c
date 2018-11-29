#include <stdio.h>
#include <stdlib.h>

typedef struct element *list;
struct element {
    int value;
    list next;
};

// a) iterativ
int sum_it(list l) {
    int sum = 0;
    while (l != NULL) {
        sum = sum + l->value;
        l = l->next;
    }
    return sum;
}

// a) rekursiv
int sum_rec(list l) {
    // Basisfall: leere Liste
    if (l == NULL) {
        return 0;
    }
    // Zusammengesetzter Fall: Element + Restliste
    return l->value + sum_rec(l->next);
}

// b) iterativ
void rmEvens_it(list *l) {
    while (*l != NULL) {
        if ((*l)->value % 2 == 0) {
            list temp = *l;
            (*l) = (*l)->next;
            free(temp);
        } else {
            l = &(*l)->next;
        }
    }
}

// b) rekursiv
void rmEvens_rec(list *l) {
    if (*l == NULL) {
        return;
    }
    if ((*l)->value % 2 == 0) {
        *l = (*l)->next;
    } else {
        l = &(*l)->next;
    }
    rmEvens_rec(l);
}

// Ausgabe
int main(void) {
    // lp = [1,2,3,4,5,6,7,8,9,10]
    list lp = malloc(sizeof *lp);
    list cur = lp;
    for (int i = 0; i < 10; ++i) {
        cur->value = i;
        cur->next = malloc(sizeof *cur);
        cur = cur->next;
    }
    cur->value = 10;
    cur->next = NULL;

    // lp und Produkte
    for (cur = lp; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->value);
    }
    printf("sum_it(lp) = %d\n", sum_it(lp));
    printf("sum_rec(lp) = %d\n", sum_rec(lp));

    // lp nach rmEvens (iterativ)
    rmEvens_it(&lp);
    for (cur = lp; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->value);
    }

    // lp nach rmEvens (rekursiv)
    lp->value = 0; lp->next->next->next->value = 6; // ein paar neue zu löschende Elemente
    rmEvens_rec(&lp);
    for (cur = lp; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->value);
    }

    return 0;
}
