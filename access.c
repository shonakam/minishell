#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // コマンドライン引数の数が正しいか確認
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // ファイルパスの取得
    char *path = argv[1];

    // ファイルが存在するか確認
    if (access(path, F_OK) == 0)
    {
        printf("File exists: %s\n", path);

        // ファイルが読み込み可能か確認
        if (access(path, R_OK) == 0)
        {
            printf("File is readable: %s\n", path);
        }
        else
        {
            printf("File is not readable: %s\n", path);
        }
    }
    else
    {
        printf("File does not exist: %s\n", path);
    }

    return 0;
}
