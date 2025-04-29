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

#### Kode
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAX_FILES 100

typedef struct {
    char *title, *heroin;
    int id;
} manhwa;

typedef struct {
    int month, idx;
} release;

manhwa manhwa_list[] = {
    {"Mistaken_as_the_Monster_Dukes_Wife", "Lia+Dellis", 168827},
    {"The_Villainess_Lives_Again", "Artezia+Rosan", 147205},
    {"No_I_Only_Charmed_the_Princess", "Adelia+Vita", 169731},
    {"Darling_Why_Cant_We_Divorce", "Ophelia+Lizen", 175521}
};

release rel[4];
char downloaded_files[MAX_FILES][256];
int downloaded_count = 0;

void sanitize_heroine_name(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i]; i++) {
        if (src[i] == '+')
            dest[j++] = '_';
        else
            dest[j++] = src[i];
    }
    dest[j] = '\0';
}

void month_count() {
    for (int i = 0; i < 4; i++) {
        char filename[128], buffer[1024];
        snprintf(filename, sizeof(filename), "Manhwa/%s.txt", manhwa_list[i].title);

        FILE *file = fopen(filename, "r");
        while (fgets(buffer, sizeof(buffer), file)) {
            if (buffer[0] == 'R') {
                rel[i].month = ((int)buffer[14] - '0') * 10 + ((int)buffer[15] - '0');
                break;
            }
        }

        fclose(file);
        rel[i].idx = i;
    }
}

void make_Heroines() {
    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {"mkdir", "-p", "Heroines", NULL};
        execv("/bin/mkdir", args);
        exit(EXIT_FAILURE);
    }
    wait(NULL);
}

typedef struct {
    int index;
} ThreadData;

void *download_images(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int idx = data->index;

    char clean_heroine[128];
    sanitize_heroine_name(clean_heroine, manhwa_list[idx].heroin);

    char folder_path[256];
    snprintf(folder_path, sizeof(folder_path), "Heroines/%s", clean_heroine);

    char mkdir_cmd[300];
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p \"%s\"", folder_path);
    system(mkdir_cmd);

    char query[512];
    snprintf(query, sizeof(query), "https://www.google.com/search?tbm=isch&q=%s+character+%s",
             manhwa_list[idx].title, manhwa_list[idx].heroin);

    char curl_cmd[2048];
    snprintf(curl_cmd, sizeof(curl_cmd),
             "curl -s -A \"Mozilla/5.0\" \"%s\" | grep -o 'src=\\\"[^\\\"]*\\\"' | grep -Eo 'https?://[^\\\"]+' | head -n %d",
             query, rel[idx].month);

    FILE *fp = popen(curl_cmd, "r");
    if (!fp) {
        pthread_exit(NULL);
    }

    char img_url[1024];
    int count = 1;
    while (fgets(img_url, sizeof(img_url), fp) != NULL && count <= rel[idx].month) {
        img_url[strcspn(img_url, "\n")] = 0;

        char save_path[256];
        snprintf(save_path, sizeof(save_path), "%s/%s_%d.jpg",
                 folder_path, clean_heroine, count);

        char download_cmd[1024];
        snprintf(download_cmd, sizeof(download_cmd),
                 "curl -s \"%s\" -o \"%s\"", img_url, save_path);

        system(download_cmd);

        snprintf(downloaded_files[downloaded_count], sizeof(downloaded_files[0]),
                 "%s/%s_%d.jpg", clean_heroine, clean_heroine, count);
        downloaded_count++;

        count++;
    }

    pclose(fp);
    pthread_exit(NULL);
}

void make_jpg() {
    for (int i = 0; i < 4; i++) {
        pthread_t tid;
        ThreadData *data = malloc(sizeof(ThreadData));
        data->index = i;

        pthread_create(&tid, NULL, download_images, (void *)data);
        pthread_join(tid, NULL); 
        free(data);
    }
}

void list_downloaded_files() {
    printf("\nDaftar Gambar yang Berhasil Diunduh:\n");
    for (int i = 0; i < downloaded_count; i++) {
        printf("- %s berhasil diunduh\n", downloaded_files[i]);
    }
}

int main() {
    month_count();
    make_Heroines();
    make_jpg();
    list_downloaded_files();
    return 0;
}

