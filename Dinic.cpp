#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
const int INF = 1e8 + 10;

struct Dinic {
	int s, t, n, m;
	Dinic() {
		s = t = n = m = 0;
	}
	struct edge {
		int from, to, cap, flow;
		edge(int a, int b, int c, int d) :from(a), to(b), cap(c), flow(d) {}
	};
	vector<edge> edges;
	vector<int> G[maxn];
	bool vis[maxn];
	int deep[maxn];
	int cur[maxn];
	void addEdge(int from, int to, int flow) {
		edges.push_back(edge(from, to, flow, 0));
		edges.push_back(edge(to, from, 0, 0));
		G[from].push_back(edges.size() - 2);
		G[to].push_back(edges.size() - 1);
	}

	int BFS() {
		memset(vis, 0, sizeof(vis));
		queue<int> que;
		que.push(s);
		deep[s] = 0;
		vis[s] = 1;
		while (que.size()) {
			int tmp = que.front();
			que.pop();
			for (int i = 0; i < G[tmp].size(); i++) {
				auto& e = edges[G[tmp][i]];
				if (vis[e.to] == 0 && e.cap > e.flow) {
					vis[e.to] = 1;
					deep[e.to] = deep[tmp] + 1;
					que.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int x, int f) {
		if (x == t || f == 0)return f;
		int flow = 0, r;
		for (int& i = cur[x]; i < G[x].size(); i++) {
			auto& e = edges[G[x][i]];
			if (deep[x] + 1 == deep[e.to] && (r = DFS(e.to, min(e.cap - e.flow, f)))) {
				e.flow += r;
				f -= r;
				flow += r;
				edges[G[x][i] ^ 1].flow -= r;
				if (f == 0)
					break;
			}
		}
		return flow;
	}

	int maxFlow(int s, int t) {
		this->s = s;
		this->t = t;
		int flow = 0;
		while (BFS()) {
			memset(cur, 0, sizeof(cur));
			flow += DFS(s, INF);
		}
		return flow;
	}
}G;

int main() {
	ios::sync_with_stdio(false);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	int i;
	int a, b, w;
	for (i = 0; i < m; i++) {
		cin >> a >> b >> w;
		G.addEdge(a, b, w);
	}
	cout << G.maxFlow(s, t) << endl;
	return 0;
}