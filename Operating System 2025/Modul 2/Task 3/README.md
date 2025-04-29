[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9LcL5VTQ)
|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221126 | Fairuz Hanif Rahmadi |
| 5025221156 | Frenaldy Bestabba Hasugian |
| 5025221165 | Rafi Aqila Maulana |

# Praktikum Modul 2 _(Module 2 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - Trabowo & Peddy Movie Night](/task-1/)

- [Task 2 - Organize and Analyze Anthony's Favorite Films](/task-2/)

- [Task 3 - Cella’s Manhwa](/task-3/)

- [Task 4 - Pipip's Load Balancer](/task-4/)

## Laporan Pengerjaan Task-3 (Cella's Manhwa)

### A) Summoning the Manhwa Stats
#### 📌 **Deskripsi Singkat** 
> Membantu Cella mengambil data manhwa menggunakan API dan menyimpannya di folder dengan ketentuan yang tertera.

#### 📝 **Cara Pengerjaan**
1) Mencari ID dan nama manhwa kemudian menyimpannya di array of struct.
2) Membuat folder "Manhwa" dengan menggunakan execv() yang digunakan untuk menyimpan file-file data manhwa.
3) Mencari data-data menhwa menggunakan API dan kemudian menyimpannya dalam bentuk yang telah diolah oleh salah satu function json.
4) Memfilter data mentah json agar sesuai format ketentuan Cella.

#### 👉 **Kendala**
> Kesulitan dalam membaca file mentah sehingga diubah menjadi format json dengan menggunakan "| jq".


#### Kode
```
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <sys/wait.h>
  
  typedef struct {
      char *title;
      int id;
  } manhwa;
  
  manhwa manhwa_list[] = {
      {"Mistaken_as_the_Monster_Dukes_Wife", 168827},
      {"The_Villainess_Lives_Again", 147205},
      {"No_I_Only_Charmed_the_Princess", 169731},
      {"Darling_Why_Cant_We_Divorce", 175521}
  };
  
  void make_Manhwa() {
      pid_t pid = fork();
      if(pid == 0) {
          char *args[] = {"mkdir", "-p", "Manhwa", NULL};
          execv("/bin/mkdir", args);
          exit(EXIT_FAILURE);
      }   
      wait(NULL);
  }
  
  void make_json() {
      for(int i = 0; i < sizeof(manhwa_list) / sizeof(manhwa); i++) {
          pid_t pid = fork();
          if(pid == 0) {
              char filename[(1 << 11)], command[(1 << 12)];
              
              snprintf(filename, sizeof(filename), "Manhwa/%s.txt", manhwa_list[i].title);
              snprintf(command, sizeof(command),
                      "curl -s https://api.jikan.moe/v4/manga/%d | jq > \"%s\"",
                      manhwa_list[i].id, filename);
              
              char *args[] = {"/bin/sh", "-c", command, NULL};
              execv("/bin/sh", args);
              exit(EXIT_FAILURE);
          }
          wait(NULL); 
      }
  }
  
  void filter_json() {
      for(int i = 0; i < sizeof(manhwa_list) / sizeof(manhwa); i++) {
          pid_t pid = fork();
          if(pid == 0) {
              char filename[(1 << 11)], tempname[(1 << 12)], command[(1 << 15)];
              
              snprintf(filename, sizeof(filename), "Manhwa/%s.txt", manhwa_list[i].title);
              snprintf(tempname, sizeof(tempname), "%s.temp", filename);
              
              snprintf(command, sizeof(command),
                  "jq -r '\"Title: \" + (.data.title // \"Unknown\") + \"\\n\" + "
                  "\"Status: \" + (.data.status // \"Unknown\") + \"\\n\" + "
                  "\"Release: \" + (.data.published.from // \"Unknown\" | sub(\"T.*\"; \"\")) + \"\\n\" + "
                  "\"Genre: \" + ((.data.genres // []) | map(.name) | join(\", \") // \"Unknown\") + \"\\n\" + "
                  "\"Theme: \" + ((.data.themes // []) | map(.name) | join(\", \") // \"Unknown\") + \"\\n\" + "
                  "\"Author: \" + ((.data.authors // [])[0].name // \"Unknown\")' "
                  "\"%s\" > \"%s\" && mv \"%s\" \"%s\"",
                  filename, tempname, tempname, filename);
              
              char *args[] = {"/bin/sh", "-c", command, NULL};
              execv("/bin/sh", args);
              exit(EXIT_FAILURE);
          }
          wait(NULL);
      }
  }
  
  int main() {
      make_Manhwa();
      make_json();
      filter_json();
      return EXIT_SUCCESS;
  }
```

