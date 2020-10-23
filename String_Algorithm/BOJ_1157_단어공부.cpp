#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

char str[1000002];
map<char, int> M;
map<char, int>::iterator iter;

typedef struct _pos {
	char ss;
	int n;
}pos;
vector<pos> Vec;

int main() {
	scanf("%s", str);
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			M[str[i] - 32]++;
		}
		else M[str[i]]++;
	}
	int cnt = 0;
	for (iter = M.begin(); iter != M.end(); iter++) {
		if (iter->second > cnt) {
			cnt = iter->second;
			Vec.clear();
			Vec.push_back(pos({ iter->first, iter->second }));
		}
		else if (iter->second == cnt) {
			Vec.push_back(pos({ iter->first, iter->second }));
		}
	}
	if (Vec.size() > 1) printf("?\n");
	else printf("%c\n", Vec[0].ss);


	return 0;
}