```

#### Hasil
> Folder [Heroin](Heroin/)

### D) Making the Waifu Gallery
#### 📌 **Deskripsi Singkat**
> Membantu Cella mengarsipkan file Heroinnya sesuai dengan format dan ketentuan yang sudah ditetapkan

#### **📝 Cara Pengerjaan**
1) Menyiapkan nama file dan nama heroin secara langsung (manual) dan menyimpannya di array of struct
2) Membuat Folder "image" di folder "Archive"
3) Mengubah masing masing folder foto heroin ke dalam bentuk zip
4) Hapus file yang lama di Folder Heroin satu per satu dengan urutan awal (bukan abjad)

#### 👉 **Kendala**
> Salah urutan menghapus file Heroin yang lama karena kurang teliti

#### Kode
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_PATH 512

typedef struct {
    char manhwa_title[MAX_PATH];
    char heroine_name[MAX_PATH];
} HeroineData;

HeroineData heroines[] = {
    {"MISTAKEN_AS_THE_MONSTER_DUKES_WIFE", "Lia_Dellis"},
    {"THE_VILLAINESS_LIVES_AGAIN", "Artezia_Rosan"},
    {"NO_I_ONLY_CHARMED_THE_PRINCESS", "Adelia_Vita"},
    {"DARLING_WHY_CANT_WE_DIVORCE", "Ophelia_Lizen"}
};

void create_archive_images_folder() {
    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {"mkdir", "-p", "Archive/Images", NULL};
        execv("/bin/mkdir", args);
        exit(EXIT_FAILURE);
    }
    wait(NULL);
}

void zip_heroine_folder(const char *manhwa, const char *heroine) {
    pid_t pid = fork();
    if (pid == 0) {
        char zip_name[MAX_PATH];
        snprintf(zip_name, sizeof(zip_name), "Archive/Images/%s_%s.zip", manhwa, heroine);

        char folder_path[MAX_PATH];
        snprintf(folder_path, sizeof(folder_path), "Heroines/%s", heroine);

        char *args[] = {"zip", "-r", zip_name, folder_path, NULL};
        execv("/usr/bin/zip", args);
        exit(EXIT_FAILURE);
    }
    wait(NULL);
}

void delete_heroine_images(const char *heroine) {
    char temp_list[] = "file_list.txt";

    // Fork untuk membuat list file dengan ls
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open(temp_list, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        char folder_path[MAX_PATH];
        snprintf(folder_path, sizeof(folder_path), "Heroines/%s", heroine);

        char *args[] = {"ls", folder_path, NULL};
        execv("/bin/ls", args);
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    // Buka file_list.txt
    FILE *fp = fopen(temp_list, "r");

    char files[100][MAX_PATH];
    int count = 0;
    while (fgets(files[count], sizeof(files[count]), fp)) {
        files[count][strcspn(files[count], "\n")] = 0; // hapus \n
        count++;
    }
    fclose(fp);

    // Urutkan abjad
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(files[i], files[j]) > 0) {
                char temp[MAX_PATH];
                strcpy(temp, files[i]);
                strcpy(files[i], files[j]);
                strcpy(files[j], temp);
            }
        }
    }

    // Hapus file satu per satu
    for (int i = 0; i < count; i++) {
        char filepath[MAX_PATH];
        snprintf(filepath, sizeof(filepath), "Heroines/%s/%s", heroine, files[i]);
        if (remove(filepath) == 0) {
            printf("Berhasil menghapus %s\n", filepath);
        } else {
            perror("Gagal menghapus file");
        }
    }

    // Hapus file_list.txt
    remove(temp_list);
}

int main() {
    int n = sizeof(heroines) / sizeof(HeroineData);

    create_archive_images_folder();

    for (int i = 0; i < n; i++) {
        zip_heroine_folder(heroines[i].manhwa_title, heroines[i].heroine_name);
    }

    for (int i = 0; i < n; i++) {
        delete_heroine_images(heroines[i].heroine_name);
    }

    return 0;
}
```
#### Hasil
> Folder [images](Archive/image)

### E) Solver
#### 📌 **Deskripsi Singkat**
> Menjalankan program A, B, C, dan D secara berurutan

#### Kode -> [Solver](Solver.c)
```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void run_program(const char *program_name) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *args[] = {(char *)program_name, NULL};
        execv(program_name, args);
        exit(EXIT_FAILURE);
    } 
    else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("%s exited with status %d\n", program_name, WEXITSTATUS(status));
        }
    } 
    else {
        exit(EXIT_FAILURE);
    }
}

int main() {
    run_program("./A_Summoning_the_Manhwa_Stats");
    run_program("./B_Seal_the_Scrolls");
    run_program("./C_Making_the_Waifu_Gallery");
    run_program("./D_Zip_Save_Goodbye");

    return 0;
}
```



