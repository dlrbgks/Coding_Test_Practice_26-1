//소수와 함께하는 여행
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 10000

int prime[MAX];
int visited[MAX];

typedef struct {
    int num;
    int cnt;
} Queue;

Queue queue[MAX];

int front, rear;

void makePrime() {

    for (int i = 0; i < MAX; i++)
        prime[i] = 1;

    prime[0] = prime[1] = 0;

    for (int i = 2; i * i < MAX; i++) {

        if (prime[i]) {

            for (int j = i * i; j < MAX; j += i)
                prime[j] = 0;
        }
    }
}

int bfs(int start, int target) {

    memset(visited, 0, sizeof(visited));

    front = rear = 0;

    queue[rear++] = (Queue){ start, 0 };

    visited[start] = 1;

    int placeVal[4] = { 1000, 100, 10, 1 };

    while (front < rear) {

        Queue cur = queue[front++];

        if (cur.num == target)
            return cur.cnt;

        for (int i = 0; i < 4; i++) {

            int place = placeVal[i];

            int currentDigit = (cur.num / place) % 10;

            for (int j = 0; j <= 9; j++) {

                if (j == currentDigit)
                    continue;

                // 천의 자리 0 x
                if (i == 0 && j == 0)
                    continue;

                // 새로운 숫자 
                int next =
                    cur.num
                    - currentDigit * place
                    + j * place;

                // 소수 + 미방문
                if (prime[next] && !visited[next]) {

                    visited[next] = 1;

                    queue[rear++] =
                        (Queue){ next, cur.cnt + 1 };
                }
            }
        }
    }

    return -1;
}

int main() {

    int start, target;

    scanf("%d %d", &start, &target);

    makePrime();

    printf("%d\n", bfs(start, target));

    return 0;
}