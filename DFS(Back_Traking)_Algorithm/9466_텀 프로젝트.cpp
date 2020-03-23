/*
	이번 가을학기에 '문제 해결' 강의를 신청한 학생들은 텀 프로젝트를 수행해야 한다. 프로젝트 팀원 수에는 제한이 없다. 
	심지어 모든 학생들이 동일한 팀의 팀원인 경우와 같이 한 팀만 있을 수도 있다. 
	프로젝트 팀을 구성하기 위해, 모든 학생들은 프로젝트를 함께하고 싶은 학생을 선택해야 한다. (단, 단 한 명만 선택할 수 있다.) 
	혼자 하고 싶어하는 학생은 자기 자신을 선택하는 것도 가능하다.
	
	학생들이(s1, s2, ..., sr)이라 할 때, r=1이고 s1이 s1을 선택하는 경우나, 
	s1이 s2를 선택하고, s2가 s3를 선택하고,..., sr-1이 sr을 선택하고, sr이 s1을 선택하는 경우에만 한 팀이 될 수 있다.

	주어진 선택의 결과를 보고 어느 프로젝트 팀에도 속하지 않는 학생들의 수를 계산하는 알고리즘을 구현해라

	DFS, 재귀를 활용하여 브루트포스를 하여 팀을 구성하는 알고리즘 구현. 
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int N;
int student[100001]; // 학생 각각이 원하는 팀원..
bool check[100001]; // 팀이 이루어졌는지 판단.
int tmp[100001]; // 팀이 이루어지면 팀이 이루어진 학생을 판단하기 위해..
bool flag;
int cnt;

void solve(int depth, int person, int start);

int main() {
	int T; scanf("%d", &T); // 테스트 케이스를 위해..
	for (int t = 0; t < T; t++) {

		scanf("%d", &N); // 학생 수
		cnt = N; // cnt == N을 한 이유는 팀이 이루어진 사람들을 빼고 팀에 속하지 못한 학생 수를 뽑기위해
		for (int a, i = 1; i <= N; i++) {
			scanf("%d", &a);
			if (a == i) { // 자기혼자 팀이 되고싶은 학생들을 미리 배재..
				check[i] = true;
				cnt--;
			}
			student[i] = a;
		}
		for (int i = 1; i <= N; i++) { // 1 ~ N번학생까지 팀이 아직 이루어지지 않았으면 브루트포스..
			if (!check[i]) {
				flag = false;
				solve(0, i, student[i]); //depth, 자기 자신, 원하는 학생..
			}
		}

		printf("%d\n", cnt);
		memset(check, false, sizeof(check)); // 테스트케이스를 위한 check함수 초기화

	}
	return 0;
}

void solve(int depth, int person, int want) {

	if (want < person) return; // person 은 자기 자신, want는 학생이 원하는 사람으로 1부터 시작해서 한명씩 보고있으므로 같은 곳을 또 들어가지 않기 위해..
								//만약 이 한 문장을 넣지 않을경우 시간초과가 발생한다..

	if (flag) {
		check[person] = true; // 자기 자신 check
		cnt -= depth + 1; // 결과값을 얻기 위해 cnt - depth + 1;
		for (int i = 0; i < depth; i++) { // 팀이 구성된 학생들을 check..
			check[tmp[i]] = true;
		}
		return;
	}
	if (depth >= N) return; // 무한히 재귀를 들어가는 것을 방지하기위해..
	if (check[want]) return; // 원하는 학생을 찾으면 리턴..

	if (!check[want]) { // 아직 구성되지 않은 학생일 때...
		if (student[want] != person) { // 원하는 학생이 아니면..
			tmp[depth] = want; // 나중 원하는 학생이 나왔을 때 check를 하기위해..
			solve(depth + 1, person, student[want]); // depth증가, 학생, 원하는 학생.??..
		}
		else {// 원하는 학생일 경우에게 도달하였을 경우..
			flag = true;
			tmp[depth] = want;
			solve(depth + 1, person, student[want]);
		}
	}
}