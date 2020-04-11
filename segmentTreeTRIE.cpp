#include        "algorithm"
#include        "iostream"
#include        "numeric"
#include        "iomanip"
#include        "cstring"
#include        "math.h"
#include        "bitset"
#include        "string"
#include        "vector"
#include        "ctime"
#include        "queue"
#include        "stack"
#include        "map"
#include        "set"

#include        "ext/pb_ds/assoc_container.hpp" // Common file
#include        "ext/pb_ds/tree_policy.hpp" // Including tree_order_statistics_node_update
#include        "ext/pb_ds/detail/standard_policies.hpp"

using namespace std;
using namespace __gnu_pbds;


#define          f first
#define          lgn 25
#define          endl '\n'
#define          sc second
#define          pb push_back
#define          N (int)3e5+5
#define          PI acos(-1.0)
#define          int long long 
#define          vi vector<int>
#define          mod 1000000007
#define          ld long double
#define          eb emplace_back
#define          mii map<int,int>
#define          vpii vector<pii>
#define          pii pair<int,int>
#define          pq priority_queue
#define          BLOCK (int)sqrt(N)
#define          test(x) while(x--)
#define          all(x) begin(x),end(x)
#define          allr(x) rbegin(x),rend(x)
#define          fo(i,a,n) for(int i=a;i<n;i++)
#define          rfo(i,n,a) for(int i=n;i>=a;i--)
#define          FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define          time() cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n"
#define 		 bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > 
OS ;

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     const char* comma = strchr (names + 1, ',');
     cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

const int inf = 0x3f3f3f3f;
const int INF = 0x3f3f3f3f3f3f3f3f;

int n,m,k,q;
string s;
vi adj[N];
int a[N];

struct Trie
{
	Trie* bit[2];
	public:

	Trie()
	{
		this->bit[0] = this->bit[1] = NULL;
	}
};

Trie* seg[4*N + 1];

void insert( Trie* root , int val )
{
	Trie* curr = root;

	for( int i = 30; ~i; i--)
	{
		int bit = (val>>i)&1;

		if( !bit )
		{
			if( !curr->bit[0] ) curr->bit[0] = new Trie();

			curr = curr->bit[0];
		}
		else
		{
			if( !curr->bit[1] ) curr->bit[1] = new Trie();
			curr = curr->bit[1];
		}
	}
}

void combine( Trie* &root , Trie* left , Trie* right)
{
	if( !left and !right ) return;
	root = new Trie();

	if( !left )
	{
		root = right;
		return;
	}
	if( !right ) 
	{
		root = left;
		return;
	}

	combine( root->bit[0] , left->bit[0] , right->bit[0] );
	combine( root->bit[1] , left->bit[1] , right->bit[1] );
}

void build(int v = 1 , int tl = 0 , int tr = n-1)
{
	if( tl == tr )
	{
		seg[v] = new Trie();
		insert(seg[v] , a[tl] );
		return;
	}

	int tm = tl+tr>>1;

	build( v<<1 , tl , tm);
	build( v<<1|1 , tm + 1 , tr );

	combine( seg[v] , seg[v<<1] , seg[v<<1|1] );
}

int maximumXor( Trie* root , int x )
{
	Trie* curr = root;
	int mx = 0;

	for( int i = 30; ~i; i--)
	{
		int bit = (x>>i)&1;

		if( !bit )
		{
			if( curr->bit[1] ) 
			{
				mx += (1LL<<i);
				curr = curr->bit[1];
			}
			else curr = curr->bit[0];
		}
		else
		{
			if( curr->bit[0] )
			{
				mx += (1LL<<i);
				curr = curr->bit[0];
			}
			else curr = curr->bit[1];
		}
	}

	return mx;
}

int query(int l , int r , int x , int v = 1 , int tl = 0 , int tr = n -1)
{
	if( l > r ) return 0;
	
	if( tl == l and tr == r )
	{
		int xx = maximumXor( seg[v] , x);
		return xx;
	}

	int tm = tl+tr>>1;

	int aa = query(l , min(r,tm) , x , v<<1 , tl , tm );
	int bb = query( max(l , tm+1) , r , x, v<<1|1 , tm+1, tr );

	return max(aa , bb);
}

// void go()
// {
// 	cin >> n;

// 	fo(i,0,n) cin >> a[i];

// 	build();
// 	cin >> q;

// 	fo(i,0,q)
// 	{
// 		int l , r , x;
// 		cin >> l >> r >> x;
// 		--l;
// 		--r;

// 		int ans = query( l , r , x );

// 		cout << ans << endl;
// 	}
// }

int32_t main()
{
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}

 