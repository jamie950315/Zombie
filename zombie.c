#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SIZE=3;

void drawBoard(int zombieX, int zombieY) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == zombieX && j == zombieY) {
                printf("Z ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main() {
    int score = 0;
    int zombieX, zombieY;
    int userX, userY;
    char playAgain;

    srand(time(NULL));

    do {
        zombieX = rand() % SIZE;
        zombieY = rand() % SIZE;

        printf("打殭屍遊戲！\n");
        drawBoard(zombieX, zombieY);

        printf("請輸入你要打的位置 (格式: x y): ");
        scanf("%d %d", &userX, &userY);

        if (userX == zombieX && userY == zombieY) {
            score++;
            printf("打對了！目前得分: %d\n", score);
        } else {
            printf("打錯了！遊戲結束。最終得分: %d\n", score);
            break;
        }

        printf("要繼續玩嗎？(y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}