#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>
#include <cstring>
using namespace std;

char world[140][64][64];
int dist[64][64];

int main(){
    memset(world,'#',sizeof world);
    memset(dist,-1,sizeof dist);

    int n,m; scanf(" %d %d",&n,&m);
    int sr,sc,tr,tc; scanf(" (%d %d) (%d %d)",&sr,&sc,&tr,&tc);

    for (int i=1; i<=n; i++){
        scanf(" %s",&world[0][i][1]);
        world[0][i][m+1]='#';
        for (int j=1; j<120; j++)
            for (int k=1; k<=m; k++)
                world[j][i][k]=world[0][i][k];
    }
    for (int i=140; i--;)
        for (int j=64; j--;)
            for (int k=64; k--;)
                world[i][j][k]=(world[i][j][k]=='#'?0x10:0x00);

    int masters; scanf(" %d",&masters);
    for (int i=0; i<masters; i++){
        int steps; scanf(" %d",&steps);
        int patrol=max(1,steps*2-2);
        for (int j=0; j<steps; j++){
            int r,c; scanf(" (%d %d)",&r,&c);
            for (int k=0; k<120; k+=patrol){
                world[k+j][r][c]=world[k+patrol-j][r][c]=0x0F;
            }
        }
    }

    for (int t=0; t<120; t++){
        for (int i=0; i<n; i++){
            for (int j=1; j<=m; j++) if (world[t][i][j]<=0x0F) world[t][i][j]|=world[t][i][j-1]&1;
            for (int j=m; j>=1; j--) if (world[t][i][j]<=0x0F) world[t][i][j]|=world[t][i][j+1]&2;
        }
        for (int i=0; i<m; i++){
            for (int j=1; j<=n; j++) if (world[t][j][i]<=0x0F) world[t][j][i]|=world[t][j-1][i]&4;
            for (int j=n; j>=1; j--) if (world[t][j][i]<=0x0F) world[t][j][i]|=world[t][j+1][i]&8;
        }
    }

    // Mark fridge as safe
    for (int i=120; i--;)
        world[i][tr][tc]=0;

    queue<tuple<int,int>> todo;
    todo.emplace(sr,sc);
    dist[sr][sc]=0;
    int res=-1;
    while (not todo.empty()){
        auto rc=todo.front(); int r=get<0>(rc),c=get<1>(rc); todo.pop();
        if (r==tr and c==tc){
            res=dist[r][c];
            break;
        }
        for (int dr=-1; dr<=+1; ++dr)
            for (int dc=-1; dc<=+1; ++dc)
                if (world[0][r+dr][c+dc]==0 and (dr==0 or dc==0) and !~dist[r+dr][c+dc])
                    dist[r+dr][c+dc]=dist[r][c]+1,
                    todo.emplace(r+dr,c+dc);
    }

    if (~res)
        printf("%d\n",res);
    else
        puts("IMPOSSIBLE");
}
