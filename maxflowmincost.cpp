#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll inf = (ll)1 << 60;

struct edge {
	ll b, cap, cost, flow;
	size_t back;
};

void addedge(vector<vector<edge>>& g, ll a, ll b, ll cap, ll cost) {
	edge r1 = {b,cap,cost,0,g[b].size()};
	edge r2 = {a,0,-cost,0,g[a].size()};
	g[a].push_back(r1);
	g[b].push_back(r2);
}

ll n, m;
ll k = inf; // The maximum amount of flow allowed

pair<ll,ll> mincostflow(vector<vector<edge>>& g, ll s, ll t) {
	ll flow = 0, cost = 0;
	while(flow < k) {
		vector<ll> id(n, 0);
		vector<ll> d(n, inf);
		vector<ll> q(n);
		vector<ll> p(n);
		vector<size_t> p_edge(n);
		ll qh=0, qt=0;
		q[qt++] = s;
		d[s] = 0;
		while(qh != qt) {
			ll v = q[qh++];
			id[v] = 2;
			if(qh == n) qh = 0;
			for(size_t i=0; i<g[v].size(); ++i) {
				edge& r = g[v][i];
				if(r.f < r.cap && d[v] + r.cost < d[r.b]) {
					d[r.b] = d[v] + r.cost;
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
		ll addflow = k - flow;
		for(ll v=t; v!=s; v=p[v]) {
			ll pv = p[v]; size_t pr = p_edge[v];
			addflow = min(addflow, g[pv][pr].cap - g[pv][pr].f);
		}
		for(ll v=t; v!=s; v=p[v]) {
			ll pv = p[v]; size_t pr = p_edge[v], r = g[pv][pr].back;
			g[pv][pr].f += addflow;
			g[v][r].f -= addflow;
			cost += g[pv][pr].cost * addflow;
		}
		flow += addflow;
	}
    return {flow,cost};
}

int main() {
    // Set the global n, m, and k

	vector<vector<edge>> g(n);
	ll s, t;

}
