#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long LL;

map<LL,LL> uf;

LL find(LL a){
        if(uf[a] != a) uf[a] = find(uf[a]);
        return uf[a];
}

void join(LL a, LL b){
        uf[find(a)] = find(b);
}

int main(){
        cin.sync_with_stdio(0); cin.tie(0); cout.tie(0);
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
                LL x, y;
                cin >> x >> y;
                x += (1LL << 40LL);
                y -= (1LL << 40LL);
                if(!uf.count(x)) uf[x] = x;
                if(!uf.count(y)) uf[y] = y;
                join(x, y);
        }
        map<LL,LL> xfreq, yfreq;
        for(auto v : uf){
                if(v.first >= 0){
                        xfreq[find(v.second)]++;
                } else {
                        yfreq[find(v.second)]++;
                }
        }
        LL ans = 0;
        for(auto v : xfreq){
                LL x = v.first;
                ans += xfreq[x] * yfreq[x];
        }
        cout << ans << endl;
}