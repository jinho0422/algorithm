#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int result;

vector<int> bundle;
vector<int> single;

int main() {
	//�Է°� 6�� �������� bundle, 1�� �������� single Vector�� �־��ش�..
	scanf("%d %d", &N, &M);
	for (int a, b, s = 0; s < M; s++) {
		scanf("%d %d", &a, &b);
		bundle.push_back(a);
		single.push_back(b);
	}
	//������ sort���ش�(��������)
	sort(bundle.begin(), bundle.end());
	sort(single.begin(), single.end());

	// ���� ���� ���� ����(6��)�� �������� ����(1��) �� 6�躸�� ������ N�� 6���� ���� ��� �������� ���� ���� ������ �� ���������� ũ�ų� ������ �Ǵ��ؼ� ����� �ݿ�
	if (bundle[0] <= single[0] * 6) {
		int share = N / 6;
		int remainder = N % 6;
		if (bundle[0] < remainder * single[0]) {
			result = (share + 1) * bundle[0];
		}
		else {
			result = share * bundle[0] + remainder * single[0];
		}
	}
	else result = N * single[0];
	printf("%d\n", result);
}