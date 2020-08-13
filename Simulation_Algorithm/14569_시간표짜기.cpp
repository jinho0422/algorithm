#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N, M; // N : ����� M : �л���
int subNumber[10000]; // �л��� ���� �� �ִ� �ĺ������� �� ����

vector<int> subject[1000][6]; //�����Ϲ迭
int student[10000][6][11]; // �л��� ���� �� �ִ� ���ϰ� �ð� ��� �迭

bool solve(int first, int second);

int main() {
	//�Է�
	scanf("%d", &N);
	//�����Է�
	for (int s, i = 0; i < N; i++) {
		scanf("%d", &s);
		for (int t, j = 0; j < s; j++) {
			scanf("%d", &t);
			subject[i][t / 10].push_back(t % 10); // t / 10 : ���� t % 10�� �ð��� ����
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
	// �����ϳ��� �л��� �ð��� ���纻��..
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			bool flag = solve(i, j);
			//flag == true�̸� �ĺ������� �����ϹǷ� subNumber�� ���������ش�
			if (flag) subNumber[j]++;
		}
	}
	//���
	for (int i = 0; i < M; i++) {
		printf("%d\n", subNumber[i]);
	}
	return 0;
}
// ����� �л��� ������ �� ������ ���ϴ� �ð��� ��� �л����� ��������� true�� ��ȯ �ϳ��� ������ false�� ��ȯ
bool solve(int first, int second) {
	for (int i = 0; i <= 5; i++) {
		int sz = subject[first][i].size();
		for (int j = 0; j < sz; j++) {
			if (student[second][i][subject[first][i][j]] == 0) return false;
		}
	}
	return true;
}