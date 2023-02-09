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

///con fractional cascading(query en log(n))
struct st2d{
    vector<vector< vector< int > > > st;
    int sz;

    st2d (int n) : sz(n),st(4*n) {
        for(int i=0;i<4*n;i++)
            for(int j=0;j<5;j++)
                st[i].push_back({});
    }

    void build(int p,int l,int r,vector<int> *base)
    {
        if(l==r)
        {
            for(auto y : base[l])
                st[p][0].push_back(y);
            return;
        }
        int mid=(l+r)>>1;

        build(p<<1,l,mid,base);
        build((p<<1)+1,mid+1,r,base);

        int pl=0,pr=0;
        while(pl<st[p<<1][0].size() && pr<st[(p<<1)+1][0].size())
        {
            if(st[p<<1][0][pl]<st[(p<<1)+1][0][pr])
            {
                st[p][0].push_back(st[p<<1][0][pl]);
                pl++;
            }
            else
            {
                st[p][0].push_back(st[p<<1][0][pr]);
                pr++;
            }
        }

        while(pl<st[p<<1][0].size())
        {
            st[p][0].push_back(st[p<<1][0][pl]);
            pl++;
        }

        while(pr<st[(p<<1)+1][0].size())
        {
            st[p][0].push_back(st[(p<<1)+1][0][pr]);
            pr++;
        }

        for(auto y : st[p][0])
        {
            int i0=lower_bound(st[p<<1][0].begin(),st[p<<1][0].end(),y)-st[p<<1][0].begin();
            int i1=upper_bound(st[p<<1][0].begin(),st[p<<1][0].end(),y)-st[p<<1][0].begin();
            int i2=lower_bound(st[(p<<1)+1][0].begin(),st[(p<<1)+1][0].end(),y)-st[(p<<1)+1][0].begin();
            int i3=upper_bound(st[(p<<1)+1][0].begin(),st[(p<<1)+1][0].end(),y)-st[(p<<1)+1][0].begin();
            st[p][1].push_back(i0);
            st[p][2].push_back(i1);
            st[p][3].push_back(i2);
            st[p][4].push_back(i3);
        }
    }

    int query(int p,int l,int r,int x,int y,int ll,int lr,int L,int R)
    {
        if(p==1)
        {
            int i0=lower_bound(st[1][0].begin(),st[1][0].end(),x)-st[1][0].begin();
            int i1=upper_bound(st[1][0].begin(),st[1][0].end(),y)-st[1][0].begin()-1;

            int mid=r>>1;

            return query(2,0,mid,x,y,st[1][1][i0],st[1][2][i1]-1,L,R)+query(3,mid+1,r,x,y,st[1][3][i0],st[1][4][i1]-1,L,R);
        }
        if(L<=l && r<=R)
        {
            return lr-ll+1;
        }
        if(l>R || r<L)
            return 0;
        if(lr==ll-1)
            return 0;

        int mid=(l+r)>>1;

        return query(p<<1,l,mid,x,y,st[p][1][ll],st[p][2][lr]-1,L,R)+query((p<<1)+1,mid+1,r,x,y,st[p][3][ll],st[p][4][lr]-1,L,R);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);



    return 0;
}
