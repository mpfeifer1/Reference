#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll inf = (ll)1 << 60;

struct edge {
	int b, u, c, f;
	size_t back;
};

void add_edge(vector<vector<edge>>& g, int a, int b, int u, int c) {
	edge r1 = {b,u,c,0,g[b].size()};
	edge r2 = {a,0,-c,0,g[a].size()};
	g[a].push_back(r1);
	g[b].push_back(r2);
}

int n, m, k;

pair<int,int> mincostflow(vector<vector<edge>>& g, int s, int t) {
	int flow = 0,  cost = 0;
	while(flow < k) {
		vector<int> id(n, 0);
		vector<int> d(n, inf);
		vector<int> q(n);
		vector<int> p(n);
		vector<size_t> p_edge(n);
		int qh=0, qt=0;
		q[qt++] = s;
		d[s] = 0;
		while(qh != qt) {
			int v = q[qh++];
			id[v] = 2;
			if(qh == n)  qh = 0;
			for(size_t i=0; i<g[v].size(); ++i) {
				edge& r = g[v][i];
				if(r.f < r.u && d[v] + r.c < d[r.b]) {
					d[r.b] = d[v] + r.c;
					if(id[r.b] == 0) {
						q[qt++] = r.b;
						if(qt == n) qt = 0;
					}
					else if(id[r.b] == 2) {
						if(--qh == -1) qh = n-1;
						q[qh] = r.b;
					}
					id[r.b] = 1;
					p[r.b] = v;
					p_edge[r.b] = i;
				}
			}
		}
		if(d[t] == inf) break;
		int addflow = k - flow;
		for(int v=t; v!=s; v=p[v]) {
			int pv = p[v]; size_t pr = p_edge[v];
			addflow = min(addflow, g[pv][pr].u - g[pv][pr].f);
		}
		for(int v=t; v!=s; v=p[v]) {
			int pv = p[v]; size_t pr = p_edge[v], r = g[pv][pr].back;
			g[pv][pr].f += addflow;
			g[v][r].f -= addflow;
			cost += g[pv][pr].c * addflow;
		}
		flow += addflow;
	}
    return {flow,cost};
}

int main() {
    // Set the global n, m, and k

	vector<vector<edge>> g(n);
	int s, t;

}
