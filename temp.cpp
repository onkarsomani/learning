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
        string s1 , s2;
        cin  >> s1 >> s2;
        n = s1.length();
        vector<int> cnt1 (2, 0) , cnt2 (2,0);
        int j = 0;
        int flg = 0;
        bug(s1, s2);
        int ans = 0;
        for(int i = 0 ; i < n ; i++){
            if(s1[i] == '0')cnt1[0]++;
            else cnt1[1]++;
            if(s2[i] == '0')cnt2[0]++;
            else cnt2[1]++;
            // print(cnt1);
            // print(cnt2);
            if(cnt1[0] == cnt2[0] && cnt1[1] == cnt2[1]){
                bug(i);
                if(j == i)j++;
                else{
                    if( (j - 1 < 0 || s1[j] != s1[j-1]) &&  (i + 1 >= n || s1[i] != s1[i+1]) ){
                        queue<int> q [2];
                        char prev = s2[j];
                        int cnt = 1;
                        for(int k = j + 1 ; k <= i ; k++){
                            if(s2[k] != prev){
                                q[prev - '0'].push(cnt);
                                cnt = 1;
                                prev = s2[k];
                            }
                            else cnt++;
                        }
                        q[prev - '0'].push(cnt);
                        int carr[2];
                        cnt = 1;
                        carr[0] = 0 , carr[1] = 0;
                        prev = s1[j];
                        int tans = 0;
                        for(int k = j + 1 ; k <= i ; k++){
                            if(s1[k] != prev){
                                carr[prev - '0'] += cnt; 
                                cnt = 1;
                                if(q[prev - '0'].empty()){
                                    flg = 1;
                                    break;
                                }
                                else{
                                    if(carr[prev - '0'] == q[prev - '0'].front())q[prev - '0'].pop();
                                    else if(carr[prev - '0'] > q[prev - '0'].front()){
                                        flg = 1;
                                        break;
                                    }
                                }
                                // redefine prev 
                                tans ++;
                                prev = s1[k];
                            }
                            else cnt++;
                        }
                        tans++;
                        ans += tans/2;
                        carr[prev - '0'] += cnt; 
                        if(q[prev - '0'].empty()){
                            flg = 1;
                            break;
                        }
                        else{
                            if(carr[prev - '0'] == q[prev - '0'].front())q[prev - '0'].pop();
                            else if(carr[prev - '0'] > q[prev - '0'].front()){
                                flg = 1;
                                break;
                            }
                        }
                        if(flg)break;
                        else j = i + 1;
                    }
                    else{
                        flg =1;
                        break;
                    }
                }
            }
        }
        if(j != n)flg = 1;
        if(flg)cout << -1 << '\n';
        else cout << ans << '\n';
        
    }
}


