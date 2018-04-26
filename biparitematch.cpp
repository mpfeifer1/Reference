bool match(int curr, vector<vector<int>>& adj, vector<int>& l, vector<int>& r, vector<int>& vis) {
    if(vis[curr]) return false;
    vis[curr] = true;

    for(auto next : adj[curr]) {
        if(r[next] == -1 || match(r[next], adj, l, r, vis)) {
            l[curr] = next;
            r[next] = curr;
            return true;
        }
    }
    return false;
}

int bipartite(vector<vector<int>>& adj, int n, int m) {
    vector<int> l, r, vis;
    l.resize(n, -1);
    r.resize(m, -1);
    vis.resize(n);

    bool works = true;
    while(works) {
        works = false;
        fill(vis.begin(), vis.end(), 0);
        for(int i = 0; i < n; i++) {
            if(l[i] == -1) {
                works |= match(i, adj, l, r, vis);
            }
        }
    }

    int ret = 0;
    for(int i = 0; i < n; i++) {
        ret += (l[i] != -1);
    }
    return ret;
}
