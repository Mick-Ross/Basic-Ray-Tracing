#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

typedef struct pt {
    int x;
    int y;
    LIST_ENTRY(pt) pointers;
} point;

LIST_HEAD(pointsList, pt);

void setPoint(point* point, int x1, int y1) {
    point->x = x1;
    point->y = y1;
}

int main() {
    
    point *p1, *p2, *p3;
    point *p;

    p1 = malloc(sizeof(point));
    p2 = malloc(sizeof(point));
    p3 = malloc(sizeof(point));
    setPoint(p1, 0, 0);
    setPoint(p2, 3, 7);
    setPoint(p3, 4, 2);

    struct pointsList head;

    LIST_INIT(&head);
    LIST_INSERT_HEAD(&head, p1, pointers);
    LIST_INSERT_HEAD(&head, p2, pointers);
    LIST_INSERT_HEAD(&head, p3, pointers);

    LIST_FOREACH(p, &head, pointers) {
        printf("%i\n", p->x);
    }

    free(p1);
    free(p2);
    free(p3);

    return 0;
}