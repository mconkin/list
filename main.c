#include <stdlib.h>
#include <stdio.h>

/**
 * Generic Node data structure.
 * Useful for storing complex structs.
 **/
struct node {
    void* data;
    struct node* prev;
    struct node* next;
};

/**
 * The list implementation here is
 * a double-linked-list.
 *
 * The user is weclome to splice the
 * list instead of using the `push()`
 * and `pop()` convenience tools.
 **/
struct list {
    struct node* head;
    struct node* tail;
    int length;
};

struct list* list_create();
int list_free(struct list*);
int list_push(struct list*, void*);
void* list_pop(struct list*);

struct list* list_create() {
    struct list* p=(struct list*)malloc(sizeof(struct list));
    p->head=0;
    p->tail=0;
    p->length=0;

    return p;
}

int list_free(struct list* l) {
    struct node* p1=l->head;
    for (int i=0; i<l->length; i++) {
        struct node* p2=p1->next;
        free(p1);
        p1=p2;
    }
    l->length=0;
}

int list_push(struct list* l, void* data) {
    struct node* p=(struct node*)malloc(sizeof(struct node));
    p->data=data;
    p->next=0;
    if (l->head == 0) {
        p->prev=0;
        l->head=p;
        l->tail=p;
    }
    else {
        p->prev=l->tail;
        l->tail->next=p;
        l->tail=p;
    }
    l->length++;
    return 0;
}

void* list_pop(struct list* l) {
    struct node* p=l->tail;
    l->tail->prev->next=0;
    l->tail=l->tail->prev;
    l->length--;
 
    void* data=p->data;
    free(p);

    return data;    
}

int list_print(struct list* l, void (*print_callback)(void*)) {
    struct node* p=l->head;
    for (int i=0; i<l->length; i++) {
        print_callback(p->data);
        p=p->next;
    }
    return 0;
}

/**
 * Example coordinates struct to test proof-of-concept
 **/
struct coordinates {
    int x;
    int y;
    int z;
};

void print_coordinates(void* p) {
    struct coordinates* c = (struct coordinates*) p;
    printf("[%d, %d, %d] ",c->x, c->y, c->z);
}

int main() {
    struct list* l=list_create();
    for (int i=0; i<10; i++) {
        struct coordinates* p=(struct coordinates*)malloc(sizeof(struct coordinates));
        p->x=i*205432+67%753;
        p->y=i*3+47%895;
        p->z=i*2345560+52%624;

        list_push(l, p);
    }
    struct coordinates* p=(struct coordinates*)list_pop(l);
    print_coordinates((void*)p);

    list_print(l, print_coordinates);
    list_free(l);
    printf("%d", l->length);

    return 0;
}
