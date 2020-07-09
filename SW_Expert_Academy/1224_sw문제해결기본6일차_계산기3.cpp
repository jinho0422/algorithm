#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

int N;
char str;
int result;

vector<char> Vec;
stack<int> S;

int main() {
	//freopen("test.txt", "r", stdin);
	//�Է�, ����� �ʱ�ȭ..
	for (int t = 1; t <= 10; t++) {
		result = 0;
		scanf("%d", &N);
		for (int s = 0; s <= N; s++) {
			scanf("%c", &str);
			Vec.push_back(str);
		}
		int sz = Vec.size();
		// 0 ���� ������ ���̱��� ���鼭
		for (int s = 0; s < sz; s++) {
			//'+' continue
			if (Vec[s] == '+') continue;
			//'*' �� ������ ���� ������ '('�̸� ���ϱ⸦ ���ϴ� -2�� (�� ���ϴ� -1�� stack�� �־��ش�
			else if (Vec[s] == '*') {
				int first = S.top();
				s++;
				if (Vec[s] == '(') {
					S.push(-2);
					S.push(-1);
				}
				// �����̸� stack top�� �ִ� ���ڿ� ���ؼ� �־��ش�.
				else {
					S.pop();
					S.push(first * (Vec[s] - '0'));
				}
			}
			else if (Vec[s] == '(') S.push(-1);
			else if (Vec[s] >= '0' && Vec[s] <= '9') S.push(Vec[s] - '0');
			
			// ')'�� ������ ���� '('�� ����Ű�� -1�� ���ö����� cnt�� stack�� ���� �����ش�..
			else if (Vec[s] == ')') {
				int cnt = 0;
				while (1) {
					int p = S.top();
					//-1�� ������ �� �� ���� �ִ� stack�� ���ڰ� -2�̸� �� ������ �ִ� ���� ���ؼ� �־��ش�.
					if (p == -1) {
						S.pop();
						if (S.size() != 0) {
							p = S.top();
							if (p == -2) {
								S.pop();
								p = S.top();
								cnt *= p;
								S.pop();
							}
						}
						S.push(cnt);
						break;
					}
					// ���� -2�� ������ �����ְ�
					else if (p == -2) {
						S.pop();
						int p = S.top();
						S.pop();
						cnt *= p;
					}
					else {
						S.pop();
						cnt += p;
					}
				}
			}
		}
		while (!S.empty()) {
			result += S.top();
			S.pop();
		}
		printf("#%d %d\n", t, result);
		Vec.clear();
	}

	return 0;
}