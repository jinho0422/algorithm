#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>
#include <vector>

using namespace std;

int K;
int tree[2][1025];
int board[1025];

typedef struct _Node {
	int w, n;
}Node;

vector<int> dep[10];

void divide(Node root, vector<Node> NodeIn); // 2��Ʈ���� ������ �Լ�
void DFS(int root, int depth); // �� depth�� ���� �ֱ� ����..

int main() {
	vector<Node> NodeIn;
	scanf("%d", &K);
	int sz = pow(2, K) - 1; // ��Ʈ ���� ã�� ����..
	Node root = { 0, 0 };
	for (int a, s = 1; s <= sz; s++) {
		scanf("%d", &a);
		NodeIn.push_back(Node({ s, a }));
		if (s == sz / 2 + 1) root = { s, a };
	}

	divide(root, NodeIn);
	DFS(root.n, 0);

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < dep[i].size(); j++) {
			printf("%d ", dep[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void divide(Node root, vector<Node> NodeIn) {
	vector<Node> left, right;
	Node L = { 0, 0 }, R = { 0, 0 };

	for (int i = 0; i < NodeIn.size(); i++) { // ����
		if (root.w > NodeIn[i].w) {
			left.push_back(Node({ NodeIn[i].w, NodeIn[i].n }));
		}
		else if (root.w < NodeIn[i].w) { // ������
			right.push_back(Node({ NodeIn[i].w, NodeIn[i].n }));
		}
	}

	if (left.size() != 0) {
		int sz = left.size();
		L = { left[sz / 2].w, left[sz / 2].n }; //��Ʈ ã��
		tree[0][root.n] = L.n; // ��Ʈ�� ����
		divide(L, left);
	}

	if (right.size() != 0) {
		int sz = right.size();
		R = { right[sz / 2].w, right[sz / 2].n }; // ��Ʈ ã��
		tree[1][root.n] = R.n; // ��Ʈ�� ������
		divide(R, right);
	}
}

void DFS(int root, int depth) {
	dep[depth].push_back(root);
	if (tree[0][root] != 0) DFS(tree[0][root], depth + 1);
	if (tree[1][root] != 0) DFS(tree[1][root], depth + 1);
}
