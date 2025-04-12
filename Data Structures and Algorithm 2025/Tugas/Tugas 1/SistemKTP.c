#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Shortcut
#define S 101
#define P(x) printf(x)
#define el printf("%c", '\n')

typedef struct waktu {
    int tanggal, bulan, tahun;
} waktu;

typedef struct data {
    char alamat_lahir[S], alamat_domisili[S], alamat_pembuatan[S], 
            nik[17], nama[S], kelurahan[S], kecamatan[S], agama[S],
            pekerjaan[S], kewarganegaraan[S], gol_darah;
    waktu lahir, berlaku, pembuatan;
    int rt, rw, jenis_kelamin, status, wna;
} data;

// Global variabel
data ktp[S]; int n;
char    oat1[24][S] = {"==> Silahkan_masukan_data_KTP <==", "NIK", "Nama", "Tempat_lahir", "Tanggal_lahir", "Bulan_lahir", "Tahun_lahir",
                    "Jenis_kelamin", "Golongan_darah", "Alamat_domisili", "Rt", "Rw", "Kelurahan", "Kecamatan", "Agama", "Status_perkawinan", 
                    "Pekerjaan", "Kewarganegaraan", "Berlaku_hingga", "Tempat_pembuatan_KTP", "Tanggal_pembuatan", "Bulan_pembuatan", "Tahun_pembuatan"},
        oat2[8][S] = {"==> Silahkan_memilih_opsi <==", "Tambah_data", "Cari_data", "Tampilkan_data", "Hapus_data", "Keluar", "Masukan_pilihan: "};


void delay (int mili_seconds) {
    clock_t st_time  = clock();
    for(; clock() < st_time + mili_seconds;);
}

void animation (char s[]) {
    int i, j;
    for(i = 0; i < 4; i++) {
        P(s);
        for(j = 0; j < i; j++) P(" .");
        delay(350); system("cls");
    }
}

void kapital (char s[]) {
    for(int i = 0; s[i] != '\0'; i++) 
        if(s[i] >= 97 && s[i] <= 122)
            s[i] -= 32;
};

int search_data(char s[]) {
    int i;
    for(i = 0; i < n; i++) 
        if(!strcmp(s, ktp[i].nik)) 
            return i;
    return -1;
}

void add_data() {
    if(n >= S) {
        animation("Invalid_Proccessing");
        return;
    }

    int i, j; ktp[n].wna = false;
    for(i = 0; i < 23; i++) {
        if(!i) {
            printf("%s\n", oat1[i]);
            continue;
        }
        else if(i == 18) continue;
        
        printf("%d) %s: ", i, oat1[i]);
        char in[S];
        switch(i) {
            case 1:
                scanf(" %s", ktp[n].nik);
                getchar();
                break;
            case 2:
                fgets(ktp[n].nama, S, stdin);
                kapital(ktp[n].nama);
                break;
            case 3:
                fgets(ktp[n].alamat_lahir, S, stdin);
                kapital(ktp[n].alamat_lahir);
                break;  
            case 4:
                scanf(" %d", &ktp[n].lahir.tanggal);
                break;
            case 5:
                scanf(" %d", &ktp[n].lahir.bulan);
                break;
            case 6:
                scanf(" %d", &ktp[n].lahir.tahun);
                break;
            case 7:
                scanf(" %s", in);
                kapital(in);

                if(!strcmp(in, "LAKI-LAKI"))
                    ktp[n].jenis_kelamin = 1;
                else if(!strcmp(in, "PEREMPUAN"))
                    ktp[n].jenis_kelamin = 2;
                else 
                    ktp[n].jenis_kelamin = 0;
                break;
            case 8:
                scanf(" %c", &ktp[n].gol_darah);
                if(ktp[n].gol_darah >= 97)
                    ktp[n].gol_darah -= 32;
                    break;
            case 9:
                getchar();
                fgets(ktp[n].alamat_domisili, S, stdin);
                kapital(ktp[n].alamat_domisili);
                break;
            case 10:
                scanf(" %d", &ktp[n].rt);
                break;
            case 11:
                scanf(" %d", &ktp[n].rw);
                break;
            case 12:
                getchar();
                fgets(ktp[n].kelurahan, S, stdin);
                kapital(ktp[n].kelurahan);
                break;
            case 13:
                fgets(ktp[n].kecamatan, S, stdin);
                kapital(ktp[n].kecamatan);
                break;
            case 14:
                scanf(" %s", ktp[n].agama);
                kapital(ktp[n].agama);
                break;
            case 15:
                getchar();
                fgets(in, S, stdin);
                kapital(in);

                if(!strcmp(in, "BELUM KAWIN"))
                    ktp[n].status = 2;
                else if(!strcmp(in, "KAWIN"))
                    ktp[n].status = 1;
                else 
                    ktp[n].status = 0;
                break;
            case 16:
                fgets(ktp[n].pekerjaan, S, stdin);
                kapital(ktp[n].pekerjaan);
                break;
            case 17:
                fgets(ktp[n].kewarganegaraan, S, stdin);
                kapital(ktp[n].kewarganegaraan);
                ktp[n].wna = !strcmp(ktp[n].kewarganegaraan, "WNI");
                break;
            case 19:
                fgets(ktp[n].alamat_pembuatan, S, stdin);
                kapital(ktp[n].alamat_pembuatan);
                break;
            case 20:
                scanf(" %d", &ktp[n].pembuatan.tanggal);
                break;
            case 21:
                scanf(" %d", &ktp[n].pembuatan.bulan);
                break;
            case 22:
                scanf(" %d", &ktp[n].pembuatan.tahun);
                break;
        }
    }

    system("cls");
    if(search_data(ktp[n].nik) >= 0) {animation("NIK_KTP_sudah_ada_terdata");} 
    else {animation("Proccessing_successful"); n++;}
}

