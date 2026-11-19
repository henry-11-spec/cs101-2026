#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int n;
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要購買幾組樂透彩（1～5）：");

    if (scanf("%d", &n) != 1 || n < 1 || n > 5) {
        printf("請輸入 1 到 5 的整數。\n");
        return 1;
    }

    FILE *file = fopen("lotto.txt", "w");
    if (file == NULL) {
        perror("lotto.txt");
        return 1;
    }

    time_t now = time(NULL);
    srand((unsigned int)now);

    fprintf(file, "========= Lotto649 =========\n");
    fprintf(file, "%s", ctime(&now));

    for (int row = 1; row <= 5; row++) {
        fprintf(file, "[%d]:", row);

        if (row <= n) {
            int numbers[7];
            int used[70] = {0};

            for (int i = 0; i < 7; i++) {
                int number;
                do {
                    number = rand() % 69 + 1;
                } while (used[number]);

                numbers[i] = number;
                used[number] = 1;
            }

            /* 只排序前六個號碼 */
            for (int i = 0; i < 5; i++) {
                for (int j = i + 1; j < 6; j++) {
                    if (numbers[i] > numbers[j]) {
                        int temp = numbers[i];
                        numbers[i] = numbers[j];
                        numbers[j] = temp;
                    }
                }
            }

            for (int i = 0; i < 7; i++) {
                fprintf(file, " %02d", numbers[i]);
            }
        }
        fprintf(file, "\n");
    }

    fprintf(file, "========= csie@CGU =========\n");
    fclose(file);

    printf("已為您購買 %d 組樂透彩，請查看 lotto.txt。\n", n);
    return 0;
}
