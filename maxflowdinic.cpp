// You must set the maximum size for your graph
const int MAXN = 3;

int n;
int cap[MAXN][MAXN];
int nedge[MAXN];
int edge[MAXN][MAXN];
int prev[MAXN];

void addedge(int a, int b, int c) {
    edge[a][nedge[a]++] = b;
    cap[a][b] = c;
}

int maxFlowDinic(int s, int t) {
    int q[MAXN];
    int prev[MAXN];
    int flow = 0;
    int qf, qb, bot, u, v;

    while (true) {
        qf = qb = 0;
        memset(prev, -1, sizeof(prev));

        q[qb++] = s;
        prev[s] = -2;

        while (qb > qf && prev[t] == -1) {
            u = q[qf++];
            for (int i = 0; i < nedge[u]; i++)
                if (prev[v = edge[u][i]] == -1 && cap[u][v])
                    prev[q[qb++] = v] = u;
        }

        if (prev[t] == -1) return flow;

        for (int z = 0; z < n; z++)
            if (cap[z][t] && prev[z] != -1) {
                bot = cap[z][t];

                for (v = z, u = prev[v]; u >= 0; v = u, u = prev[v])
                    bot = min(bot , cap[u][v]);

                if (!bot) continue;
                cap[z][t] -= bot;
                cap[t][z] += bot;

                for (v = z, u = prev[v]; u >= 0; v = u, u = prev[v])
                    cap[u][v] -= bot , cap[v][u] += bot;
                flow += bot;
            }
    }
}

int main() {
    int s = 0;
    int t = 2;

    // Add an edge from s to node 1 with weight a
    addedge(s,1,a);
    // Add an edge from node 1 to t with weight b
    addedge(1,t,b);

    // You must set the size of the graph beforehand
    n = 3;

    // Calculate max flow from s to t
    // Dinic's runs in E * V^2
    cout << maxFlowDinic(s,t) << endl;
}


