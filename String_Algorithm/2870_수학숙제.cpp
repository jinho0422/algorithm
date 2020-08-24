#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int N;
char str[102];
string tmpStr;

// stirng�� �� vector�� ������ ũ�⸦ ������������, ũ�Ⱑ ������ ���ڸ� ���Ͽ� ������������
bool cmp(const string& a,const string& b) {
	if (a.size() == b.size()) {
		int sz = a.size();
		for (int i = 0; i < sz; i++) {
			if (a[i] != b[i]) return a[i] < b[i];
		}
	}
	return a.size() < b.size();
}

vector<string> Vec;

// �տ� string 0�� �������ִ� �Լ�..
void zeroClear() {
	while (1) {
		if (tmpStr.length() == 1 && tmpStr == "0") break;
		if (tmpStr[0] == '0') tmpStr.erase(0, 1);
		else break;
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", str);
		int cnt = 0;
		while (str[cnt] != '\0') cnt++;

		for (int j = 0; j < cnt; j++) {
			// str[j] == ������ ��
			if (str[j] >= '0' && str[j] <= '9') tmpStr += str[j];
			// str[j]�� ���ڰ� �ƴҶ�..
			else {
				if (tmpStr.length() != 0) {
					zeroClear(); // ���ʿ� 0�� �ִ��� �Ǵ��ϴ� �Լ�..
					Vec.push_back(tmpStr); // vector�� �߰�
					tmpStr.clear(); // �ʱ�ȭ
				}
			}
		}
		// �ѹ����� ������ ���� tmpStr�� ũ�Ⱑ 0�� �ƴ϶�� ���ڰ� ���������Ƿ�
		if (tmpStr.length() != 0) {
			zeroClear();// ���ʿ� 0�� �ִ��� �Ǵ��ϰ�
			Vec.push_back(tmpStr); // vector�� �߰�
			tmpStr.clear(); // �ʱ�ȭ
		}
	}

	sort(Vec.begin(), Vec.end(), cmp); // �񳻸�����(��������)���� ����
	// ���
	for (int i = 0; i < Vec.size(); i++) {
		for (int j = 0; j < Vec[i].size(); j++) {
			printf("%c", Vec[i][j]);
		}
		printf("\n");
	}
	return 0;
}