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
        perror("popen failed");
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