#### Hasil
> Hasil diurutkan berdasarkan abjad
1) File 1: Darling_Why_Cant_We_Divorce.txt
   ```
    Title: Darling, Why Can't We Divorce?
    Status: Publishing
    Release: 2024-10-02
    Genre: Fantasy, Romance
    Theme: Isekai, Villainess
    Author: Cha, Sohee
   ```
2) FIle 2: Mistaken_as_the_Monster_Dukes_Wife.txt
   ```
     Title: Mistaken as the Monster Duke's Wife
     Status: Publishing
     Release: 2024-03-22
     Genre: Fantasy, Romance
     Theme: Isekai, Reincarnation
     Author: Euncha
   ```
3) File 3: No_I_Only_Charmed_the_Princess.txt
   ```
    Title: No, I Only Charmed the Princess!
    Status: Publishing
    Release: 2024-04-18
    Genre: Fantasy, Romance
    Theme: Isekai, Reincarnation
    Author: Maru Gongbang
   ```
4) File 4: The_Villainess_Lives_Again.txt
   ```
    Title: The Villainess Lives Again
    Status: Finished
    Release: 2020-06-03
    Genre: Drama, Fantasy, Romance
    Theme: Time Travel
    Author: Han, Mint
   ```

### B) Seal the Scrolls
#### 📌 **Deskripsi Singkat**
> Membantu cella untuk mengzip kan masing-masing file data di Manhwa dan menyimpannya di folder baru bernama Archive sesuai ketentuan Cella

#### 📝 **Cara Pengerjaan**
1) Membuat array of struct yang menyimpan nama dan ID manhwa cella.
2) Membuat folder "Archive" dengan menggunakan execv() yang digunakan untuk menyimpan data dalam bentuk Zip.
3) Membuat zip dan menyimpannya di "Archive"

#### Kode 
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

typedef struct {
    char *title;
    int id;
} manhwa;

manhwa manhwa_list[] = {
    {"Mistaken_as_the_Monster_Dukes_Wife", 168827},
    {"The_Villainess_Lives_Again", 147205},
    {"No_I_Only_Charmed_the_Princess", 169731},
    {"Darling_Why_Cant_We_Divorce", 175521},
};

void make_Archive() {
    pid_t pid = fork();
    if(pid == 0) {
        char *args[] = {"mkdir", "-p", "Archive", NULL};
        execv("/bin/mkdir", args);
        exit(EXIT_FAILURE);
    }
    wait(NULL);
}

void zip_name(const char *filename, char *zipname) {
    int j = 0;
    for(int i = 0; filename[i] != '\0'; i++) {
        if(filename[i] >= 'A' && filename[i] <= 'Z') {
            zipname[j++] = filename[i];
        }
    }
    zipname[j] = '\0';
    strcat(zipname, ".zip");
}

void make_zip() {
    make_Archive(); 
    
    for(int i = 0; i < sizeof(manhwa_list) / sizeof(manhwa); i++) {
        pid_t pid = fork();
        if(pid == 0) {
            char zipname[(1 << 11)], filename[(1 << 11)], command[(1 << 13)];
            
            
            snprintf(filename, sizeof(filename), "Manhwa/%s.txt", manhwa_list[i].title);
            zip_name(manhwa_list[i].title, zipname);
            
            char zip_path[(1 << 12)];
            snprintf(zip_path, sizeof(zip_path), "Archive/%s", zipname);
            
            snprintf(command, sizeof(command), "zip -j '%s' '%s'", zip_path, filename);
            char *args[] = {"/bin/sh", "-c", command, NULL};
            execv("/bin/sh", args);
            
            perror("execv failed");
            exit(EXIT_FAILURE);
        }
        wait(NULL);
    }
}

int main() {
    make_zip();
}
```
##### Hasil
1) [DWCD.zip](Archive/DWCWD.zip)
2) [MMDW.zip](Archive/MMDW.zip)
3) [NIOCP.zip](Archive/NIOCP.zip)
4) [TVLA.zip](Archive/TVLA.zip)
   

### C) Making the Waifu Gallery
#### 📌 **Deskripsi Singkat**
> Mengunduh gambar masing-masing heroin manhwa sesuai ketentuan yang Cella berikan

#### **📝 Cara Pengerjaan**
1) Menyimpan nama manhwa berserta IDnya di dalam sebuah array of struct
2) Membuat folder "Heroin" untuk menyimpan masing-masing file heroin pada setiap Manhwa
3) Mengubah keterngan bulan pada file data dari string ke int
4) Mendownload file gambar sesuai bulan rilis manhwa dan menyimpannya di file yang sesuai

#### 👉 **Kendala**
> Kesulitan dalam mendapatkan API yang menyediakan keterangan heroin secara explisit, sehingga saya mencari nama Heroin dan linknya secara manual 

#### Hasil
> Folder [Heroin](Heroin/)





