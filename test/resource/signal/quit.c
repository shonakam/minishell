#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigquit(int sig)
{
    printf("SIGQUIT received! Signal number: %d\n", sig);
}

int main(void)
{
    // SIGQUITに対するシグナルハンドラを設定
    signal(SIGQUIT, handle_sigquit);

    printf("Running... Press Ctrl + \\ to send SIGQUIT\n");

    // プログラムが終了しないように無限ループ
    while (1)
    {
        sleep(1); // 1秒待機
    }

    return 0;
}
