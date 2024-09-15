/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:09:07 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/15 16:55:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

unsigned long get_time_macOS()
{
    struct timeval tv;
    unsigned int ret;

    __asm__ (
        "mov x8, #0x74\n"        // システムコール番号 116 (gettimeofday) の16進数表現
        "mov x0, %[tv_ptr]\n"    // 引数1: struct timeval * を x0 レジスタにセット
        "mov x1, 0\n"            // 引数2: NULL を x1 レジスタにセット
        "svc #0\n"               // システムコールを実行
        "mov %w[ret], w0\n"      // システムコールの戻り値を ret 変数に保存 (32ビット)
        : [ret] "=r" (ret)       // 出力オペランド
        : [tv_ptr] "r" (&tv)     // 入力オペランド
        : "x0", "x1", "x8"       // 使用するレジスタ
    );

    if (ret == -1) {
        perror("syscall");
        return 0;
    }

    return (unsigned long)tv.tv_sec;  // 秒数を返す
}

int main()
{
	unsigned long time = get_time_macOS();
	printf("Current time: %lu\n", time);
	return 0;
}