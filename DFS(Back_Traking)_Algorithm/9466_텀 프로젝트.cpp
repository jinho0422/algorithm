/*
	�̹� �����б⿡ '���� �ذ�' ���Ǹ� ��û�� �л����� �� ������Ʈ�� �����ؾ� �Ѵ�. ������Ʈ ���� ������ ������ ����. 
	������ ��� �л����� ������ ���� ������ ���� ���� �� ���� ���� ���� �ִ�. 
	������Ʈ ���� �����ϱ� ����, ��� �л����� ������Ʈ�� �Բ��ϰ� ���� �л��� �����ؾ� �Ѵ�. (��, �� �� �� ������ �� �ִ�.) 
	ȥ�� �ϰ� �;��ϴ� �л��� �ڱ� �ڽ��� �����ϴ� �͵� �����ϴ�.
	
	�л�����(s1, s2, ..., sr)�̶� �� ��, r=1�̰� s1�� s1�� �����ϴ� ��쳪, 
	s1�� s2�� �����ϰ�, s2�� s3�� �����ϰ�,..., sr-1�� sr�� �����ϰ�, sr�� s1�� �����ϴ� ��쿡�� �� ���� �� �� �ִ�.

	�־��� ������ ����� ���� ��� ������Ʈ ������ ������ �ʴ� �л����� ���� ����ϴ� �˰����� �����ض�

	DFS, ��͸� Ȱ���Ͽ� ���Ʈ������ �Ͽ� ���� �����ϴ� �˰��� ����. 
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
int student[100001]; // �л� ������ ���ϴ� ����..
bool check[100001]; // ���� �̷�������� �Ǵ�.
int tmp[100001]; // ���� �̷������ ���� �̷���� �л��� �Ǵ��ϱ� ����..
bool flag;
int cnt;

void solve(int depth, int person, int start);

int main() {
	int T; scanf("%d", &T); // �׽�Ʈ ���̽��� ����..
	for (int t = 0; t < T; t++) {

		scanf("%d", &N); // �л� ��
		cnt = N; // cnt == N�� �� ������ ���� �̷���� ������� ���� ���� ������ ���� �л� ���� �̱�����
		for (int a, i = 1; i <= N; i++) {
			scanf("%d", &a);
			if (a == i) { // �ڱ�ȥ�� ���� �ǰ���� �л����� �̸� ����..
				check[i] = true;
				cnt--;
			}
			student[i] = a;
		}
		for (int i = 1; i <= N; i++) { // 1 ~ N���л����� ���� ���� �̷������ �ʾ����� ���Ʈ����..
			if (!check[i]) {
				flag = false;
				solve(0, i, student[i]); //depth, �ڱ� �ڽ�, ���ϴ� �л�..
			}
		}

		printf("%d\n", cnt);
		memset(check, false, sizeof(check)); // �׽�Ʈ���̽��� ���� check�Լ� �ʱ�ȭ

	}
	return 0;
}

void solve(int depth, int person, int want) {

	if (want < person) return; // person �� �ڱ� �ڽ�, want�� �л��� ���ϴ� ������� 1���� �����ؼ� �Ѹ� ���������Ƿ� ���� ���� �� ���� �ʱ� ����..
								//���� �� �� ������ ���� ������� �ð��ʰ��� �߻��Ѵ�..

	if (flag) {
		check[person] = true; // �ڱ� �ڽ� check
		cnt -= depth + 1; // ������� ��� ���� cnt - depth + 1;
		for (int i = 0; i < depth; i++) { // ���� ������ �л����� check..
			check[tmp[i]] = true;
		}
		return;
	}
	if (depth >= N) return; // ������ ��͸� ���� ���� �����ϱ�����..
	if (check[want]) return; // ���ϴ� �л��� ã���� ����..

	if (!check[want]) { // ���� �������� ���� �л��� ��...
		if (student[want] != person) { // ���ϴ� �л��� �ƴϸ�..
			tmp[depth] = want; // ���� ���ϴ� �л��� ������ �� check�� �ϱ�����..
			solve(depth + 1, person, student[want]); // depth����, �л�, ���ϴ� �л�.??..
		}
		else {// ���ϴ� �л��� ��쿡�� �����Ͽ��� ���..
			flag = true;
			tmp[depth] = want;
			solve(depth + 1, person, student[want]);
		}
	}
}