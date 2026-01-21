#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char matrix[5][5];

void generateMatrix(char *key) {
    int used[26] = {0}, k = 0;

    for (int i = 0; key[i]; i++) {
        char c = toupper(key[i]);
        if (!isalpha(c)) continue;
        if (c == 'J') c = 'I';

        if (!used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
}

void printMatrix() {
    printf("Ma tran khoa Playfair (5x5):\n");
    printf("      j=0  j=1  j=2  j=3  j=4\n");
    printf("    -------------------------\n");

    for (int i = 0; i < 5; i++) {
        printf("i=%d | ", i);
        for (int j = 0; j < 5; j++) {
            printf(" %c   ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findPos(char c, int *r, int *c1) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c) {
                *r = i;
                *c1 = j;
                return;
            }
}

void preprocess(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) {
            char c = toupper(input[i]);
            if (c == 'J') c = 'I';
            output[j++] = c;
        }
    }
    output[j] = '\0';
}

void PlayfairEncrypt(char *plain, char *cipher) {
    int i = 0, k = 0;

    printf("\nCAC BUOC MA HOA PLAYFAIR:\n");

    while (plain[i]) {
        char a = plain[i];
        char b;

        if (plain[i + 1] == '\0')
            b = 'X';
        else if (plain[i] == plain[i + 1])
            b = 'X';
        else
            b = plain[i + 1];

        int r1, c1, r2, c2;
        findPos(a, &r1, &c1);
        findPos(b, &r2, &c2);

        printf("Cap: %c %c\n", a, b);
        printf("  %c -> (%d,%d)\n", a, r1, c1);
        printf("  %c -> (%d,%d)\n", b, r2, c2);

        if (r1 == r2) {
            printf("  Quy tac: Cung hang\n");
            cipher[k++] = matrix[r1][(c1 + 1) % 5];
            cipher[k++] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            printf("  Quy tac: Cung cot\n");
            cipher[k++] = matrix[(r1 + 1) % 5][c1];
            cipher[k++] = matrix[(r2 + 1) % 5][c2];
        }
        else {
            printf("  Quy tac: Hinh chu nhat\n");
            cipher[k++] = matrix[r1][c2];
            cipher[k++] = matrix[r2][c1];
        }

        printf("  -> %c%c\n\n", cipher[k - 2], cipher[k - 1]);

        if (b == 'X' && a == plain[i + 1])
            i += 1;
        else
            i += 2;
    }

    cipher[k] = '\0';
}

int main() {
    char plain[2000] = "";
    char buffer[300];
    char clean[2000];
    char key[100];
    char cipher[2000];

    system("color F0");

    FILE *fPlain = fopen("Plain.txt", "r");
    if (!fPlain) {
        printf("Khong mo duoc file Plain.txt\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), fPlain))
        strcat(plain, buffer);
    fclose(fPlain);

    FILE *fKey = fopen("Key.txt", "r");
    if (!fKey) {
        printf("Khong mo duoc file Key.txt\n");
        return 1;
    }
    fgets(key, sizeof(key), fKey);
    fclose(fKey);
    key[strcspn(key, "\n")] = '\0';

    printf("BAN RO: %s\n", plain);
    printf("KHOA: %s\n", key);

    generateMatrix(key);
    printMatrix();

    preprocess(plain, clean);
    PlayfairEncrypt(clean, cipher);

    FILE *fCipher = fopen("Cipher.txt", "w");
    if (!fCipher) {
        printf("Khong mo duoc file Cipher.txt\n");
        return 1;
    }
    fprintf(fCipher, "%s", cipher);
    fclose(fCipher);

    printf("BAN MA: %s\n", cipher);

    return 0;
}

