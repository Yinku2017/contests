//#pragma GCC optimize(2)


#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#include<ext/rope>
using namespace __gnu_cxx;
//using namespace __gnu_pbds;
void err(istream_iterator<string> it){cerr<<endl;}
template<typename T, typename... Args>void err(istream_iterator<string> it, T a, Args... args){cerr << *it << " = " << a << " , ";err(++it, args...);}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define mem(a,b) memset((a),b,sizeof((a)))
#define fpre(x) cout<<fixed<<setprecision(x)
#define clr(v) (v).clear()
#define pii pair<int,int>
#define pdd pair<double,double>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp make_pair
#define ep emplace_back
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define lowbit(i) (i&(-i))
#define lson rt<<1
#define rson lson|1
#define fi first
#define se second
const double eps=1e-10;
inline int dcmp(double x){if(x<-eps)return -1;if(x>eps)return 1;return 0;}
//-----------------------------------------------head


const ll mod=998244353;
const int maxn=2e5+5;
ll qp(ll x,ll n)
{
    ll r=1;
    for(x%=mod;n;n>>=1,x=x*x%mod)
        if(n&1)
            r=r*x%mod;
    return r;
}
ll inv(ll x)
{
    return qp(x,mod-2);
}
int oklen;
ll val[maxn],a[55];
char s[maxn];
struct SAM
{
	struct node
	{
		int to[26];
		int len,link;
	}t[2*maxn];
	int sz,lst;
	ll ans;
	int newnode(int len)
	{
	    ++sz;
		mem(t[sz].to,0);
		t[sz].len=len;
		t[sz].link=0;
		return sz;
	}
	void init()
	{
	    ans=0;
		sz=0;
		lst=1;
		newnode(0);
	}
	void add(char w)
	{
	    int c=w-'a';
		int p=lst;
		int now=newnode(t[p].len+1);
		while(p&&!t[p].to[c])
		{
			t[p].to[c]=now;
			p=t[p].link;
		}
		if(!p)
			t[now].link=1;
		else
		{
			int q=t[p].to[c];
			if(t[p].len+1==t[q].len)
				t[now].link=q;
			else
			{
				int clone=newnode(t[p].len+1);
				t[clone].link=t[q].link;
				for(int i=0;i<26;++i)
					t[clone].to[i]=t[q].to[i];
				t[q].link=clone;
				t[now].link=clone;
				while(p&&t[p].to[c]==q)
				{
					t[p].to[c]=clone;
					p=t[p].link;
				}
			}
		}
		lst=now;
		int le=min(oklen,t[now].len),fle=t[t[now].link].len;
		if(fle+1<=oklen)
            ans=(ans+(val[le]-val[fle]+mod)%mod)%mod;
        assert(ans>=0);
	}
}sam;

ll inv26[maxn];
ll pw[maxn][55];
void init()
{
    inv26[0]=1;
    ll nv=inv(26);
    for(int i=1;i<maxn;++i)
        inv26[i]=inv26[i-1]*nv%mod;
    for(int i=1;i<maxn;++i)
    {
        pw[i][0]=1;
        for(int j=1;j<=50;++j)
            pw[i][j]=pw[i][j-1]*i%mod;
    }
}
int main()
{
    init();
    int _;
    for(scanf("%d",&_);_;--_)
    {
        sam.init();
        int l,k,n,m;
        scanf("%d%d%d%d",&l,&k,&n,&m);
        scanf("%s",s);
        for(int i=0;i<=k;++i)
            scanf("%lld",a+i);
        for(int i=1;i<=l+m;++i)
        {
            ll v=0;
            for(int j=0;j<=k;++j)
                v=(v+a[j]*pw[i][j])%mod;
            v=v*inv26[i]%mod;
            v=v*max(n-i+1,0)%mod;
            val[i]=(v+val[i-1])%mod;
        }
        oklen=n;
        for(int i=0;i<l;++i)
            sam.add(s[i]);
        printf("%lld\n",sam.ans);
        while(m--)
        {
            char cc[2];
            scanf("%s",cc);
            sam.add(cc[0]);
            printf("%lld\n",sam.ans);
        }
    }
}
