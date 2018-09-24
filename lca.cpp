int LOG = 21;

// Calculate depth for all nodes
void dfs_lca(vector<vector<int>>& adj, vector<int>& depth, vector<bool>& vis, vector<int>& par, int node, int Depth = 0) {
    depth[node] = Depth;
    vis[node] = true;
    for(int x : adj[node]) {
        if(!vis[x]) {
            par[x] = node;
            dfs_lca(adj, depth, vis, par, x, Depth+1);
        }
    }
}

// Return Nth parent of node x
int par(vector<vector<int>>& memo, int x, int n) {
    for(int k = LOG; k >= 0; --k) {
        if(n & (1 << k)) {
            x = memo[x][k];
            if(x == -1) return x;
        }
    }
    return x;
}

// Builds LCA table
void build(vector<vector<int>>& memo, vector<int>& par) {
    int n = par.size();
    for(int i = 0; i < n; ++i) memo[i][0] = par[i];
    for(int k = 1; k < LOG; ++k) {
        for(int i = 0; i < n; ++i) {
            if(memo[i][k-1] == -1) {
                memo[i][k] = -1;
                continue;
            }
            memo[i][k] = memo[memo[i][k-1]][k-1];
        }
    }
}