void delete_data() {    
    if (n == 0) {
        animation("Data_ktp_masih_kosong");
        return;
    }

    char s[S]; 
    P("Masukan_NIK_KTP_yang_ingin_dihapus: "); scanf(" %s", s);

    int hapus = search_data(s);
    if(hapus == -1) {
        animation("Data_KTP_tidak_ditemukan");
    }
    else {
        for(int i = hapus; i < n - 1; i++)
            ktp[i] = ktp[i + 1];
        n--;
        animation("Delete_successfuly");
    }
}

void simple_display (int i) {
    for (int j = 1; j < 23; j++) {
        printf("%d) %s: ", j, oat1[j]);
        switch (j) {
            case 1:
                printf("%s\n", ktp[i].nik);
                break;
            case 2:
                printf("%s", ktp[i].nama);
                break;
            case 3:
                printf("%s", ktp[i].alamat_lahir);
                break;
            case 4:
                printf("%02d\n", ktp[i].lahir.tanggal);
                break;
            case 5:
                printf("%02d\n", ktp[i].lahir.bulan);
                break;
            case 6:
                printf("%04d\n", ktp[i].lahir.tahun);
                break;
            case 7:
                printf("%s\n", ktp[i].jenis_kelamin == 1 ? "LAKI-LAKI" : ktp[i].jenis_kelamin == 2 ? "PEREMPUAN" : "TIDAK DIKETAHUI");
                break;
            case 8:
                printf("%c\n", ktp[i].gol_darah);
                break;
            case 9:
                printf("%s", ktp[i].alamat_domisili);
                break;
            case 10:
                printf("%d\n", ktp[i].rt);
                break;
            case 11:
                printf("%d\n", ktp[i].rw);
                break;
            case 12:
                printf("%s", ktp[i].kelurahan);
                break;
            case 13:
                printf("%s", ktp[i].kecamatan);
                break;
            case 14:
                printf("%s\n", ktp[i].agama);
                break;
            case 15:
                printf("%s\n", ktp[i].status == 1 ? "KAWIN" : ktp[i].status == 2 ? "BELUM KAWIN" : "TIDAK DIKETAHUI");
                break;
            case 16:
                printf("%s", ktp[i].pekerjaan);
                break;
            case 17:
                printf("%s", ktp[i].kewarganegaraan);
                break;
            case 18:
                P("Seumur Hidup\n");
                break;
            case 19:
                printf("%s", ktp[i].alamat_pembuatan);
                break;
            case 20:
                printf("%02d\n", ktp[i].pembuatan.tanggal);
                break;
            case 21:
                printf("%02d\n", ktp[i].pembuatan.bulan);
                break;
            case 22:
                printf("%04d\n", ktp[i].pembuatan.tahun);
                break;
        }
    }
}

void display_data1() {
    if (n == 0) {
        animation("Tidak_ada_data_KTP_yang_bisa_ditampilkan");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("==> Data KTP ke-%d <==\n", i + 1);
        simple_display(i);
        printf("\n");
    }
    delay(1); P("--> Please enter any key to continue! "); getch(); system("cls");
    animation("Return");
}

void display_data2() {
    if (n == 0) {
        animation("--> Tidak_ada_data_KTP_yang_bisa_ditampilkan");
        return;
    }

    char s[S]; 
    P("--> Masukan_NIK_KTP_yang_ingin_dicari: "); scanf(" %s", s);
    int i = search_data(s); system("cls");

    if(i == -1) {
        animation("--> Data_KTP_tidak_ditemukan");
        return;
    }
    
    P("--> Data_KTP_berhasil_ditemukan\n");
    simple_display(i);
    el; delay(1); P("--> Please enter any key to continue! "); getch(); system("cls");
    animation("Return");
}

int main() {
    int op, i; n = 0;

    // Starting_animation
    system("cls");
    P("==> KTP Database System in C Proggraming Languange <==\n");
    delay(1); P("--> Please enter any key to continue! "); 
    getch(); system("cls"); animation("Start");

    do {
        do {
            for(i = 0; i < 7; i++) {
                if(i >= 1 && i <= 5) 
                    printf("%d) ", i);
                printf("%s\n", oat2[i]);
            }
            scanf(" %d", &op); system("cls");

            // Processing_animation
            if(op >= 1 && op <= 4) animation("Loading");
            else if(op < 1 || op > 5) animation("Invalid_input_option");
        } while(op < 1 || op > 5); // Invalid_input
        
        switch(op) {
            case 1:
                add_data();
                break;
            case 2:
                display_data2();
                break;
            case 3:
                display_data1();
                break;
            case 4:
                delete_data();
                break;
            default: break;
        }
    } while(op != 5);
    
    // Exit Animation
    system("cls"); animation("Exit");

    return 0;
}

// 456, 20 - 22
