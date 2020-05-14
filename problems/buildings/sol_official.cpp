#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)

typedef long long ll;
typedef vector <int> vi;
typedef pair <int, int> pii;

#define maxn 200010

int n;
int x[maxn], y[maxn], c[maxn], p[maxn];
//map <int, vi> mx, my;
vector <int> g[maxn];

void dfs( int u, int cc )
{
  c[u] = cc;
  forn (i, g[u].size())
    if (c[g[u][i]] == 0)
      dfs(g[u][i], cc);
}

bool xless( const int &a, const int &b )
{
  return x[a] < x[b];
}
         
bool yless( const int &a, const int &b )
{
  return y[a] < y[b];
}

int read()
{
  int t = 0, s = 1;
  int c = getc(stdin);
  while (c <= 32)
    c = getc(stdin);
  if (c == '-')
    s = -1, c = getc(stdin);
  while (isdigit(c))
    t = t * 10 + c - '0', c = getc(stdin);
  return t * s;
}
         
int main()
{
  scanf("%d", &n);
  forn (i, n)
  {
    x[i] = read();
    y[i] = read();
  }
//  scanf("%d%d", &x[i], &y[i]);

  fprintf(stderr, "!\n");
  forn (i, n)
    p[i] = i;
  sort(p, p + n, xless);
  forn (i, n)
    if (i != 0 && x[p[i]] == x[p[i - 1]])
      g[p[i]].pb(p[i - 1]),
      g[p[i - 1]].pb(p[i]);

  forn (i, n)
    p[i] = i;
  sort(p, p + n, yless);
  forn (i, n)
    if (i != 0 && y[p[i]] == y[p[i - 1]])
      g[p[i]].pb(p[i - 1]),
      g[p[i - 1]].pb(p[i]);
     
/*
  forn (i, n)
    mx[x[i]].pb(i),
    my[y[i]].pb(i);

  forit(it, mx)
    forn (i, it->se.size() - 1)
      g[it->se[i]].pb(it->se[i + 1]),
      g[it->se[i + 1]].pb(it->se[i]);
  forit(it, my)
    forn (i, it->se.size() - 1)
      g[it->se[i]].pb(it->se[i + 1]),
      g[it->se[i + 1]].pb(it->se[i]);
*/

  memset(c, 0, sizeof(c));
  int cc = 0;
  forn (i, n)
    if (c[i] == 0)
      dfs(i, ++cc);

  vector <vi> a(cc);
  forn (i, n)
    a[c[i] - 1].pb(i);

  fprintf(stderr, "!\n");
  ll ans = 0;
  forn (i, cc)
  {
    set <int> sx, sy;
    forn (j, a[i].size())
      sx.insert(x[a[i][j]]),
      sy.insert(y[a[i][j]]);
    ans += (ll)sx.size() * (ll)sy.size();
  }

  printf(INT64 "\n", ans);

  return 0;
}
