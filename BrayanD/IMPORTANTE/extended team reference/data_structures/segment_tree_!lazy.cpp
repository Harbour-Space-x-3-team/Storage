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
    vector< T > st;
    ll sz;
    T neutro;

    st (ll n,T neutro) : sz(n),st(4*n),neutro(neutro) {}

    void merge(T v1,T v2)
    {
        ///up to implement
    }

    void up(int node,T v)
    {
        ///up to implement
    }

    void build(int p,int l,int r,T *arr)
    {
        if(l==r)
        {
            st[p]=arr[l];
            return ;
        }
        int mid=(l+r)>>1;

        build(p<<1,l,mid,arr);
        build((p<<1)+1,mid+1,r,arr);

        st[p]=merge(st[p<<1],st[(p<<1)+1]);
    }

    void update(int p,int l,int r,int L,int R,T v)
    {
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
        if(L<=l && r<=R)
            return st[p];
        else if(L>r || l>R)
            return neutro;

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
