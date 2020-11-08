#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct _pos1 {
    int n, playNum;
}pos1;

typedef struct _pos {
    int sum;
    vector<pos1> Vec;
}pos;

bool cmp(pos1& p, pos1& q) {
    if (p.playNum == q.playNum) return p.n < q.n;
    return p.playNum > q.playNum;
}

typedef struct _pos2 {
    int a, b, c;
}pos2;
bool cmp1(pos2& p, pos2& q) {
    return p.a > q.a;
}


map<string, pos> Map;
map<string, pos>::iterator iter;
vector<pos2> result;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    for (int s = 0; s < genres.size(); s++) {
        Map[genres[s]].sum += plays[s];
        Map[genres[s]].Vec.push_back(pos1({ s, plays[s] }));
    }


    for (iter = Map.begin(); iter != Map.end(); iter++) {
        sort(iter->second.Vec.begin(), iter->second.Vec.end(), cmp);
    }

    for (iter = Map.begin(); iter != Map.end(); iter++) {
        // printf("%d\n", iter->second.Vec.size());
        if (iter->second.Vec.size() >= 2) result.push_back(pos2({ iter->second.sum, iter->second.Vec[0].n, iter->second.Vec[1].n }));
        else result.push_back(pos2({ iter->second.sum, iter->second.Vec[0].n, -1 }));
    }

    sort(result.begin(), result.end(), cmp1);

    for (int s = 0; s < result.size(); s++) {
        //printf("%d\n", result[s].a);
        answer.push_back(result[s].b);
        if (result[s].c != -1) answer.push_back(result[s].c);
    }
    return answer;
}