#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <conio.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h> 
#else
    #include <unistd.h> 
#endif

#ifdef _WIN32
    #define clsscr() system("cls")
#else
    #define clsscr() system("clear")
#endif

void sleep_ms(int milliseconds) {
    #ifdef _WIN32
    Sleep(milliseconds);
    #else
    usleep(milliseconds * 1000);
    #endif
}

void animation(char* op) {
    clsscr();
    printf("%s", op);
    sleep_ms(320);
    for(int i = 0; i < 3; i++) {
        printf(" .");
        sleep_ms(320);
    }
    clsscr();
}

typedef struct {
    char id[7], name[26];
    double price;
    long long count;
} data;

int idx_arr = 0;
data arr[20000];

int search(char* target_id) {
    int l = 0, r = idx_arr - 1, mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(strcmp(arr[mid].id, target_id) > 0) {
            r = mid - 1;
            continue;
        }
        if(strcmp(arr[mid].id, target_id) < 0) {
            l = mid + 1;
            continue;
        }
        return mid;
    }
    return -1; 
}

void swap(data *a, data *b) {
    data c = *a;
    *a = *b;
    *b = c;
}

int partition(int low, int high) {
    data pivot = arr[high];
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j].id, pivot.id) <= 0) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1);
}

void quick_sort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}

void sort_data() {
    if (idx_arr) 
        quick_sort(0, idx_arr - 1);
}

void add_data(short op) {
    int i, j, temp;
    char cmd[5][100] = {
        "Nomor Komponen: ",
        "Nama Komponen: ",
        "Jumlah Stok: ",
        "Harga Satuan: "
    };

    if(op) temp = idx_arr++;
    else {
        if(!idx_arr) {
            animation("Tidak ada data yang bisa dirubah");
            return;
        }

        char id[7];
        printf("Id data yang ingin dirubah: ");
        scanf("%s", id);
        clsscr();
        
        temp = search(id);
        if(temp < 0) {
            animation("Id tidak ditemukan");
            return;
        }
    }
    
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            printf(i == j ? "-> " : "   ");
            printf("%d. ", j + 1);
            printf(op ? "" : "ubah ");
            printf("%s\n", cmd[j]);
        }
        printf("=> Masukan Data: ");
        switch (i) {
        case 0: scanf("%s", arr[temp].id); break;
        case 1: 
            getchar();
            fgets(arr[temp].name, sizeof(arr[temp].name), stdin); 
            arr[temp].name[strlen(arr[temp].name) - 1] = '\0';
            break;
        case 2: scanf("%ld", &arr[temp].count); break;
        case 3: scanf("%lf", &arr[temp].price); break;
        }
        clsscr();
    }
    sort_data();
    if(op) animation("Penambahan data berhasil");
    else   animation("Perubahan data berhasil");
}

void display_data(short op) {
    if(!idx_arr) {
        animation("Tidak ada data yang bisa ditampilkan");
        return;
    }

    double total_aset = 0;
    char cmd[4][10] = {
        "ID", "Nama", "Jumlah", "Harga"
    };
    if(op) printf("| %-6s ", cmd[0]);
    printf("| %-25s | %-10s | %-10s |\n", cmd[1], cmd[2], cmd[3]);
    for(int i = 0; i < idx_arr; i++) {
        if(op) printf("| %-6s ", arr[i].id);
        printf("| %-25s | %-10ld | %-10.2lf |\n", arr[i].name, arr[i].count, arr[i].price);
        total_aset += ((double)arr[i].count * arr[i].price);
    }
    getch();
    clsscr();
    printf("Total aset: %.2lf\n", total_aset);
    printf("Total data: %d\n", idx_arr);
    getch();
}

void erase_data() {
    char id[7];
    int temp, i, j;

    if(!idx_arr) {
        animation("Tidak ada data yang bisa dihapus");
        return;
    }

    printf("Id data yang ingin dihapus: ");
    scanf("%s", id);

    temp = search(id);
    if(temp < 0) {
        animation("Id tidak ditemukan");
        return;
    }

    idx_arr--;
    for(i = temp; i < idx_arr; i++) 
        arr[i] = arr[i + 1];
    animation("Penghapusan Data Berhasil");
}

bool load_data() {
    FILE* file = fopen("DB.bin", "rb");

    if(!file) return 0;
    
    fseek(file, 0, SEEK_END);
    idx_arr = ftell(file) / sizeof(data);
    rewind(file);

    fread(arr, sizeof(data), idx_arr, file);
    fclose;
    return 1;
}

void save_data() {
    FILE* file = fopen("DB.bin", "wb");

    if(!file) {
        animation("Gagal membuka file DB.bin");
        return;
    }

    fwrite(arr, sizeof(data), idx_arr, file);
    fclose(file);
}

void menu() {
    animation("Loading");
    if(!load_data()) {
        animation("File DB.bin tidak ditemukan");
        return;
    }

    bool exit = false;
    short i, arrow = 0;
    char ch, cmd[6][100] = {
        "1. \033[4mM\033[0menambah data\n",
        "2. Meng\033[4mu\033[0mbah data\n",
        "3. Menampilkan semua data dengan inde\033[4mx\033[0m\n",
        "4. Menampilkan semua data \033[4mt\033[0manpa index\n",
        "5. \033[4mH\033[0mapus data\n",
        "6. \033[4mK\033[0meluar\n"
    };      
    do {
        clsscr();
        printf("   #  \033[4mMENU PENGOLAHAN DATA\033[0m\n");
        for(i = 0; i < 6; i++) {
            printf(arrow == i ? "-> " : "   ");
            printf("%s", cmd[i]);
        } 
        ch = getch();
        clsscr();
        if(ch == -32) {
            ch = getch();
            if(ch == 80) 
                arrow++;
            else if(ch == 72)
                arrow--;
            else animation("Invalid key");
            if(arrow < 0) arrow = 5;
            if(arrow > 5) arrow = 0;
        }
        else if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') {
            if(ch >= 'a' && ch <= 'z') ch -= 32;
            switch (ch) {
            case 'M': add_data(1); break;
            case 'U': add_data(0); break;
            case 'X': display_data(1); break;
            case 'T': display_data(0); break;
            case 'H': erase_data(); break;
            case 'K': exit = true; break;
            default: animation("Invalid key"); break;
            }
        }
        else if(ch >= '0' && ch <= '9') {
            switch (ch) {
            case '1': add_data(1); break;
            case '2': add_data(0); break;
            case '3': display_data(1); break;
            case '4': display_data(0); break;
            case '5': erase_data(); break;
            case '6': exit = true; break;
            default: animation("Invalid key"); break;
            }
        }
        else if(ch == 13) {
            switch (arrow) {
            case 0: add_data(1); break;
            case 1: add_data(0); break;
            case 2: display_data(1); break;
            case 3: display_data(0); break;
            case 4: erase_data(); break;
            case 5: exit = true; break;
            }
        }
        else animation("Invalid key");
    } while(!exit || clsscr());
    animation("Menyimpan data ke bin");
    save_data();
} 

int main() {
    menu();
}