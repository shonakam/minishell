#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_rdir {
	char	*file;
	int		mode;
	int		rdir_fd;
	int		out_backup;
	int		in_backup;
}				t_rdir;

void handle_input_redirection(t_rdir *rdir)
{
    // 標準入力のバックアップを取る
    rdir->in_backup = dup(STDIN_FILENO);

    // 入力用のファイルを開く
    rdir->rdir_fd = open(rdir->file, O_RDONLY);
    if (rdir->rdir_fd < 0) {
        perror("open error");
        return;
    }

    // 標準入力をファイルにリダイレクト
    dup2(rdir->rdir_fd, STDIN_FILENO);

    // ファイルディスクリプタを閉じる
    close(rdir->rdir_fd);
}

void restore_input_redirection(t_rdir *rdir)
{
    // 標準入力を元に戻す
    dup2(rdir->in_backup, STDIN_FILENO);
    close(rdir->in_backup);
}

int main()
{
    t_rdir rdir;

    // 入力リダイレクトするファイル名を指定
    rdir.file = "input.txt";

    // 入力リダイレクト処理
    handle_input_redirection(&rdir);

    // コマンド実行 (例: cat コマンド)
    execlp("cat", "cat", NULL);

    // リダイレクト解除
    restore_input_redirection(&rdir);

    return 0;
}
