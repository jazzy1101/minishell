#include "../minishell.h"

void handle_signal()
{
    for (int i = 0; i < g_param->child_count; i++) {
        kill(g_param->child_pids[i], SIGTERM); // Send SIGTERM to each child process
    }
    while (waitpid(-1, NULL, 0) > 0); // Wait for all child processes to terminate
    exit(0); // Exit the shell
}