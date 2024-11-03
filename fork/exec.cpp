#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <program-to-run>" << endl;

        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");

        return 1;
    }

    if (pid == 0) {
        int out_fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        int err_fd = open("err.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1 || err_fd == -1) {
            perror("open");

            return 1;
        }

        if (dup2(out_fd, STDOUT_FILENO) == -1 || dup2(err_fd, STDERR_FILENO) == -1) {
            perror("dup2");

            return 1;
        }

        close(out_fd);
        close(err_fd);

        execvp(argv[1], &argv[1]);
        perror("execvp");

        return 1;
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            cout << "Child process exited with code " << WEXITSTATUS(status) << endl;
        } else {
            cerr << "Child process did not exit normally" << endl;
        }
    }

    return 0;
}
