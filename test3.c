#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigquit(int sig)
{
    write(STDOUT_FILENO, "\b\b", 2);
    fflush(stdout);  
}

int main() {
    // SIGQUITのデフォルト動作を無効にする（終了を防ぐ）
    signal(SIGQUIT, handle_sigquit);  // SIGQUITを捕まえてhandle_sigquitを呼ぶ

    // 無限ループでシグナルを待機
    const char *args[] = {"/bin/cat", NULL};  // 例としてcatコマンド
    execve(args[0], (char *const *)args, NULL);  // execveでcatを実行

    return 0;
}
