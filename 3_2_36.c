#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree;
typedef struct node {
    int key;
    tree left;
    tree right;
} node;

// a)
// Hilfsfunktion
int count(tree t, int key) {
    if (t == NULL) {
        return 0;
    }
    int c = 0;
    if (t->key == key) {
        c = c + 1;
    }
    return c + count(t->left, key) + count(t->right, key);
}

// a)
// Funktion baz
tree baz(tree s, tree t) {
    if (s == NULL) {
        return NULL;
    }
    tree ret = malloc(sizeof *ret); // sizeof(node)
    ret->key = count(t, s->key);
    ret->left = baz(s->left, t);
    ret->right = baz(s->right, t);
    return ret;
}

// b)
int leafprod(tree t) {
    // Basisfall
    if (t == NULL) {
        return 1;
    }
    // Blatt
    if (t->left == NULL && t->right == NULL) {
        return t->key;
    }
    // Zusammengesetzter Fall
    return leafprod(t->left) * leafprod(t->right);
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

int main(void) {
    // t = 42
    //    /  \
    //   8    7
    //  /
    // 16
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

    // Einfacher Baum für a)
    struct node lookup_tree = {.key = 8, .left = NULL, .right = NULL};

    // t und leafprod(t)
    printf("t = ");
    print_tree(t);
    printf("\n");
    printf("leafprod(t) = %d\n", leafprod(t));

    // baz(t, lookup_tree)
    printf("baz(t,lookup_tree) = ");
    print_tree(baz(t, &lookup_tree)); // <- ACHTUNG:
                                      // Pointer auf baz(t,lookup_tree)
                                      // verloren ohne free!
    printf("\n");

    return 0;
}
