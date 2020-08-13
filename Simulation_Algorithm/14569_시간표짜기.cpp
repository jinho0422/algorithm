#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M; // N : 과목수 M : 학생수
int subNumber[10000]; // 학생이 들을 수 있는 후보과목의 수 저장

vector<int> subject[1000][6]; //과목등록배열
int student[10000][6][11]; // 학생이 들을 수 있는 요일과 시간 등록 배열

bool solve(int first, int second);

int main() {
	//입력
	scanf("%d", &N);
	//과목입력
	for (int s, i = 0; i < N; i++) {
		scanf("%d", &s);
		for (int t, j = 0; j < s; j++) {
			scanf("%d", &t);
			subject[i][t / 10].push_back(t % 10); // t / 10 : 요일 t % 10은 시간을 저장
		}
	}
	scanf("%d", &M);
	for (int s, i = 0; i < M; i++) {
		scanf("%d", &s);
		for (int t, j = 0; j < s; j++) {
			scanf("%d", &t);
			student[i][t / 10][t % 10]++;
		}
	}
	// 과목하나씩 학생의 시간에 맞춰본다..
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			bool flag = solve(i, j);
			//flag == true이면 후보과목이 가능하므로 subNumber를 증가시켜준다
			if (flag) subNumber[j]++;
		}
	}
	//출력
	for (int i = 0; i < M; i++) {
		printf("%d\n", subNumber[i]);
	}
	return 0;
}
// 과목과 학생을 비교했을 때 과목이 원하는 시간이 모두 학생에게 들어있으면 true를 반환 하나라도 없으면 false를 반환
bool solve(int first, int second) {
	for (int i = 0; i <= 5; i++) {
		int sz = subject[first][i].size();
		for (int j = 0; j < sz; j++) {
			if (student[second][i][subject[first][i][j]] == 0) return false;
		}
	}
	return true;
}