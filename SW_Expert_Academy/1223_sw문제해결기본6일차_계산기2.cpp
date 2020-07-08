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
	//입력 계산식의 길이가 주어지지 않았으므로 vector에 넣어 길이를 찾는다.
	for (int t = 1; t <= 10; t++) {
		scanf("%d", &N);
		result = 0;
		for (int i = 0; i <=N; i++) {
			scanf("%c", &str);
			Vec.push_back(str);
		}
		int sz = Vec.size();
		// stack을 사용해서 0~9 사이의 숫자이면 stack에 넣고 '+'면 continue, '*'이면 stack top을 꺼내어 '*'다음 숫자와 곱해서 stack에 넣어준다.
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
		// stack에 있는 모든 수를 더해 값을 가져온다.
		while (!S.empty()) {
			result += S.top();
			S.pop();
		}
		//출력 && 초기화
		printf("#%d %d\n", t, result);
		Vec.clear();
	}

	return 0;
}