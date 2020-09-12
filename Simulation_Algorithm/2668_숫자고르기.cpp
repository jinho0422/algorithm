#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int numbers[101];

vector<int> Vec;

int main() {
    scanf("%d", &N);
    for (int a, i = 1; i <= N; i++) {
        scanf("%d", &a);
        Vec.push_back(a);
    }
    sort(Vec.begin(), Vec.end());
    int sz = Vec.size();
    int num = 0;
    for (int s = 0; s < sz; s++) {
        if (s + 1 == Vec[s]) {
            numbers[num++] = Vec[s];
        }
    }
    printf("%d\n", num);
    for (int s = 0; s < num; s++) {
        printf("%d\n", numbers[s]);
    }

    return 0;
}