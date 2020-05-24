#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <tuple>
#include <map>
using namespace std;

char world[140][64][64];

struct DistanceField{
  private:
    int dist[64][64];

  public:
    DistanceField(){for (int i=64; i--;) for (int j=64; j--;) dist[i][j]=-1;}
    int *const operator[](int const i){return dist[i];}
};

map<int,DistanceField> dist;

int main(){
    memset(world,'#',sizeof world);

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

    queue<tuple<int,int,int>> todo;
    todo.emplace(0,sr,sc);
    dist[0][sr][sc]=0;
    int res=-1;
    while (not todo.empty()){
        auto trc=todo.front(); int t=get<0>(trc),r=get<1>(trc),c=get<2>(trc); todo.pop();
        if (r==tr and c==tc){
            res=dist[t][r][c];
            break;
        }
        for (int dr=-1; dr<=+1; ++dr)
            for (int dc=-1; dc<=+1; ++dc)
                if (world[(t+1)%120][r+dr][c+dc]==0 and (dr==0 or dc==0) and !~dist[t+1][r+dr][c+dc])
                    dist[t+1][r+dr][c+dc]=dist[t][r][c]+1,
                    todo.emplace(t+1,r+dr,c+dc);
    }

    if (~res)
        printf("%d\n",res);
    else
        printf("-1\n");
}
