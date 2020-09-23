#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;

// ���������� ���� ����
bool cmp(const int p, const int q) {
	if (p > q) return true;
	return false;
}
vector<int> crain; // ũ�����̵���ִ� vector
vector<int> box; // box�� ���԰� ����ִ� vector

int main() {
	//�Է�
	scanf("%d", &N);
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		crain.push_back(a);
	}
	scanf("%d", &M);
	for (int a, i = 0; i < M; i++) {
		scanf("%d", &a);
		box.push_back(a);
	}
	// ���� �������� ����
	sort(crain.begin(), crain.end(), cmp);
	sort(box.begin(), box.end(), cmp);
	//���� ũ������ �ű������ �ڽ����԰� ������ -1 ���
	if (crain[0] < box[0]) {
		printf("-1\n");
		return 0;
	}
	int time = 0; // �����
	// ũ���� �� �ڽ��� ���� ���� �ڽ��� ũ�Ⱑ ũ������ ũ�⺸�� �۰ų� ������
	while (1) {
		for (int i = 0; i < crain.size(); i++) {
			for (int j = 0; j < box.size(); j++) {
				if (crain[i] >= box[j]) {
					box.erase(box.begin() + j); // vector�� erase�� ���� ����
					break;
				}
			}
		}
		time++;
		if (box.size() == 0) break; // �ڽ��� ��� �Ű����� break..
	}
	//���
	printf("%d\n", time);
	return 0;
}