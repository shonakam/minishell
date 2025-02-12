#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/wait.h>
#include <readline/readline.h>

void handle_sigquit(int sig)
{
    // 親プロセスでSIGQUITを処理
    printf("SIGQUIT received in parent process.\n");
}

// 端末設定の変更 (SIGQUITの動作を無効化)
void set_terminal_flags(int fd, int disable_signals)
{
    struct termios old_tio, new_tio;

    // 現在の端末設定を取得
    if (tcgetattr(fd, &old_tio) != 0)
    {
        perror("tcgetattr failed");
        return;
    }

    new_tio = old_tio;

    // ISIGフラグを無効化することで、SIGQUITやSIGINTのデフォルト動作を無効化
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

// 端末設定を元に戻す
void reset_terminal_flags(int fd, struct termios *old_tio)
{
    if (tcsetattr(fd, TCSANOW, old_tio) != 0)
    {
        perror("tcsetattr failed");
    }
}

int main(int ac, char **av, char **envp)
{
	const char *args[] = {"/bin/cat", NULL};

    signal(SIGQUIT, SIG_IGN);
    set_terminal_flags(STDIN_FILENO, 1);
    pid_t pid = fork();
    if (pid == 0)
	{
        signal(SIGQUIT, SIG_IGN);
        execve("/bin/cat", args, NULL);  // 例としてcatコマンドを実行
        perror("exec failed");  // execが失敗した場合の処理
        exit(EXIT_FAILURE);
	}
    else if (pid > 0)
    {  // 親プロセス
        wait(NULL);  // 子プロセスが終了するのを待つ
    } 
    struct termios old_tio;
	tcgetattr(STDIN_FILENO, &old_tio);
	reset_terminal_flags(STDIN_FILENO, &old_tio);  // 端末設定を元に戻す
    return 0;
}
