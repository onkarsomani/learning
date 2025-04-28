#include <bits/stdc++.h>
using namespace std;
#define int int64_t
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int ttt;
    cin >> ttt;
    while(ttt--){
        int n , m , k , x , y ;
        cin >> n >> m >> k;
        map<int , int> fmin , smin;
        for(int i = 0 ; i < k ; i++){
            cin >> x >> y;
            if(!fmin.count(x)){
                fmin[x] = y;
                smin[x] = m + 1;
            }
            else if(y < fmin[x]){
                smin[x] = fmin[x];
                fmin[x] = y;
            }
            else{
                smin[x] = min(y , smin[x]);
            }
        }
        int prev = n  , mini = m + 1;
        fmin[1] = min(fmin[1] , m + 1);
        smin[1] = min(smin[1] , m + 1);
        int ans = 0;
        map<int,int> bt;
        for(auto it = fmin.rbegin() ; it != fmin.rend() ; it++){
            ans += (prev - it->F)*(mini - 1);
            cout << it->F << " " << it->S << '\n';
            if(it->S <= mini){
                mini = it->S;
                bt[it->F] = 1;
            }
            prev = it->F;
        }
        ans += prev * (mini - 1);
        cout << ans << '\n';
        

        
    }
    return 0;
}
