#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll inf = (ll)1 << 60;

struct edge {
    ll u, v;
    ll cap, flow;
};

vector<vector<edge>> adj;
ll s, t, n;

void addedge(ll u, ll v, ll cap) {
    adj[u].push_back({u,v,cap,0});
}

// Need to set s, t, n beforehand
ll edmondskarp() {
    ll maxflow = 0;
    vector<edge*> par(n, nullptr);
    queue<ll> q;

    q.push(s);
    while(!q.empty()) {
        ll curr = q.front();
        q.pop();

        for(auto& edge : adj[curr]) {
            par[edge.v] = &edge;
            q.push(edge.v);

            if(edge.v == t) {
                ll flow = inf;
                auto paredge = par[edge.v];
                while(paredge != nullptr) {
                    flow = min(flow, paredge->cap - paredge->flow);
                    paredge = par[paredge->u];
                }

                maxflow += flow;

                paredge = par[edge.v];
                while(paredge != nullptr) {
                    paredge->flow += flow;
                    paredge = par[paredge->u];
                }
            }
        }
    }

    return maxflow;
}

int main() {
    n = 3;
    s = 0;
    t = 2;
    adj.resize(n);

    addedge(s,1,5);
    addedge(1,t,4);

    cout << edmondskarp() << endl;
}
