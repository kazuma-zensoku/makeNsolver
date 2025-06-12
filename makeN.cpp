#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long; using mint=modint998244353;
const int inf = INT_MAX / 2; const ll infl = 1LL << 60;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const vector<int> dx = {1, 0, -1, 0}; const vector<int> dy = {0, 1, 0, -1};
template<typename T> using vc = vector<T>; template<typename T> using vv = vc<vc<T>>;
using vi = vc<int>;  using vvi = vv<int>; using vl = vc<ll>; using vvl = vv<ll>; using vvvl = vv<vl>; using vvvvl = vv<vvl>;
using vs = vc<string>; using vvs = vv<string>; using P = pair<ll, ll>;
#define nrep(i,n) for (int i = 0; i < (n); ++i)
#define nfor(i,s,n) for(ll i=s;i<n;i++)//i=s,s+1...n-1 ノーマルfor
#define vc_cout(v){ll n = v.size();nrep(i,n)cout<<v[i]<<" \n"[i+1==n];}//一次元配列を出力する
#define vv_cout(v){ll n = v.size();nrep(i,n){nrep(j,v[i].size()){cout<<v[i][j]<<' ';}cout<<endl;}}//二次元配列を出力する
template<class T> using pq = priority_queue<T, vc<T>>;//★大きい順に取り出す コスト,頂点 bfs系で使う　小さい順じゃないですABC305E
template<class T> using pq_g = priority_queue<T, vc<T>, greater<T>>;//小さい順に取り出す　ダイクストラ法で使う
#define cout(n) cout<<n<<endl;
using ld = long double;
ll N, K;
ll ans;
vc<string> a;
vc<string> ops;
vc<string> st; 
vc<string> formulas;
ll generated_nodes = 0;
//　計算量はO(n! 4^(n-1) (Cn-1))? Cn: n番目のカタラン数
ld evalRPN(vector<string>& tokens) {
    vector<ld> st;
    for(string s : tokens){
        if(s=="+"){
            ld a = st.back(); st.pop_back();
            ld b = st.back(); st.pop_back();
            st.push_back(a+b);
        }
        else if(s=="-"){
            ld a = st.back(); st.pop_back();
            ld b = st.back(); st.pop_back();
            st.push_back(b-a);
        }
        else if(s=="*"){
            ld a = st.back(); st.pop_back();
            ld b = st.back(); st.pop_back();
            st.push_back(a*b);
        }
        else if(s=="/"){
            ld a = st.back(); st.pop_back();
            ld b = st.back(); st.pop_back();
            if(a==0) return -1;
            st.push_back(b/a);
        }
        else{
            ld x = stold(s);
            st.push_back(x);
        }
    }
    return st.front();
}

ll dfs(vl & idx, ll depth, ll op_sum){
    generated_nodes++;
    if(depth == K && op_sum == K-1){
        ans++;
        if(abs(evalRPN(st)-N) < 1e-9){
            string tmp;
            nrep(i, st.size()){
                tmp += st[i] + " ";
            }
            formulas.push_back(tmp);
        }
        return 0;
    }
    if(op_sum < depth-1){
        nrep(i, 4){
            st.push_back(ops[i]);
            dfs(idx, depth, op_sum+1);
            st.pop_back();
        }
    }
    if(depth < K) {
        st.push_back(a[idx[depth]]);
        dfs(idx, depth+1, op_sum);
        st.pop_back();
    }
    return 0;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> N >> K;
	a.resize(K);
    ops.resize(4);
    ops = {"+", "-", "*", "/"};
	nrep(i, K){
		cin >> a[i];
	}
    vl idx(K, 0);
    nrep(i, K){
        idx[i] = i;
    }

    do{
        dfs(idx, 0, 0);
    }while(next_permutation(idx.begin(), idx.end()));

    if(formulas.size() == 0){
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;

    cout << formulas.size() << endl;
    for(string s : formulas){
        cout << s << endl;
    }     
} 
