#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int N, C;

// map�� ���� value�� �󵵼��� ���� ������ �����ϱ����� struct
typedef struct _pos {
	int cnt, f;
}pos;
// vector�� ���� ���� �󵵼� ���� ������ �����ϱ� ���� strcut
typedef struct _pos1 {
	int a, b, c;
}pos1;
// �󵵸� ���������������� ���� �󵵰� ���ٸ� ���� ���� ������� ����..
bool cmp (const pos1& p, const pos1& q) { 
		if (p.b == q.b) return p.c < q.c;
		else return p.b > q.b;
};

map<int, pos> m;
map<int, pos>::iterator iter; 
vector<pos1> Vec;

int main() {
	//�Է�
	scanf("%d %d", &N, &C);
	int order = 0; // ���� ������ �����ϱ�����
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		m[a].cnt++;
		if (m[a].cnt == 1) m[a].f = order++; // ���� ó�� ���Դٸ� ���� ������ ����..
	}
	// map m�� ���鼭 Vector������
	for (iter = m.begin(); iter != m.end(); iter++) {
		Vec.push_back(pos1({ iter->first, iter->second.cnt, iter->second.f }));
	}
	// �󵵿� ���� ����..
	sort(Vec.begin(), Vec.end(), cmp);
	// ���
	for (int i = 0; i < Vec.size(); i++) {
		for (int j = 0; j < Vec[i].b; j++) {
			printf("%d ", Vec[i].a);
		}
	}
	printf("\n");
	return 0;
}