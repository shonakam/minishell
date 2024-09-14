#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

typedef struct	command {
	char **args;            // コマンドとその引数
	struct command *next;    // 次のコマンド
}				command_t;

// ビルトインコマンドかどうかを判定する
int is_builtin(char *cmd)
{
	return (strcmp(cmd, "pwd") == 0); // 例: pwd がビルトイン
}

// ビルトインコマンドの実行
void run_builtin(char **args, int write_fd)
{
	if (strcmp(args[0], "pwd") == 0)
	{
		char	cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			dprintf(write_fd, "%s\n", cwd); // パイプに結果を書き込む
		else
			perror("getcwd() error");
	}
}

void execute_command_chain(command_t *cmd_list) {
    int pipefd[2];
    int in_fd = 0; // 最初のコマンドの標準入力は元々の標準入力（0）に接続
    pid_t pid;

    while (cmd_list != NULL)
	{
        if (cmd_list->next != NULL)
            pipe(pipefd); // 次のコマンドが存在する場合、パイプを作成
        if (is_builtin(cmd_list->args[0]))
		{
            // ビルトインコマンドを親プロセスで実行
            run_builtin(cmd_list->args, pipefd[1]); // ビルトインの結果をパイプに書き込み
            close(pipefd[1]); // 書き込みを閉じる
            in_fd = pipefd[0]; // 次のコマンドの標準入力として設定
        }
		else
		{
            pid = fork();
            if (pid == 0) {
                // 子プロセス内

                if (in_fd != 0) {
                    dup2(in_fd, 0); // 標準入力を前のコマンドの出力にリダイレクト
                    close(in_fd);
                }

                if (cmd_list->next != NULL) {
                    close(pipefd[0]); // 読み取り側を閉じる
                    dup2(pipefd[1], 1); // 標準出力をパイプにリダイレクト
                    close(pipefd[1]);
                }

                execvp(cmd_list->args[0], cmd_list->args); // コマンドの実行
                perror("execvp failed");
                exit(1);
            } else {
                // 親プロセス内

                if (cmd_list->next != NULL) {
                    close(pipefd[1]); // パイプの書き込み側を閉じる
                }

                if (in_fd != 0) {
                    close(in_fd); // 既に使用済みの標準入力を閉じる
                }
                in_fd = pipefd[0]; // 次のコマンドの標準入力として設定
            }
        }

        cmd_list = cmd_list->next; // 次のコマンドへ進む
    }

    while (wait(NULL) > 0); // 全ての子プロセスが終了するのを待機
}

int	main() {
    // コマンド例: pwd | cat -e
    // command_t cmd1 = { .args = (char*[]){"pwd", NULL}, .next = NULL };
    // command_t cmd2 = { .args = (char*[]){"cat", "-e", NULL}, .next = NULL };
	command_t cmd1 = { .args = (char*[]){"cat", NULL}, .next = NULL };
    command_t cmd2 = { .args = (char*[]){"cat", NULL}, .next = NULL };
	command_t cmd3 = { .args = (char*[]){"ls", NULL}, .next = NULL };
    cmd1.next = &cmd2;
	cmd2.next = &cmd3;
    execute_command_chain(&cmd1);
    return 0;
}
