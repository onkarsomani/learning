#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define double long double
#define ull unsigned long long
#define MOD 998244353
#define print(a) for(auto x : a) cerr << x << " "; cerr<<endl;
#define print1(b) for(auto x : b) cerr << x.first << " " << x.second <<endl;
#define print2(a,x,y) for(int i =x ;i<y;i++) cerr<< a[i] << " ";cerr<<endl;
#define F first
#define S second
#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__)
template <typename Arg1>
void __f(const char * name , Arg1&& arg1){cerr << name << " : " << arg1 << endl ; }
template <typename Arg1, typename... Args>
void __f(const char * names , Arg1&& arg1, Args&&... args){
    const char* comma = strchr (names + 1,',');
    cerr.write (names, comma - names) << " : " << arg1 << " | ";__f(comma +1, args... );
}


int32_t main() {
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);
    int ttt=1 ;
    int mod = 998244353;
    cin>>ttt;
    for(int tt = 1 ; tt <= ttt ; tt++ ){
        int n;
        cin >> n;
        vector<pair<int,int>>vp;
        for(int i = 0 ; i < n ; i++){
            int l , r;
            cin >> l >> r;
            vp.push_back({l,r});
        }
        vector<set<int>>adj(n);
        for(int i = 0 ; i < n-1 ; i++){
            int u , v;
            cin >> u >> v;
            u-- , v--;
            adj[u].insert(v);
            adj[v].insert(u);
        }
        queue<int>q;
        for(int i = 0 ; i < n ; i++){
            if(adj[i].size() == 1){
                q.push(i);
                // bug(i);
            }
        }
        if(n == 1){
            cout << vp[0].F << '\n';
            continue;
        }
        int currsum = 0;
        int ans = 0;
        while(!q.empty()){
            int t = q.front();
            q.pop();
            // bug(t);
            // print1(vp);
            // bug(currsum);
            ans = max(ans , vp[t].F);
            if(adj[t].empty())continue;
            ans = max(ans , vp[t].F + currsum);
            int par = *adj[t].begin();
            int vchild = vp[t].F;
            if(vchild > vp[par].F && vchild <= vp[par].S){
                vp[par].F = vchild;
            }
            else if(vchild > vp[par].S){
                currsum += vchild - vp[par].S;
                // vp[par] = {vchild , vchild};
            }
            // bug(t);
            // print1(vp);
            adj[t].erase(adj[t].begin());
            adj[par].erase(t);
            if(adj[par].size() == 1){
                q.push(par);
            }
        }
        cout << ans << '\n';
    }
}


