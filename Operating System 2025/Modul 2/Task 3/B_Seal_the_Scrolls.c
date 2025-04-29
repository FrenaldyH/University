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

