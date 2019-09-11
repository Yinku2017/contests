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


const int maxn=2e5+5;
struct mat
{
    ll a[5][5];
    mat(){}
    void init()
    {
        for(int i=0;i<=4;++i)
            for(int j=0;j<=4;++j)
                a[i][j]=(i==j?0:1e10);
    }
    mat operator+(const mat &t)const
    {
        mat r;
        mem(r.a,127);
        for(int i=0;i<=4;++i)
            for(int j=0;j<=4;++j)
                for(int k=0;k<=4;++k)
                    r.a[i][j]=min(r.a[i][j],a[i][k]+t.a[k][j]);
        return r;
    }
    void show()
    {
        for(int i=0;i<=4;++i)
            for(int j=0;j<=4;++j)
            cout<<a[i][j]<<"\t\n"[j==4];cout<<endl;
    }
}t[maxn<<2];
char s[maxn];
void build(int l,int r,int rt)
{
    t[rt].init();
    if(l==r)
    {
        if(s[l]=='2')
            t[rt].a[0][0]=1,t[rt].a[0][1]=0;
        else if(s[l]=='0')
            t[rt].a[1][1]=1,t[rt].a[1][2]=0;
        else if(s[l]=='1')
            t[rt].a[2][2]=1,t[rt].a[2][3]=0;
        else if(s[l]=='9')
            t[rt].a[3][3]=1,t[rt].a[3][4]=0;
        else if(s[l]=='8')
            t[rt].a[3][3]=1,t[rt].a[4][4]=1;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,lson);
    build(m+1,r,rson);
    t[rt]=t[lson]+t[rson];
}

mat query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
        return t[rt];
    int m=(l+r)>>1;
    if(m>=R)
        return query(L,R,l,m,lson);
    else if(m<L)
        return query(L,R,m+1,r,rson);
    else return query(L,R,l,m,lson)+query(L,R,m+1,r,rson);
}

int main()
{
    int n,q;
    while(~scanf("%d%d",&n,&q))
    {
        scanf("%s",s+1);
        reverse(s+1,s+n+1);
        build(1,n,1);
        while(q--)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            l=n-l+1,r=n-r+1;
            if(l>r)
                swap(l,r);
            mat re=query(l,r,1,n,1);
            printf("%lld\n",re.a[0][4]<=n?re.a[0][4]:-1);
        }

    }
}
