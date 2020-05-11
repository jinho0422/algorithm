]#include <string>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

char op[100];
int numbers[100];
int tmp[100];
int check[100];
int cc[101];
long long result;

queue<char> Q;

void solve(int depth, int endd);

long long solution(string expression) {
    long long answer = 0;
    int opcnt = 0;
    int numcnt = 0;
    int checknum = 0;
    int pownum = 0;
    int sz = expression.size();
    for (int s = sz - 1; s >= 0; s--) {
        if (expression[s] == '*' || expression[s] == '-' || expression[s] == '+') {
            op[opcnt++] = expression[s];
            numbers[numcnt++] = checknum;
            checknum = 0;
            pownum = 0;
        }
        if (expression[s] >= '0' && expression[s] <= '9') {
            int ee = expression[s] - '0';
            checknum += ee * pow(10, pownum);
            pownum++;
            if (s == 0) numbers[numcnt++] = checknum;
        }
    }
    for (int s = 0; s < numcnt; s++) {
        printf("%d ", numbers[s]);
    }
    for (int s = 0; s < opcnt; s++) {
        printf("%c ", op[s]);
    }


    solve(0, numcnt);
    answer = result;

    return answer;
}

void solve(int depth, int endd) {
    if (depth == endd) {
        long long sum = 0;
        int x = 0;

        sum = numbers[tmp[0]];
        for (int s = 0; s < depth; s++) {
            printf("%d ", tmp[s]);
        }
        printf("\n");

        for (int s = 0; s < depth - 1; s++) {
            if (op[tmp[s]] == '+') {
                sum += numbers[tmp[s] + 1];
            }
            if (op[tmp[s]] == '-') {
                sum -= numbers[tmp[s] + 1];
            }
            if (op[tmp[s]] == '*') {
                sum *= numbers[tmp[s] + 1];
            }
        }
        printf("%lld\n", sum);

        if (result < abs(sum)) result = abs(sum);
        return;
    }

    for (int i = 0; i < endd; i++) {
        if (!check[i]) {
            check[i] = true;
            tmp[depth] = i;
            solve(depth + 1, endd);
            tmp[depth] = 0;
            check[i] = false;
        }
    }
}