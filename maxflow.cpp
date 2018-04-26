const int SIZE = 500;

ll bfs(vector<vector<ll>>& og, vector<vector<ll>>& rg, vector<ll>& par, ll s, ll t, ll n) {
    vector<ll> f(SIZE, 0);

    vector<bool> visited(SIZE, false);
    visited[s] = true;

    queue<ll> q;
    q.push(s);
    par[s] = -1;
    f[s] = inf;

    while(!q.empty()) {
        ll u = q.front();
        q.pop();
        for(ll v = 0; v < n; v++) {
            if(visited[v] == false && rg[u][v] > 0) {
                q.push(v);
                par[v] = u;
                visited[v] = true;
                f[v] = min(f[u], rg[u][v]);
            }
        }
    }

    if(visited[t]) {
        return f[t];
    }
    return 0;
}

// Takes in original graph, residual graph, source, sink, #nodes
ll fulkerson(vector<vector<ll>>& og, vector<vector<ll>>& rg, ll s, ll t, ll n) {
    ll max_flow = 0, path_flow = 0;

    vector<ll> par(SIZE);

    while(path_flow = bfs(og, rg, par, s, t, n)) {
        for(ll v = t; v != s; v = par[v]) {
            ll u = par[v];
            rg[u][v] -= path_flow;
            rg[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    ll n, m, s, t;
    cin >> n >> m >> s >> t;

    // Set up original graph and residual graph
    vector<vector<ll>> og, rg;
    og.resize(SIZE, vector<ll>(SIZE, 0));
    rg.resize(SIZE, vector<ll>(SIZE, 0));

    for(ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;

        og[u][v] = w;
        rg[u][v] = w;
    }

    fulkerson(og, rg, s, t, n);
}
