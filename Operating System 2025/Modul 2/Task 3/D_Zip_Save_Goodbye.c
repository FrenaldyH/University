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
