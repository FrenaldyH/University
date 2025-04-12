#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#define el printf("\n")
#define ll long long
#define dd double
#define Cls system("cls")

void delay (int mili_seconds) {
    clock_t st_time  = clock();
    for(; clock() < st_time + mili_seconds;);
}

typedef struct Queue {
    int* arr;
    int size, front, end, capacity;
} Queue;

void create_queue (Queue* queue, int capacity) {
    queue->arr = (int*)malloc(capacity * sizeof(int));
    queue->front = queue->size = 0;
    queue->capacity = capacity;
    queue->end = -1;
}

bool is_emptyQ (Queue *queue) {
    return !queue->size;
}

bool is_fullQ(Queue *queue) {
    return queue->size == queue->capacity;
}

void push_backQ (Queue* queue) { Cls;
    if(is_fullQ(queue)) {
        printf("Queue is full!"), el;
        delay(1000);
        return;
    }

    int val;
    printf("Enter the value to push: ");
    scanf(" %d", &val);

    queue->end = (queue->end + 1) % queue->capacity;
    queue->arr[queue->end] = val;
    queue->size++;
}

void pop_frontQ (Queue* queue) { Cls;
    if(is_emptyQ(queue)) {
        printf("Queue is empty!"), el;
        delay(1000);
        return;
    }

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
}

void findQ (Queue* queue) { Cls;
    if(is_emptyQ(queue)) {
        printf("Queue is empty!"), el;
        delay(1000);
        return;
    }

    int val, i, idx;
    printf("Enter the value to find: ");
    scanf(" %d", &val);

    for(i = 0; i < queue->size; i++) {
        idx = (queue->front + i) % queue->capacity;
        if(!(queue->arr[idx] ^ val)) {
            printf("%d found at index %d\n", val, idx);
            delay(1000);
            return;
        }
    }
    printf("%d not found in this queue", val), el;
    delay(1000);
}

void displayQ (Queue* queue) { Cls;
    if(is_emptyQ(queue)) {
        printf("Queue is empty!"), el;
        return;
    }
    printf("Queue: ");
    for(int i = 0; i < queue->size; i++) {
        int idx = (queue->front + i) % queue->capacity;
        printf("%d ", queue->arr[idx]);
    }
    printf("\n");
    delay(1000);
}

void changeQ (Queue* queue) { Cls;
    if(is_emptyQ(queue)) {
        printf("Queue is empty!");
        return;
    }

    int idx, newval;
    do {
        Cls;
        printf("Enter the index to change (0-%d): ", queue->size - 1);
        scanf("%d", &idx); 

        if(idx < 0 || idx >= queue->size) {
            printf("Invalid index! \nPlease try again."), el;
            delay(1000);
            return;
        }
    } while(idx < 0 || idx >= queue->size);
    printf("Enter the new value: ");
    scanf(" %d", &newval);

    queue->arr[(queue->front + idx) % queue->capacity] = newval;
    printf("Value at index %d changed to %d", idx, newval), el;
    delay(1000);
}

ll totalQ (Queue* queue) {
    ll i, idx, sum = 0;
    for(i = 0; i < queue->size; i++) {
        idx = (queue->front + i) % queue->capacity;
        sum += queue->arr[idx];
    }
    return sum;
}

int maxQ (Queue* queue) {
    int i, idx, tmax = queue->arr[queue->front];
    for(i = 1; i < queue->size; i++) {
        idx = (queue->front + i) % queue->capacity;
        if(queue->arr[idx] > tmax)
            tmax = queue->arr[idx];
    }
    return tmax;
}

int minQ (Queue* queue) {
    int i, idx, tmin = queue->arr[queue->front];
    for(i = 0; i < queue->size; i++) {
        idx = (queue->front + i) % queue->capacity;
        if(queue->arr[idx] < tmin)
            tmin = queue->arr[idx];
    }
    return tmin;
}

dd avgQ (Queue* queue) {
    return (is_emptyQ(queue) ? 0 : (dd)totalQ(queue) / queue->size);
}

void clearQ (Queue* queue) {
    queue->front = queue->size = 0;
    queue->end = -1;
}

void menu (Queue* queue) {
    int chc;
    do {
        do { Cls;
            printf("===> Queue Menu: "), el;
            printf("1. Add value"), el;
            printf("2. Pop value"), el;
            printf("3. Check empty"), el;
            printf("4. Check full"), el;
            printf("5. Find value"), el;
            printf("6. Clear queue"), el;
            printf("7. Change value at certain index"), el;
            printf("8. Display queue"), el;
            printf("9. Total value"), el;
            printf("10. Minimal value"), el;
            printf("11. Maximal value"), el;
            printf("12. Average value"), el;
            printf("13. Exit"), el;
            printf("Enter your choice (1-13): ");
            scanf("%d", &chc);

            if(chc < 1 || chc > 13) {
                Cls, printf("Invalid choice! \nPlease try again"), el;
                delay(500), Cls;
            }
        } while(chc < 1 || chc > 13);

        switch (chc) {
            case 1: push_backQ(queue); break;
            case 2: pop_frontQ(queue); break;
            case 3: Cls, printf("%s\n", is_emptyQ(queue) ? "Queue is empty!" : "Queue is not empty!"); delay(1000); break;
            case 4: Cls, printf("%s\n", is_fullQ(queue) ? "Queue is full!" : "Queue is not full!"); delay(1000); break;
            case 5: findQ(queue); break;
            case 6: Cls, clearQ(queue); printf("Queue cleared successfully!\n"); delay(1000); break;
            case 7: changeQ(queue); break;
            case 8: displayQ(queue); break;
            case 9: Cls, printf("Total value: %lld\n", totalQ(queue)); delay(1000); break;
            case 10: Cls, printf(is_emptyQ(queue) ? "Queue is empty!\n" : "Minimal value: %d\n", minQ(queue)); delay(1000); break;
            case 11: Cls, printf(is_emptyQ(queue) ? "Queue is empty!\n" : "Maximal value: %d\n", maxQ(queue)); delay(1000); break;
            case 12: Cls, printf("Average value: %.2lf\n", avgQ(queue)); delay(1000); break;
            case 13: Cls, printf("Exiting...\n"); delay(1000); break;
        }
    } while(chc ^ 13);
}

int main() {
    Queue queue;
    int size;
    do {
        Cls, printf("Enter the size of the queue: ");
        scanf("%d", &size);
        if (size <= 0) {
            printf("Size must be a positive integer! Please try again.\n");
            delay(1000);
            continue;
        }
    } while (size <= 0);
    Cls, create_queue(&queue, size);
    menu(&queue);
    free(queue.arr);
    Cls;
    return 0;
}