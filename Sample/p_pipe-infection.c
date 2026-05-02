#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 101

typedef struct {
    int to;
    int type;
} Edge;

Edge graph[MAXN][MAXN];
int deg[MAXN];

int n, k;
int max_result = 0;

// 방문 상태 저장
typedef struct {
    int infected[MAXN];
    int step;
} State;

State visited[100000];
int visited_count = 0;

// 상태 비교
int same_state(int* a, int* b) {
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

// 방문 여부 체크
int is_visited(int* infected, int step) {
    for (int i = 0; i < visited_count; i++) {
        if (visited[i].step != step) continue;
        if (same_state(visited[i].infected, infected))
            return 1;
    }
    return 0;
}

// 방문 저장
void add_visited(int* infected, int step) {
    for (int i = 1; i <= n; i++)
        visited[visited_count].infected[i] = infected[i];
    visited[visited_count].step = step;
    visited_count++;
}

// 감염 확산
void spread(int* infected, int type, int* result) {
    int queue[MAXN];
    int front = 0, rear = 0;

    int visited_local[MAXN] = { 0 };

    for (int i = 1; i <= n; i++) {
        if (infected[i]) {
            queue[rear++] = i;
            visited_local[i] = 1;
        }
    }

    while (front < rear) {
        int cur = queue[front++];

        for (int i = 0; i < deg[cur]; i++) {
            int nxt = graph[cur][i].to;
            int t = graph[cur][i].type;

            if (t == type && !visited_local[nxt]) {
                visited_local[nxt] = 1;
                queue[rear++] = nxt;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        result[i] = visited_local[i];
    }
}

// 감염 개수 세기
int count_infected(int* infected) {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (infected[i]) cnt++;
    return cnt;
}

// DFS 탐색
void dfs(int* infected, int step) {
    if (is_visited(infected, step)) return;
    add_visited(infected, step);

    int cnt = count_infected(infected);
    if (cnt > max_result) max_result = cnt;

    if (step == k) return;

    for (int t = 1; t <= 3; t++) {
        int new_infected[MAXN] = { 0 };

        spread(infected, t, new_infected);
        dfs(new_infected, step + 1);
    }
}

int solution(int N, int infection, int edges[][3], int edges_len, int K) {
    n = N;
    k = K;
    max_result = 0;
    visited_count = 0;

    for (int i = 1; i <= n; i++) {
        deg[i] = 0;
    }

    for (int i = 0; i < edges_len; i++) {
        int x = edges[i][0];
        int y = edges[i][1];
        int t = edges[i][2];

        graph[x][deg[x]++] = (Edge){ y, t };
        graph[y][deg[y]++] = (Edge){ x, t };
    }

    int infected[MAXN] = { 0 };
    infected[infection] = 1;

    dfs(infected, 0);

    return max_result;
}

int main() {
    int n = 10;
    int infection = 1;
    int k = 2;

    int edges[9][3] = {
        {1, 2, 1}, {1, 3, 1}, {1, 4, 3}, {1, 5, 2},
        {5, 6, 1}, {5, 7, 1}, {2, 8, 3}, {2, 9, 2}, {9, 10, 1}
    };

    int result = solution(n, infection, edges, 9, k);
    printf("최대 감염 수: %d\n", result);

    return 0;
}