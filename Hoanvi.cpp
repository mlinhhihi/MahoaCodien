#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ColumnarEncrypt(char *plain, int key[], int klen, char *cipher) {
    int len = strlen(plain);
    int row = (len + klen - 1) / klen;
    char table[50][50];
    int idx = 0;

    for (int i = 0; i < row; i++)
        for (int j = 0; j < klen; j++)
            table[i][j] = ' ';

    for (int i = 0; i < row && idx < len; i++)
        for (int j = 0; j < klen && idx < len; j++)
            table[i][j] = plain[idx++];

    printf("MA TRAN HOAN VI:\n");
    printf("       ");
    for (int j = 0; j < klen; j++)
        printf("C%-3d", j + 1);
    printf("\n     -----------------------------\n");

    for (int i = 0; i < row; i++) {
        printf("H%-2d | ", i + 1);
        for (int j = 0; j < klen; j++)
            printf(" %c  ", table[i][j]);
        printf("\n");
    }

    idx = 0;
    printf("\nCAC BUOC MA HOA:");

    for (int i = 0; i < klen; i++) {
        int col = key[i] - 1;
        printf("\nDoc cot C%d: ", key[i]);

        for (int r = 0; r < row; r++) {
            if (table[r][col] != ' ') {
                cipher[idx++] = table[r][col];
                printf("%c ", table[r][col]);
            }
        }
    }

    cipher[idx] = '\0';
}

int main() {
    char plain[2000] = "";
    char cipher[2000];
    char keyStr[50];
    int key[50], klen;

    system("color F0");

    FILE *fPlain = fopen("Plain.txt", "r");
    if (!fPlain) {
        printf("Khong mo duoc file INPUT.txt\n");
        return 1;
    }
    fgets(plain, sizeof(plain), fPlain);
    fclose(fPlain);
    plain[strcspn(plain, "\n")] = '\0';

    FILE *fKey = fopen("Key.txt", "r");
    if (!fKey) {
        printf("Khong mo duoc file KEY.txt\n");
        return 1;
    }
    fgets(keyStr, sizeof(keyStr), fKey);
    fclose(fKey);
    keyStr[strcspn(keyStr, "\n")] = '\0';

    printf("BAN RO: %s\n", plain);
    printf("KHOA: %s\n", keyStr);

    klen = strlen(keyStr);
    for (int i = 0; i < klen; i++)
        key[i] = keyStr[i] - '0';

    ColumnarEncrypt(plain, key, klen, cipher);

    FILE *fout = fopen("Cipher.txt", "w");
    fprintf(fout, "%s", cipher);
    fclose(fout);

    printf("\nBAN MA: %s\n", cipher);
    return 0;
}

