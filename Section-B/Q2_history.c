#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Page {
    char url[51];
    struct Page *prev;
    struct Page *next;
} Page;

Page *current = NULL;

void free_forward(Page *node) {
    if (node == NULL) return;
    
    Page *walker = node->next;
    while (walker != NULL) {
        Page *temp = walker->next;
        free(walker);
        walker = temp;
    }
    node->next = NULL;
}

void visit(const char *url) {
    free_forward(current);
    
    Page *p = (Page *)malloc(sizeof(Page));
    strcpy(p->url, url);
    p->prev = current;
    p->next = NULL;

    if (current != NULL) {
        current->next = p;
    }
    current = p;
}

void back(void) {
    if (current == NULL || current->prev == NULL) {
        printf("NO BACK\n");
    } else {
        current = current->prev;
        printf("%s\n", current->url);
    }
}

void forward(void) {
    if (current == NULL || current->next == NULL) {
        printf("NO FORWARD\n");
    } else {
        current = current->next;
        printf("%s\n", current->url);
    }
}

void print_current(void) {
    if (current == NULL) {
        printf("NONE\n");
    } else {
        printf("%s\n", current->url);
    }
}

void free_all_history(void) {
    if (current == NULL) return;

    while (current->prev != NULL) {
        current = current->prev;
    }

    while (current != NULL) {
        Page *temp = current->next;
        free(current);
        current = temp;
    }
}

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) return 0;

    for (int i = 0; i < q; i++) {
        char cmd[20];
        scanf("%s", cmd);

        if (strcmp(cmd, "VISIT") == 0) {
            char url[51];
            scanf("%s", url);
            visit(url);
        } else if (strcmp(cmd, "BACK") == 0) {
            back();
        } else if (strcmp(cmd, "FORWARD") == 0) {
            forward();
        } else if (strcmp(cmd, "CURRENT") == 0) {
            print_current();
        }
    }

    free_all_history();
    return 0;
}