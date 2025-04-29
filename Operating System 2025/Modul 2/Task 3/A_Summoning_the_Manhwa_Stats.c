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
            
            // Create the filtering command
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