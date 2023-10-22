#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 501;
const int INF = 987654321;

int n, m, s, d, u, v, p, dist[MAX];
vector<pair<int, int>> arr[MAX];
vector<int> prevArr[MAX];

bool checked[MAX][MAX];

void dijkstra(int start) {
    priority_queue<pair<int, int>> pq;

    pq.push({ 0, start });
    dist[start] = 0;

    while (!pq.empty()) {
        int curDist = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] > curDist)
            continue;

        for (int i = 0; i < arr[cur].size(); i++) {
            if (!checked[cur][arr[cur][i].second])
                continue;

            int nextDist = curDist + arr[cur][i].first;
            int next = arr[cur][i].second;

            if (dist[next] > nextDist) {
                prevArr[next].clear();
                prevArr[next].push_back(cur);
                dist[next] = nextDist;
                pq.push({ -nextDist, next });
            }
            else if (dist[next] == nextDist)
                prevArr[next].push_back(cur);
        }
    }
}

void removeEdge(int ed) {
    for (int i = 0; i < prevArr[ed].size(); i++) {
        int cur = prevArr[ed][i];

        if (!checked[cur][ed])
            continue;

        removeEdge(cur);

        checked[cur][ed] = false;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        memset(checked, true, sizeof(checked));

        for (int i = 0; i < n; i++) {
            arr[i].clear();
            prevArr[i].clear();
            dist[i] = INF;
        }

        cin >> s >> d;
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> p;

            arr[u].push_back({ p, v });
        }

        dijkstra(s);
        removeEdge(d);

        for (int i = 0; i < n; i++)
            dist[i] = INF;

        dijkstra(s);

        if (dist[d] == INF)
            cout << -1 << '\n';
        else
            cout << dist[d] << '\n';
    }

    return 0;
}