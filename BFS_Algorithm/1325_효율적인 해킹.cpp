/*
 ȿ������ ��ŷ ������ N���� ��ǻ�ͷ� �̷�����ִ� ȸ�翡�� 
 �ѹ��� �a������ ���� ���� ��ǻ�͸� ��ŷ �� �� �ִ� ��ǻ�͸� ��ŷ�Ϸ����ϴ� ����.
 ��ǻ�ʹ� �ŷ��ϴ� ����� �ŷ����� �ʴ� ����� �̷���� �ִµ�,
 A�� B�� �ŷ��ϴ� ��쿡�� B�� ��ŷ�ϸ� A�� ��ŷ�� �� �ִٴ� ���̴�.
 

  5���� �ð��̶�� ���� Ȱ���Ͽ� BFS�� 1~N ������ ��ǻ�͸� ��ŷ���� �� ���� ��ŷ�Ǿ����� ��ǻ���� ������ ã�� ������� ���� ���̴�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
bool check[10001]; // �ѹ�üũ�� ��ǻ�ʹ� �� üũ���� �ʱ�����.
int result;

vector<int> Vec[10001]; // �ŷڰ����� ��ǻ�͸� �Է��ϱ� ����..
queue<int> Q; // �ϳ��� ��ǻ�� ��ŷ���� ��ŷ�� �� �ִ� ��� ��ǻ�͸� üũ�ϱ� ����.
queue<int> Q_result; // ���������� ������� �������.

int BFS(int start);

int main() {
	scanf("%d %d", &N, &M);
	for (int a, b, i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		Vec[b].push_back(a); // b�� ��ǻ�͸� ��ŷ�ϸ� a�� ��ǻ�ʹ� ������ ��ŷ..
	}

	for (int i = 1; i <= N; i++) { // 1 ~ N������ ��ǻ�͸� �ϳ��� ���캸�� ������ ��ǻ�͸� ��ŷ���� �� ��� ��ǻ�Ͱ� ��ŷ�Ǵ� �� �������� BFS�� ���.
		int K = BFS(i); 
		if (result == K) Q_result.push(i); // K���� result���� ������ ���� ũ���� ��ǻ�͸� ��ŷ.
		else if (result < K) { // �� ũ�ٸ� �� ���� ��ǻ�͸� ��ŷ�ϹǷ� ���ݱ��� �־��� ������� ��� pop���ְ� result�� �ٲ��ְ� ����� Q�� �ִ´�.
			while (!Q_result.empty()) Q_result.pop();
			Q_result.push(i);
			result = K;
		}
		memset(check, false, sizeof(check));
	}

	while (!Q_result.empty()) {
		int p = Q_result.front();
		Q_result.pop();
		printf("%d ", p);
	}
	printf("\n");

	return 0;
}

int BFS(int start) {
	check[start] = true;
	Q.push(start);
	int cnt = 0; // ��ŷ�� �� �ִ� ������ �����ش�.

	while (!Q.empty()) {
		int p = Q.front();
		Q.pop();

		int sz = Vec[p].size();
		for (int s = 0; s < sz; s++) {
			int first = Vec[p][s];

			if (!check[first]) {
				check[first] = true;
				Q.push(first);
				cnt++;
			}
		}
	}
	return cnt;
}