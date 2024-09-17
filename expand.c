#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *expand_string(const char *input) {
    size_t input_len = strlen(input);
    char *output = malloc(1024); // 出力バッファ
    size_t out_len = 0;

    int in_single_quote = 0;
    int in_double_quote = 0;

    for (size_t i = 0; i < input_len; i++) {
        char c = input[i];

        if (c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote; // シングルクォートのトグル
            continue; // クォート自体は出力に含めない
        }
        if (c == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote; // ダブルクォートのトグル
            continue; // クォート自体は出力に含めない
        }

        // 変数展開の処理（例として簡略）
        if (in_double_quote && c == '$' && isalnum(input[i + 1])) {
            // 環境変数を処理する部分（簡略）
            i++; // 次の文字を見て変数名を取得
            while (isalnum(input[i])) {
                output[out_len++] = input[i++];
            }
            output[out_len++] = ' '; // 変数展開をスペースで区切る簡略的な方法
            i--; // インデックスを調整
        } else {
            output[out_len++] = c; // そのまま出力
        }
    }

    output[out_len] = '\0'; // 終端文字を追加
    return output; // 出力を返す
}

int main() {
    const char *input = "Hello '$USER', today is \"$DAY\"!";
    char *output = expand_string(input);

    printf("Expanded string: %s\n", output);
    free(output); // メモリを解放
    return 0;
}