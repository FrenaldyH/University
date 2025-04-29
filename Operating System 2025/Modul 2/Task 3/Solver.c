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
    run_program("./A_Summoning_the_Manhwa_Stats.exe");
    run_program("./B_Seal_the_Scrolls.exe");
    run_program("./C_Making_the_Waifu_Gallery.exe");
    run_program("./D_Zip_Save_Goodbye.exe");

    return 0;
}
