#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>

struct termios original_tio;

void handle_sigquit(int sig)
{
    // バックスペースを出力して^\を消す
    write(STDOUT_FILENO, "\b", 1);  // 1回バックスペースを出力
    fflush(stdout);  // 出力を即座に表示
}

void handle_sigint(int sig)
{
    // SIGINTを受け取ったときにメッセージを表示する
    write(STDOUT_FILENO, "\nSIGINT received. Process will not terminate.\n", 45);
    fflush(stdout);  // 出力を即座に表示
}

void set_terminal_flags(int fd, int disable_signals)
{
    // 現在の端末設定を取得
    if (tcgetattr(fd, &original_tio) != 0)
    {
        perror("tcgetattr failed");
        return;
    }

    struct termios new_tio = original_tio;

    // ISIGフラグを無効化して、SIGQUITやSIGINTの処理を無効にする
    if (disable_signals)
    {
        new_tio.c_lflag &= ~ISIG;  // ISIGフラグを無効化
    }

    // 端末設定を変更
    if (tcsetattr(fd, TCSANOW, &new_tio) != 0)
    {
        perror("tcsetattr failed");
        return;
    }
}

void restore_terminal_flags(int fd)
{
    // プログラム終了時に元の端末設定を復元
    if (tcsetattr(fd, TCSANOW, &original_tio) != 0)
    {
        perror("tcsetattr failed to restore");
    }
}

int main() {
    // プログラム終了時に端末設定を元に戻すように登録
    atexit(restore_terminal_flags);  // atexitに標準関数を登録

    // SIGQUITとSIGINTを適切に処理する関数を設定
    signal(SIGQUIT, handle_sigquit);  // 親プロセスでSIGQUITを捕まえる
    signal(SIGINT, handle_sigint);    // 親プロセスでSIGINTを捕まえる
    set_terminal_flags(STDIN_FILENO, 1);  // ISIGを無効化

    pid_t pid = fork();
    if (pid == 0) {
        // 子プロセスでcatやgrepを実行
        const char *args[] = {"/bin/cat", NULL};  // 例としてcatコマンド
        execve(args[0], (char *const *)args, NULL);  // execveでcatを実行

        perror("execve failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // 親プロセスで待機
        wait(NULL);  // 子プロセスの終了を待つ
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
