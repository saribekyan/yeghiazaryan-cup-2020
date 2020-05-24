#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace std;

typedef vector<int>   VI;
typedef vector<VI>   VVI;
typedef vector<VVI> VVVI;

typedef pair<int,int> PI;

const int T = 120; // max. period of all masters
const int infty = 999999999;

const int dx[5] = {0, 0, 1, 0,-1};
const int dy[5] = {0, 1, 0,-1, 0};

int R,C;
vector<string> mp;
vector<vector<PI>> patrols;
PI start, jelly;

PI readpos()
{
	int r,c;
	char ch;
	cin >> ch >> r >> c >> ch;
	return make_pair(r-1,c-1);
}

int main()
{
	cin >> R >> C;

	start = readpos();
	jelly = readpos();

	mp.resize(R);
	for(int i=0; i<R; i++) cin >> mp[i];

	int p,n;
	cin >> p;
	patrols.resize(p);
	for(int i=0; i<p; i++) {
		cin >> n;
		patrols[i].resize(n);
		for(int j=0; j<n; j++) patrols[i][j] = readpos();
	}

	VVVI reach(R,VVI(C,VI(T,1))), dist(R,VVI(C,VI(T,infty)));

	for(int t=0; t<T; t++) {

		for(int r=0; r<R; r++)
			for(int c=0; c<C; c++)
				if ( mp[r][c]=='#' ) reach[r][c][t] = 0;

		for(int i=0; i<patrols.size(); i++) {
			int j;
			if ( patrols[i].size()==1 ) {
				j = 0;
			} else {
				j = t%(2*patrols[i].size()-2);
				if ( j>=patrols[i].size() ) j = 2*patrols[i].size()-2-j;
			}
			for(int d=1; d<=4; d++) {
				int r = patrols[i][j].first;
				int c = patrols[i][j].second;
				for(int k=0; 0<=r && r<R && 0<=c && c<C; k++) {
					if ( mp[r][c]=='#' ) break;
					reach[r][c][t] = 0;
					r += dy[d];
					c += dx[d];
				}
			}
		}
	}

	// Do input some consistency checks:
	assert( mp[start.first][start.second]!='#' &&
	        mp[jelly.first][jelly.second]!='#' );
	for(int i=0; i<patrols.size(); i++) {
		for(int j=0; j<patrols[i].size(); j++) {
			assert( mp[patrols[i][j].first][patrols[i][j].second]!='#' );
			if ( j>0 ) assert( abs(patrols[i][j].first -patrols[i][j-1].first)+
			                   abs(patrols[i][j].second-patrols[i][j-1].second)<=1 );
		}
	}

	queue<pair<PI,int>> que;
	que.push(make_pair(start,0));
	int res = infty;

	while ( !que.empty() ) {
		PI pos = que.front().first;
		int d  = que.front().second;
		que.pop();

		// Make sure that we find this before we check if the position
		// is (non-)reachable due to masters in sight.
		if ( pos==jelly ) { res = d; break; }

		if ( reach[pos.first][pos.second][d%T] &&
		     dist[pos.first][pos.second][d%T]==infty ) {
			dist[pos.first][pos.second][d%T] = d;
			for(int i=0; i<=4; i++) {
				int r = pos.first  + dy[i];
				int c = pos.second + dx[i];
				if ( 0<=r && r<R && 0<=c && c<C )
					que.push(make_pair(make_pair(r,c),d+1));
			}
		}
	}

	if ( res<infty ) {
		cout << res << endl;
	} else {
		cout << "IMPOSSIBLE\n";
	}

	return 0;
}
