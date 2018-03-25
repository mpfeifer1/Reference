ll fastpow(ll base, ll exp, ll mod) {
    ll res = 1;
    while(exp > 0) {
        if((exp & 1) == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }

    return res % mod;
}

const ll MAXN = 1000000;
ll factarr[MAXN+1];
ll ifactarr[MAXN+1];

void generate() {
    factarr[0] = 1;
    for(ll i = 1; i <= MAXN; i++) {
        factarr[i] = (factarr[i-1] * i) % mod;
    }
    ifactarr[MAXN] = fastpow(factarr[MAXN], mod-2, mod);
    for(int i = MAXN-1; i >= 0; i--) {
        ifactarr[i] = (ifactarr[i+1] * (i+1)) % mod;
    }
}

ll fact(ll n) {
    return factarr[n];
}

ll ifact(ll n) {
    return ifactarr[n];
}

ll ncr(ll n, ll r) {
    if(n < 0 || r < 0 || r > n) return 0;
    ll ans = (fact(n) * ifact(r)) % mod;
    return (ans * ifact(n-r)) % mod;
}

ll npr(ll n, ll r) {
    if(n < 0 || r < 0 || r > n) return 0;
    return (fact(n) * ifact(n-r)) % mod;
}
