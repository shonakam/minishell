#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

typedef struct s_pipe {
    int read_end;
    int write_end;
} t_pipe;

void fork_and_exec_command(char *cmd, t_pipe *pipe_in, t_pipe *pipe_out)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // 子プロセス
        if (pipe_in != NULL)
        {
            close(pipe_in->write_end);  // 入力パイプの書き込み側を閉じる
            dup2(pipe_in->read_end, STDIN_FILENO); // 標準入力をパイプの読み取り側にリダイレクト
            close(pipe_in->read_end);  // リダイレクト後にパイプの読み取り側を閉じる
        }

        if (pipe_out != NULL)
        {
            close(pipe_out->read_end);  // 出力パイプの読み取り側を閉じる
            dup2(pipe_out->write_end, STDOUT_FILENO); // 標準出力をパイプの書き込み側にリダイレクト
            close(pipe_out->write_end);  // リダイレクト後にパイプの書き込み側を閉じる
        }

        execlp(cmd, cmd, NULL);  // コマンドを実行
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

void create_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    t_pipe pipe_in = {-1, -1};
    t_pipe pipe_out = {-1, -1};

    char *commands[] = {"ls", "cat", NULL, NULL, NULL};  // NULL 終端のコマンドリスト

    // 最初のコマンドから開始
    for (int i = 0; commands[i] != NULL; ++i)
    {
        if (commands[i + 1] != NULL)
            create_pipe(&pipe_out);
        fork_and_exec_command(commands[i], (i == 0 ? NULL : &pipe_in), (commands[i + 1] != NULL ? &pipe_out : NULL));
        // 入力パイプを更新
        if (commands[i + 1] != NULL)
        {
            close(pipe_in.read_end);
            close(pipe_in.write_end);
            pipe_in = pipe_out;
        }
    }

    if (pipe_in.read_end != -1)
    {
        close(pipe_in.read_end);
        close(pipe_in.write_end);
    }
    while (wait(NULL) > 0)
        ;
}
