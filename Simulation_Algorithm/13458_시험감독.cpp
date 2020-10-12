#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
int board[1000001];
int first, second;
long long result;

int main() {
	//입력
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	//first : 총감독이 맡을 수 있는 인원, second : 부 감독이 맡을 수 있는 인원
	scanf("%d %d", &first, &second);
	result = N; // 총감독은 항상 고사장에 한명씩 있어야되므로
	for (int i = 0; i < N; i++) {
		int s = board[i] - first; // 고사장인원에서 총감독이 맡을 수 인원을 빼고
		if (s <= 0) continue; // 0보다 작으면 continue..
		result += (s / second); // 몫을 result에 더해주고
		int f = s % second;  
		if (f != 0) result++; //나머지가 있으면 부감독을 한명 더 포함시킨다..
	}
	// 출력
	printf("%lld\n", result);
	return 0;
}