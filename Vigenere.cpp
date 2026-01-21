#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void VigenereEncrypt(char *plain, char *key, char *cipher) {
    int i, j = 0;
    int lenP = strlen(plain);
    int lenK = strlen(key);

    printf("\nCAC BUOC MA HOA VIGENERE:\n");
    printf("Cong thuc: C = (P + K) mod 26\n\n");

    for (i = 0; i < lenP; i++) {
        if (isalpha(plain[i])) {
            int p = toupper(plain[i]) - 'A';
            int k = toupper(key[j % lenK]) - 'A';
            int c = (p + k) % 26;

            cipher[i] = c + 'A';

            printf("P=%c(%2d) + K=%c(%2d) = (%2d + %2d) %% 26 = %2d -> %c\n",
                   toupper(plain[i]), p,
                   toupper(key[j % lenK]), k,
                   p, k, c,
                   cipher[i]);

            j++;
        } else {
            cipher[i] = plain[i]; 
        }
    }
    cipher[lenP] = '\0';
}

int main() {
    char plain[1000] = "";
    char buffer[1000];
    char key[100];
    char cipher[1000];

    system("color F0");

    FILE *fPlain = fopen("Plain.txt", "r");
    if (fPlain == NULL) {
        printf("Khong mo duoc file Plain.txt\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), fPlain) != NULL) {
        strcat(plain, buffer);
    }
    fclose(fPlain);

    FILE *fKey = fopen("Key.txt", "r");
    if (fKey == NULL) {
        printf("Khong mo duoc file Key.txt\n");
        return 1;
    }
    fgets(key, sizeof(key), fKey);
    fclose(fKey);
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) == 0) {
        printf("Khoa khong duoc rong!\n");
        return 1;
    }

    printf("DU LIEU VAO:\n");
    printf("Ban ro: %s\n", plain);
    printf("Khoa: %s\n", key);

    VigenereEncrypt(plain, key, cipher);

    FILE *fCipher = fopen("Cipher.txt", "w");
    if (fCipher == NULL) {
        printf("Khong mo duoc file Cipher.txt\n");
        return 1;
    }
    fprintf(fCipher, "%s", cipher);
    fclose(fCipher);

    printf("\nBAN MA: %s\n", cipher);

    return 0;
}

