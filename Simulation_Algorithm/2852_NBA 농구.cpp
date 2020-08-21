#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N;
int G;
int team[2];
bool flagTeam; // false : team1 : 승리중, true : team2 : 승리중
char str[20];
int result[2];
int minute, second;
int beforeM;


// 팀이 이기고 있는 시간부터 beforeM에 저장하여 동점이 됬을 때 이기고 있던 팀에게 시간을 전달..
int main() {
	scanf("%d", &N);
	int flag = false;
	for (int i = 0; i < N; i++) {
		scanf("%d %s", &G, str);
		minute = ((str[0] - '0') * 10 + (str[1] - '0')) * 60;
		second = (str[3] - '0') * 10 + (str[4] - '0');
		team[G -1]++;
		// 0팀이 이길때.. flag는 계속적으로 이기고 있으면 이전 시간을 갱신하지 않기 위해
		if (team[0] > team[1] && !flag) {
			flagTeam = true;
			flag = true;
			beforeM = minute + second;
		}
		//1팀이 이길때..
		else if (team[0] < team[1] && !flag) {
			flagTeam = false;
			flag = true;
			beforeM = minute + second;
		}
		// 비길 때..
		else if (team[0] == team[1] && flag) {
			if (flagTeam) {
				result[0] += ((minute + second) - beforeM);
				beforeM = 0;
				flag = false;
			}
			else {
				result[1] += ((minute + second) - beforeM);
				beforeM = 0;
				flag = false;
			}
		}
	}
	// 48분까지이므로 마지막으로 이기고 있었으면 시간을 이긴팀에 더해준다.
	if (team[0] > team[1]) result[0] += ((48 * 60) - beforeM);
	
	else if (team[0] < team[1]) result[1] += ((48 * 60) - beforeM);
	
	for (int i = 0; i < 2; i++) printf("%02d:%02d\n", result[i] / 60, result[i] % 60);
	return 0;
}