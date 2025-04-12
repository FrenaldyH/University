#include <stdio.h>
#include <string.h>

// Shortcut
#define S 1001
#define P(x) printf(x)
#define el printf("%c", '\n')

typedef struct Stall {
    char name[S];
    double income, expense;
} Stall;

void swap(Stall *a, Stall *b) {
    Stall t = *a; *a = *b; *b = t;
}

int partition(Stall arr[], int l, int r) { // Zero indexed
    double pivot = arr[r].income - arr[r].expense;

    int i, j;
    for(j = i = l; j < r; j++) {
        if(arr[j].income - arr[j].expense > pivot) {
            swap(&arr[i], &arr[j]); i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

void quicksort(Stall arr[], int l, int r) {
    if(l < r) {
        int mid = partition(arr, l, r);

        quicksort(arr, l, mid - 1);
        quicksort(arr, mid + 1, r);
    }
}

int main() {
    double tincome, texpense, total_profit, total_loss, temp;
    Stall stalls[8]; int i, j; char tname[S]; 
    

    FILE *input = fopen("input211.txt", "r");
    for(i = 0; fscanf(input, "%s %lf %lf", tname, &tincome, &texpense) == 3; i++) {
        // printf("%s %lf %lf\n", tname, tincome, texpense);
        strcpy(stalls[i].name, tname);
        stalls[i].expense = texpense;
        stalls[i].income = tincome;
    }
    
    quicksort(stalls, 0, i - 1);
    for(j = 0; j < i; j++) {
        printf("%s %.2lf\n", stalls[j].name, (stalls[j].income - stalls[j].expense));
    }

    total_profit = total_loss = 0;
    for(j = 0; j < i; j++) {
        temp = stalls[j].income - stalls[j].expense;
        if(temp >= 0.00) 
            total_profit += temp;
        else 
            total_loss -= temp;
    }

    temp = -1e9;
    for(j = 0; j < i; j++) {
        if(temp < stalls[j].income - stalls[j].expense) {
            temp = stalls[j].income - stalls[j].expense;
            strcmp(tname, stalls[j].name);
        }
    }

    printf("\nJumlah Stalls: %d\nTotal Profit: %.2lf\nTotal Loss: %.2lf\n", i, total_profit, total_loss);
    return 0;
}