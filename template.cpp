#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define float long double
 
#define print(a) for(auto x : a) cerr << x << " "; cerr<<endl;
#define print1(b) for(auto x : b) cerr << x.first << " " << x.second <<endl;
#define print2(a,x,y) for(int i =x ;i<y;i++) cerr<< a[i] << " ";cerr<<endl;
 
#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__)
 
 
template <typename Arg1>
void __f(const char * name , Arg1&& arg1){cerr << name << " : " << arg1 << endl ; }
template <typename Arg1, typename... Args>
void __f(const char * names , Arg1&& arg1, Args&&... args){
    const char* comma = strchr (names + 1,',');
    cerr.write (names, comma - names) << " : " << arg1 << " | ";__f(comma +1, args... );
}

int fact[3000001];
int mod = 998244353;


mt19937_64 rng((int) chrono::steady_clock::now().time_since_epoch().count());




// most possible mistakes 

/*

unending loop 

1ll not used 

memset other than 0 -1 

*/

//gcd
int gcd(int a, int b) {
   if (b == 0)
   return a;
   return gcd(b, a % b);
}

// Trie
class TrieNode {
public:
    TrieNode* child[26];
    
    TrieNode() {
        for(int i = 0; i < 26; i++)
            child[i] = nullptr;   
    }
};

//ncr
int power(int num , int pow, int mod){
    if(pow==0){
        return 1;
    }
    int ans =1;
    if(pow%2){
        ans*=num;
        ans%=mod;
    }
    int t = power(num,pow/2,mod);
    ans*= t;
    ans%=mod;
    ans*=t;
    ans%=mod;
    return ans;
}


int C(int n, int r,int mod)
{       
    int ans = 1;

    ans*= fact[n];
    ans%= mod;
    ans*= power(fact[r],mod-2,mod);
    ans%=mod;
    ans*= power(fact[n-r],mod-2,mod);
    ans%=mod;

    return ans;
}

// dp version
/*
for(int n = 0 ; n <= 5000 ; n++){
    for(int r = 0 ; r <= 5000 ; r++){
        if(n== 0 && r== 0)dp[n][r]= 1;
        else if(n== 0)dp[n][r]= 0;
        else{
            int ans = 0;
            ans += dp[n-1][r-1];
            ans %= mod;
            ans += dp[n-1][r];
            ans %= mod;
            dp[n][r]= ans;
        }
    }
}
*/




int mod = 998244353;


//dfs
vector<int>adj[400000];
vector<int>vis;
void dfs(int ind , vector <int> & vis , vector<vector<int>> & adj){
    vis[ind]=1;
    for(auto child : adj[ind]){
        if(vis[child])continue;
        dfs(child , vis , adj);
    }
}





// ------------------------------------- seg tree -------------------------







class segtree{
    public :
    vector<int> t;
    vector<int> a;
    int n;

    unsigned long long combine(unsigned long long c, unsigned long long d) {
        return std::__gcd(c, d);
    }

    void update (int ind, int updind , int tl , int tr , int updval ){
        int mid = (tl + tr)/2;
        if(tl == tr){
            t[ind] = updval;
            a[tl] = updval;
            return;
        }
        if(updind <= mid){
            update(2* ind + 1, updind , tl , mid , updval);
        }
        else{
            update(2* ind + 2, updind , mid + 1 , tr , updval);
        }
        t[ind] = combine(t[2*ind + 1] , t[2*ind + 2]);
    }

    int query(int ind,  int l , int r , int tl , int tr){
        int mid = (tl+ tr)/2;
        int ans =0;
        if(l<= tl && r>= tr){
            return t[ind];
        }
        else if(tl > r  || tr < l){
            return 0;
        }
        else{
            ans = combine (query( (2*ind) + 1, l, r , tl , mid) , query( (2*ind) + 2, l, r , mid + 1, tr));
            return ans;
        }
    }

    int build(int ind , int tl , int tr){
        if(tl== tr){
            t[ind] = a[tl];
        }
        else{
            int mid = (tl + tr)/2;
            t[ind] = combine (build( (ind * 2) + 1 , tl , mid ) , build( (ind* 2 ) + 2 , mid + 1 , tr)); 
        } 
        return t[ind];
    }

    int find(int ind , int tl , int tr , int val){
        if(tl == tr)return tl;
        int mid = (tl+tr)/2;
        if(t[2*ind + 1] >= val){
            return find(2*ind + 1, tl , mid , val);
        }
        else{
            return  find(2*ind + 2 , mid + 1 , tr , val);
        }
    }

    int query(int l , int r){
        return query(0 , l , r , 0 , n - 1 );
    }

    void upd(int ind , int val){
        update(0 , ind , 0 , n-1 , val);
    }

    int find(int val){
        return find(0 , 0 , n-1 , val);
    }
    
    segtree(vector<int> v){
        a = v;
        t.resize(a.size()*4);
        n = a.size();
        build(0 , 0 , n-1);
    }
};








// 3d dp

vector<vector<vector<int>>> dp(1 , vector<vector<int>>(1 , vector<int>(1 , -1) ) );














int32_t main() {
 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif


    fact[0]=1;
    for(int i=1;i<=3e6;i++){
        fact[i]= i * fact[i-1];
        fact[i]%=mod;
    }
    
    int t=1;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=0;i<=n;i++){
            adj[i].clear();
        }
        vector<vector<int>> adj(n+1);
        vector<int> vis(n+1 , 0);
        int x , y;
        for(int i=0;i<n-1;i++){
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        vis.clear();
        vis.resize(n+1,0);



    }
 
    
}










