#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N;
int G;
int team[2];
bool flagTeam; // false : team1 : �¸���, true : team2 : �¸���
char str[20];
int result[2];
int minute, second;
int beforeM;


// ���� �̱�� �ִ� �ð����� beforeM�� �����Ͽ� ������ ���� �� �̱�� �ִ� ������ �ð��� ����..
int main() {
	scanf("%d", &N);
	int flag = false;
	for (int i = 0; i < N; i++) {
		scanf("%d %s", &G, str);
		minute = ((str[0] - '0') * 10 + (str[1] - '0')) * 60;
		second = (str[3] - '0') * 10 + (str[4] - '0');
		team[G -1]++;
		// 0���� �̱涧.. flag�� ��������� �̱�� ������ ���� �ð��� �������� �ʱ� ����
		if (team[0] > team[1] && !flag) {
			flagTeam = true;
			flag = true;
			beforeM = minute + second;
		}
		//1���� �̱涧..
		else if (team[0] < team[1] && !flag) {
			flagTeam = false;
			flag = true;
			beforeM = minute + second;
		}
		// ��� ��..
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
	// 48�б����̹Ƿ� ���������� �̱�� �־����� �ð��� �̱����� �����ش�.
	if (team[0] > team[1]) result[0] += ((48 * 60) - beforeM);
	
	else if (team[0] < team[1]) result[1] += ((48 * 60) - beforeM);
	
	for (int i = 0; i < 2; i++) printf("%02d:%02d\n", result[i] / 60, result[i] % 60);
	return 0;
}