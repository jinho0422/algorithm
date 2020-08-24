#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
bool check[100002];
int result, cnt;


queue<int> Q;

void BFS(int start);

int main() {
	//�Է�
	scanf("%d %d", &N, &K);
	BFS(N);
	//���
	printf("%d\n%d\n", result, cnt); // result : �ð� �����, cnt ; �� �ð��� ����������ϴ���
	return 0;
}

void BFS(int start) {
	bool bkFlag = false; // ���� �� �ð��� ������ ã�Ҵٸ� bkFlag = true;
	Q.push(start);
	while (!Q.empty()) {
		int sz = Q.size(); // �ð������� ���� ����.. Q�� size��ŭ ������..
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			if (p == K) { // ���� ������ �����ٸ�
				cnt++; // ī��Ʈ�� ���� 
				bkFlag = true; // �������� bkFlag = true�� �Ѵ�..
				continue;
			}
			check[p] = true;
			if (p + 1 <= 100000) { // ������ ��ĭ ����
				if (!check[p + 1]) {
					Q.push(p + 1);
				}
			}
			if (p - 1 >= 0) { //�ڷ� ��ĭ ����
				if (!check[p - 1]) {
					Q.push(p - 1);
				}
			}
			if (p * 2 <= 100000) { // �����̵�..
				if (!check[p * 2]) {
					Q.push(p * 2);
				}
			}
		}
		if (bkFlag) break;
		result++;	
	}
}