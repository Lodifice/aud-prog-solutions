#include <stdio.h>
#include <stdlib.h>

typedef struct element *list;
typedef struct element {
    int value;
    list next;
} element;

typedef struct node *tree;
typedef struct node {
    int key;
    tree left;
    tree right;
} node;

// a)
int f(list l) {
    while (l != NULL && l->next != NULL) {
        int next_value = l->next->value;
        if (l->value - next_value > 1 || l->value - next_value < -1) {
            return 0;
        }
        l = l->next;
    }
    return 1;
}

// b)
void defol(tree *p) {
    if (p == NULL) {
        return;
    }
    if (*p == NULL) {
        return;
    }
    if ((*p)->left == NULL && (*p)->right == NULL) {
        free(*p);
        *p = NULL;
    } else {
        defol(&(*p)->left);
        defol(&(*p)->right);
    }
}

// Ausgabe
void print_tree(tree tree) {
    if (tree == NULL) {
        return;
    }
    printf("%d(", tree->key);
    print_tree(tree->left);
    printf(",");
    print_tree(tree->right);
    printf(")");
}

void check_b(void) {
    // t = 42
    //    /  \
    //   8    7
    //       /
    //      16
    tree t = malloc(sizeof *t);
    tree cur = t;
    t->key = 42;
    t->left = malloc(sizeof *t);
    t->left->key = 8;
    t->left->left = NULL;
    t->left->right = NULL;
    t->right = malloc(sizeof *t);
    t->right->key = 7;
    t->right->left = NULL;
    t->right->right = NULL;
    t->right->left = malloc(sizeof *t);
    t->right->left->key = 16;
    t->right->left->left = NULL;
    t->right->left->right = NULL;

    // t vor defol
    print_tree(t);
    printf("\n");

    // defol(t) -> t ohne Blätter
    defol(&t);
    print_tree(t);
    printf("\n");
}

void check_a(void) {
    // lp = [0,1,2,3,4,5,6,7,8,9,10]
    list lp = malloc(sizeof *lp);
    list cur = lp;
    for (int i = 0; i < 10; ++i) {
        cur->value = i;
        cur->next = malloc(sizeof *cur);
        cur = cur->next;
    }
    cur->value = 10;
    cur->next = NULL;

    // "korrekte" Liste -> 1
    printf("%d\n", f(lp));

    // "inkorrekte" Liste -> 0
    // [0,1,2,3,4,5,6,7,8,9,7]
    cur->value = 7;
    printf("%d\n", f(lp));
}

int main(void) {
    check_b();
    check_a();
    return 0;
}
