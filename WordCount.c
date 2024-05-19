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
        printf("�ַ�����%d\n", result);
    } else if (strcmp(param, "-w") == 0) {
        result = countWords(filename);
        printf("��������%d\n", result);
    } else {
        printf("����Ĳ�����������'-c'ͳ���ַ�����'-w'ͳ�Ƶ�������\n");
        return 1;
    }

    return 0;
}

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("�޷����ļ�");
        return -1;
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) { // ͳ�Ʒǿհ��ַ�
            count++;
        }
    }
    fclose(file);
    return count;
}

int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("�޷����ļ�");
        return -1;
    }

    bool inWord = false;
    int wordCount = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch) || ch == ',' || ch == '#') { // ��ĸ�����š�# ��Ϊ���ʲ���
            if (!inWord) {
                inWord = true;
                wordCount++;
            }
        } else if (isspace(ch)) { // �����ո񣬽�����ǰ����
            inWord = false;
        }
    }
    fclose(file);
    return wordCount;
}

