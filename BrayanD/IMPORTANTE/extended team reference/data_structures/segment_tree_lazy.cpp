#include <bits/stdc++.h>
#define db(x) cout << (x) << '\n';
#define all(v) (v).begin(),(v).end()
#define allr(v) (v).rbegin(),(v).rend()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pii;
typedef pair<double,ll> pdi;
typedef pair<string,ll> psi;
typedef pair<ll,string> pls;
typedef pair<ll,pii> pip;
typedef pair<pii,pii> ppp;

template <typename T>
struct st{
    vector< T > st,lazy;
    ll sz;
    T neutroQ,neutroL;

    st (ll n,T neutroq,T neutrol) : sz(n),st(4*n),lazy(4*n),neutroQ(neutroQ),neutroL(neutrol) {}

    void merge(T v1,T v2)
    {
        ///up to implement
    }

    void up(int node,T v)
    {
        ///up to implement
    }

    void push(int node,int l,int r)
    {
        if(l==r)
            return ;
        if(st[node]==neutroL)
            return ;
        ///up to implement
    }

    void build(int p,int l,int r,T *arr)
    {
        if(l==r)
        {
            st[p]=arr[l];
            lazy[p]=neutroL;
            return ;
        }
        int mid=(l+r)>>1;

        build(p<<1,l,mid,arr);
        build((p<<1)+1,mid+1,r,arr);

        st[p]=merge(st[p<<1],st[(p<<1)+1]);
        lazy[p]=neutroL;
    }

    void update(int p,int l,int r,int L,int R,T v)
    {
        push(p,l,r);

        if(L<=l && r<=R)
        {
            up(p,v);
            return ;
        }
        int mid=(l+r)>>1;

        if(L<=mid)
            update(p<<1,l,mid,L,R,v);
        if(R>mid)
            update((p<<1)+1,mid+1,r,L,R,v);

        st[p]=merge(st[p<<1],st[(p<<1)+1]);
    }

    T query(int p,int l,int r,int L,int R)
    {
        push(p,l,r);

        if(L<=l && r<=R)
            return st[p];
        else if(L>r || l>R)
            return neutroQ;

        int mid=(l+r)>>1;

        st[p]=merge(query(p<<1,l,mid,L,R),query((p<<1)+1,mid+1,r,L,R));
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);



    return 0;
}
