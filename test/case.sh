# SUCCESS ✅
echo "Hello World" > file.txt | cat file.txt
echo "Hello World" > file1.txt > file2.txt | tee file3.txt
cat < s1 | cat -e
cat < file_list.txt | grep "file"

# FAILE 

# 未達成
ls | grep "file"
ls | grep "file" | sort
ls > file_list.txt | cat -e
ls > file_list.txt | cat -e

# 出力リダイレクトと標準入力リダイレクトの組み合わせ
echo "Input" > input.txt
cat < input.txt > output.txt
cat output.txt
echo "Input" > input.txt | cat < input.txt > output.txt | cat output.txt

# パイプと複数のリダイレクト
ls | tee file_list.txt | grep "file" > filtered.txt
cat filtered.txt