#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int countCharacters(const char *filename);
int countWords(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] input_file_name\n", argv[0]);
        return 1;
    }

    const char *param = argv[1];
    const char *filename = argv[2];

    int result;
    if (strcmp(param, "-c") == 0) {
        result = countCharacters(filename);
        printf("字符数：%d\n", result);
    } else if (strcmp(param, "-w") == 0) {
        result = countWords(filename);
        printf("单词数：%d\n", result);
    } else {
        printf("错误的参数！请输入'-c'统计字符数或'-w'统计单词数。\n");
        return 1;
    }

    return 0;
}

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开文件");
        return -1;
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) { // 统计非空白字符
            count++;
        }
    }
    fclose(file);
    return count;
}

int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开文件");
        return -1;
    }

    bool inWord = false;
    int wordCount = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == ',' || ch == '#') { // 字母、逗号、# 视为单词部分
            if (!inWord) {
                inWord = true;
                wordCount++;
            }
        } else if (isspace(ch)) { // 遇到空格，结束当前单词
            inWord = false;
        }
    }
    fclose(file);
    return wordCount;
}

