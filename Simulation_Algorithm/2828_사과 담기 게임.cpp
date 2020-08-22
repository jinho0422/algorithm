#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

int N, M, J;
int board[21];
int result;

vector<int> Vec;

int main() {
	//�Է�
	scanf("%d %d %d", &N, &M, &J);
	for (int i = 0; i < J; i++) {
		scanf("%d", &board[i]);
	}
	//�ٱ����� ��ġ�� �ִ´�(���ӵ� M)
	for (int i = 1; i <= M; i++) {
		Vec.push_back(i);
	}
	// ����� �������� ���� �ϳ��� ���鼭 �������� �ּҰ��� ã�´�.
	for (int i = 0; i < J; i++) {
		int minCheck = 100; // ������ �ּҰ��� ã������
		bool flag = false; // �ٱ����� ���ʿ� ����� ������ false �����ʿ� ������ true
		for (int j = 0; j < Vec.size(); j++) {
			if (board[i] > Vec[0] && !flag) flag = true;
			// ������ �ּҰ� ����
			if (minCheck > abs(board[i] - Vec[j])) minCheck = abs(board[i] - Vec[j]);
		}
		// ������� �����ְ�
		result += minCheck;
		// ����� �ٱ����� ���ʿ� ������ �ٱ��ϸ� minCheck��ŭ �������� �ٱ��ϸ� �Ű��ְ�
		if (!flag) {
			for (int k = 0; k < Vec.size(); k++) {
				Vec[k] -= minCheck;
			}
		}
		// ���������� �ٱ��ϸ� �Ű��ش�.
		else {
			for (int k = 0; k < Vec.size(); k++) {
				Vec[k] += minCheck;
			}
		}
	}
	//���
	printf("%d\n", result);
	return 0;
}