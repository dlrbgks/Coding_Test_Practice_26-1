#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX 501

int graph[MAX][MAX];

int main() {

    int N, M;

    scanf("%d %d", &N, &M);

    // 입력
    for (int i = 0; i < M; i++) {

        int a, b;

        scanf("%d %d", &a, &b);

        graph[a][b] = 1;
    }

    // 꼼수 - 물어보니 플로이드 워셜이라네요
    for (int i = 1; i <= N; i++) {//경유

        for (int j = 1; j <= N; j++) {//시작

            for (int k = 1; k <= N; k++) {//끝

                if (graph[j][i] && graph[i][k]) {

                    graph[j][k] = 1;
                }
            }
        }
    }

    int answer = 0;

    // 검사
    for (int i = 1; i <= N; i++) {

        int count = 0;

        for (int j = 1; j <= N; j++) {

            // i < j, j < i
            if (graph[i][j] || graph[j][i]) {

                count++;
            }
        }

        // 자기 제외 비교 끝
        if (count == N - 1) {

            answer++;
        }
    }

    printf("%d\n", answer);

    return 0;
}