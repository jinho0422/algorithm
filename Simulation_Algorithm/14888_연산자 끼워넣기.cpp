#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, num;
int board[101]; // 연산해야될 값이 있는 배열
int oper[100]; // 연산자가 들어있는 배열 0 : +, 1 : -, 2 : *, 3 : / 
int tmpOper[100]; // 연산자를 순열을 통해 가져온 배열
bool check[101]; 
int maxResult, minResult; // 최대값, 최소값

void DFS(int depth);

int main() {
	//입력
	maxResult = -2000000000;
	minResult = 2000000000;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	num = 0;
	for (int a, i = 0; i < 4; i++) {
		scanf("%d", &a);
		for (int j = 0; j < a; j++) {
			oper[num++] = i; // 연산자를 숫자로 넣기..
		}
	}
	DFS(0);
	printf("%d\n%d\n", maxResult, minResult);
	return 0;
}
// 연산
int operating(int s, int sums, int nextNum ) {
	if (s == 0) sums += nextNum;
	else if (s == 1) sums -= nextNum;
	else if (s == 2) sums *= nextNum;
	else if (s == 3) sums /= nextNum;
	return sums;
}
//순열을 통해 연산자를 모두 고르고 연산하기..
void DFS(int depth) {
	if (depth == N -1) {
		int sum = board[0];
		for (int i = 0; i < depth; i++) {
			sum = operating(tmpOper[i], sum, board[i + 1]);
		}
		//결과값갱신..
		if (maxResult < sum) maxResult = sum;
		if (minResult > sum) minResult = sum;
		return;
	}
	for (int i = 0; i < num; i++) {
		if (!check[i]) {
			check[i] = true;
			tmpOper[depth] = oper[i];
			DFS(depth + 1);
			tmpOper[depth] = 0;
			check[i] = false;
		}
	}
}