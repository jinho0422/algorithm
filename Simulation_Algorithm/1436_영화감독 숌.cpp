#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N;
vector<int> Vec;

int main() {
	//�Է�
	scanf("%d", &N);
	// 666���� int �ִ�ġ���� �����鼭 ���� ���� ������ Vec�� ���� 10000(N�� �ִ밡 10000�̹Ƿ�)�̸� break;
	for (int s = 666; s <= 2147000000; s++) {
		if (Vec.size() == 10001) break;
		int checkCnt = 0; // ���ӵ� 6�� ���ڸ� ��������
		int share = s; // ��
		bool flag = false; // ���ӵ� 6�� 3���̻����� �Ǵ��ϱ�����
		while (1) {
			int remainder = share % 10; // ������
			share /= 10; 
			
			if (remainder == 6) { // �������� 6�̸� checkCnt++
				checkCnt++;
				if (checkCnt == 3) flag = true; // ���ӵ� 6�� 3���� �������Ƿ� ��������� �����ǹǷ�flag ==ture;
				
			}
			if (share == 0) break;

			if (remainder != 6) {
				checkCnt = 0;
			}
			
		}
		// ������� �����Ǹ� vector�� �־��ش�..
		if (flag) Vec.push_back(s);
	}
	//���
	printf("%d\n", Vec[N - 1]);
	return 0;
}
