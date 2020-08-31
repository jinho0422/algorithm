#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;

int N;
int result;

priority_queue<int, vector<int>, greater<int>> upW, upM, downW, downM;

int main() {
	//�Է�
	scanf("%d", &N);
	for (int m, i = 0; i < N; i++) {
		scanf("%d", &m);
		if (m > 0) upW.push(m); // Űū ���ڸ� �����ϴ� ����
		if (m < 0) downW.push(abs(m)); // Ű ���� ���ڸ� �����ϴ� ����

	}
	for (int w, i = 0; i < N; i++) {
		scanf("%d", &w);
		if (w > 0) upM.push(w); // Űū ���ڸ� �����ϴ� ����
		if (w < 0) downM.push(abs(w)); // Ű ���� ���ڸ� �����ϴ� ����
	}
	// Ű���� ���ڿ� Űū ���ڸ� �����ϴ� ����� ��Ī..
	while (1) {
		if (upW.size() == 0 || downM.size() == 0) break;
		int Mkey = upW.top();
		int Wkey = downM.top();
		downM.pop();	
		if (Mkey < Wkey) { // ���� ���ڰ� Ű���۰� ���ڰ� Ű�� ũ��
			result++; // ����� ����
			upW.pop();
		}
	}
	// Űū ���ڿ� Ű ���� ���ڸ� �����ϴ� ����� ��Ī..
	while (1) {
		if (upM.size() == 0 || downW.size() == 0) break;
		int Mkey = downW.top();
		int Wkey = upM.top();
		downW.pop();
		if (Mkey > Wkey) {
			result++;
			upM.pop();
		}
	}
	printf("%d\n", result);
	return 0;
}
