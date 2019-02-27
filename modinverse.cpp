//returns x such that x*a == 1 (mod b)
//x only exists if gcd(a, b) == 1
ll modInverse(ll a, ll b){
    return 1<a ? b - modInverse(b%a,a)*b/a : 1;
}
