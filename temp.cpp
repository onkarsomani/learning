#include <bits/stdc++.h>
using namespace std;

int main(){
    int tt = 1;
    cin >> tt;
    while(tt--){
        int n , m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(m);
        for(auto & i : a)cin >> i;
        for(auto & i : b)cin >> i;
        vector<int> v1 , v2;
        for(int l = 0 , r = n - 1 ; l < r ; l++ , r-- ){
            v1.push_back(a[r] - a[l]);
        }
        for(int l = 0 , r = m - 1 ; l < r ; l++ , r-- ){
            v2.push_back(b[r] - b[l]);
        }
        sort(v1.begin() , v1.end());
        sort(v2.begin() , v2.end());
        reverse(v1.begin() , v1.end());
        reverse(v2.begin() , v2.end());
        int i = 0 , j = 0;
        int rem1 = 0 , rem2 = 0;
        for(;;){

        }
        
    }
}