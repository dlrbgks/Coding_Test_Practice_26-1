#include <stdio.h>

int solution(int wallet[2], int bill[2]) {
    int answer = 0;

    // wallet 정렬
    int w_small = wallet[0] < wallet[1] ? wallet[0] : wallet[1];
    int w_big = wallet[0] > wallet[1] ? wallet[0] : wallet[1];

    while (1) {
        // bill 정렬
        int b_small = bill[0] < bill[1] ? bill[0] : bill[1];
        int b_big = bill[0] > bill[1] ? bill[0] : bill[1];

        // 들어가면 종료
        if (b_small <= w_small && b_big <= w_big)
            break;

        // 긴 쪽 접기
        if (bill[0] > bill[1])
            bill[0] /= 2;
        else
            bill[1] /= 2;

        answer++;
    }

    return answer;
}

int main() {
    int wallet1[2] = { 30, 15 };
    int bill1[2] = { 26, 17 };

    int wallet2[2] = { 50, 50 };
    int bill2[2] = { 100, 241 };

    printf("%d\n", solution(wallet1, bill1)); // 1
    printf("%d\n", solution(wallet2, bill2)); // 4

    return 0;
}