#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int N;
char str;
int result;
vector<char> Vec;
stack<int> S;

int main() {
	//freopen("test.txt", "r", stdin);
	//�Է� ������ ���̰� �־����� �ʾ����Ƿ� vector�� �־� ���̸� ã�´�.
	for (int t = 1; t <= 10; t++) {
		scanf("%d", &N);
		result = 0;
		for (int i = 0; i <=N; i++) {
			scanf("%c", &str);
			Vec.push_back(str);
		}
		int sz = Vec.size();
		// stack�� ����ؼ� 0~9 ������ �����̸� stack�� �ְ� '+'�� continue, '*'�̸� stack top�� ������ '*'���� ���ڿ� ���ؼ� stack�� �־��ش�.
		for (int i = 0; i < sz; i++) {
			if (Vec[i] >= '0' && Vec[i] <= '9') S.push(Vec[i] - '0');
			else if (Vec[i] == '+') continue;
			else if (Vec[i] == '*') {
				int before = S.top();
				S.pop();
				i++;
				S.push(before * (Vec[i] - '0'));
			}
		}
		// stack�� �ִ� ��� ���� ���� ���� �����´�.
		while (!S.empty()) {
			result += S.top();
			S.pop();
		}
		//��� && �ʱ�ȭ
		printf("#%d %d\n", t, result);
		Vec.clear();
	}

	return 0;
}