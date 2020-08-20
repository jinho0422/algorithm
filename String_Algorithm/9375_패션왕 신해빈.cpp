#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int T;
char name[23];
char type[23];
int result;

//Ÿ���� ������ ������ ����ϱ� ���� map
map<string, int> types;

int main() {
	scanf("%d", &T);
	for (int N, t = 0; t < T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			// �м��� �̸��� Ÿ���� ���� �޾Ƽ� map�� Ÿ���� ������ �����Ѵ�.
			scanf("%s %s", name, type);
			types[type] += 1;
		}
		result = 1;
		// map�� ó������ ������ ������ ���鼭 ���Դ°ű��� +1�� �ϰ� �����ش�.
		for (auto s = types.begin(); s != types.end(); s++) {
			int cnt = s->second;
			cnt++;
			result = result * cnt;
		}
		// �ƹ��͵� ������ ���� ���� ����� ���
		printf("%d\n", result - 1);
		//map�� �ʱ�ȭ �����ش�(���� �׽�Ʈ�� ����)
		types.clear();
	}
	return 0;
}