/*


lca

int dp [200000+1 ][31];
int depth[200001];
vector<int> adj[200001];
vector<int> vis; 

void dfs(int node , int val){
    vis[node]=1;
    depth[node] = val;
    // bug(node);
    for(auto child : adj[node]){
        // bug(node,child);
        if(vis[child])continue;
        dfs(child, val + 1);
    }
}


int kthancestor ( int node ,int k){
    int ans=node;
    for(int i=0;i<31;i++){
        if((k>>i)&1){
            if(ans == -1)break;
            ans = dp[ans][i];
        }
    }
    return ans ;
}


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t=1;
    // cin>>t;
    for(int tt=0;tt<t;tt++){
        int n ,k;
        cin>> n>> k;
        
        memset(dp,-1,sizeof(dp));
        for(int i=2;i<=n;i++){
            int x;
            cin>>x;
            adj[x].push_back(i);
            dp[i][0]= x;
        }
        for(int i=1;i<=n;i++){
            for(int j=1; j<31;j++){
                if(dp[i][j-1]!= -1)
                dp[i][j] = dp[dp[i][j-1]][j-1];
            }
        }
        vis.clear();
        vis.resize(n+1,0);
        dfs(1,0);
        while(k--){
            int x,y;
            cin>> x>> y;
            if(depth[x]<depth[y]){
                swap(x,y);
            }
            int depthdiff = depth[x] - depth[y];
            // bug(depthdiff);
            int node = kthancestor(x, depthdiff);
            // bug(node, y);
            if(node == y){
                cout<< node << "\n";
                continue;
            }
            int r = depth[node] + 1 , l=0; 
            int ans =1;
            for(int i=30;i>=0;i--){
                // bug(dp[node][i], dp[y][i]);
                if(dp[node][i]== dp[y][i]){
                    ans= dp[node][i];
                }
                else{
                    node = dp[node][i];
                    y = dp[y][i];
                }
            }
            cout<<  ans << '\n';
        }
    }   
}


*/



/*

#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define float long double
#define MOD 998244353
#define print(a) for(auto x : a) cerr << x << " "; cerr<<endl;
#define print1(b) for(auto x : b) cerr << x.first << " " << x.second <<endl;
#define print2(a,x,y) for(int i =x ;i<y;i++) cerr<< a[i] << " ";cerr<<endl;
#define pb push_back
#define F first
#define S second
#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__)
template <typename Arg1>
void __f(const char * name , Arg1&& arg1){cerr << name << " : " << arg1 << endl ; }
template <typename Arg1, typename... Args>
void __f(const char * names , Arg1&& arg1, Args&&... args)
{
    const char* comma = strchr (names + 1,',');
    cerr.write (names, comma - names) << " : " << arg1 << " | ";__f(comma +1, args... );
}

 
 
 
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t=1;
    // cin>>t;
    for(int tt=0;tt<t;tt++){
        
    }   
}

*/


// tree input


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
 
    int ttt=1 ;
    cin>>ttt;
    for(int tt = 0 ; tt < ttt ; tt++ ){
        int n;
        cin >> n;
        vector<vector<int>>adj(n);
        for(int i = 0 ; i < n-1 ; i++){
            int x , y;
            cin >> x >> y;
            x-- , y--;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        
    }
}



/*



// read question twice 
// int overflow
// maybe there is a way other than this to solve the problem 


*/


// z function


vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}


/* sieve */

vector<int> pp;

void SieveOfEratosthenes(int n){
    vector<bool> prime(n+1 , 1);
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    for (int p = 2; p <= n; p++){
        if (prime[p]){
            pp.push_back(p);
        }
    }    
}



// matmul matrix exponentiation


vector<vector<int>> matmul(vector<vector<int>> & m1 , vector<vector<int>> & m2 , int mod){
    int n = m1.size();
    int m = m1[0].size();
    int l = m2[0].size();
    vector<vector<int>> ans(n , vector<int> (l , 0));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < l ; j++){
            int64_t t = 0;
            for(int k = 0 ; k < m ; k++){
                t += (1LL *m1[i][k]*m2[k][j])%mod;
                t %= mod;
            }
            ans[i][j] = t; 
        }
    }
    return ans;
}
    
    
vector<vector<int>> matexp(vector<vector<int>> & mat , int pow , int mod){
    if(pow == 1)return mat;
    auto t = matexp(mat , pow/2 ,mod);
    auto t1 = matmul(t , t , mod);
    if(pow%2){
        t1 = matmul(t1 , mat , mod);
    }
    return t1;
}


// DSU

struct DSU {
	vector<int> e; void init(int N) { e = vector<int>(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};



// dsu template


struct ufds{
    vector <int> root, sz;
    int n;
 
    void init(int nn){
        n = nn;
        root.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) root[i] = i;
    }
 
    int find(int x){
        if (root[x] == x) return x;
        return root[x] = find(root[x]);
    }
 
    bool unite(int x, int y){
        x = find(x); y = find(y);
        if (x == y) return false;
 
        if (sz[y] > sz[x]) swap(x, y);
        sz[x] += sz[y];
        root[y] = x;
        return true;
    }
};