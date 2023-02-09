#include<bits/stdc++.h>
using namespace std;
// Pragma
#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline","03")
// Macros:
#define f first
#define s second
typedef long long ll;
// debugging macros
#define db(x) cerr << #x << ": " << (x) << '\n';
#define db_v(x) cerr << #x << ": ["; for( auto i : (x) ) cerr << i << ", "; cerr << "]\n";
#define db_p(x) cerr << #x << ": " << (x).first << " " << (x).second << '\n';
// Constraints:
const int maxn = 501010;
const int maxk = 2010;
const int inf = 1600000000;
const int mod2 = 998244353;
const double eps = 1e-9;
// Quick Functions------------------------------------------

int a[maxn], chapeo[maxk], sum[maxk], belong[maxn], mnb[maxk], ac;
int K;

void push(int bl){
    int mn = chapeo[bl];
    mnb[bl] = inf;
    for(int i=K*bl; i<K*(bl+1); i++){
        a[i] += sum[bl];
        if( chapeo[bl] != -1 ){
            if( mn > a[i] )
                mn = a[i];
            a[i] = mn;
        }
        if( a[i] < mnb[bl] )
            mnb[bl] = a[i];
    }
    sum[bl] = 0;
    chapeo[bl] = -1;
}

void pushadd(int bl,int l,int r,int d){

    int mn = chapeo[bl];

    mnb[bl] = inf;

    for(int i=K*bl; i<K*(bl+1); i++){

        a[i] += sum[bl];

        if( chapeo[bl] != -1 ){
            if( mn > a[i] )
                mn = a[i];
            a[i] = mn;
        }

        if( i >= l && i <= r ){
            a[i] += d;
        }

        if( a[i] < mnb[bl] )
            mnb[bl] = a[i];
    }
    sum[bl] = 0;

    chapeo[bl] = -1;
}

void pushchapeo(int bl,int l,int r){

    int mn = chapeo[bl];

    mnb[bl] = inf;

    for(int i=K*bl; i<K*(bl+1); i++){

        a[i] += sum[bl];

        if( chapeo[bl] != -1 ){
            if( mn > a[i] )
                mn = a[i];
            a[i] = mn;
        }

        if( i >= l && i <= r ){
            if( ac > a[i] )
                ac = a[i];
            a[i] = ac;
        }

        if( a[i] < mnb[bl] )
            mnb[bl] = a[i];
    }
    sum[bl] = 0;

    chapeo[bl] = -1;
}

void tsum(int l,int r,int d){
    pushadd(belong[l],l,r,d);
    for(int i=belong[l]+1; i<belong[r]; i++){
        mnb[i] += d;
        sum[i] += d;
        if( chapeo[i] != -1 )
            chapeo[i] += d;
    }
    if(belong[r] > belong[l])
        pushadd(belong[r],l,r,d);
}

void tchapeo(int l,int r){
    ac = inf;
    pushchapeo(belong[l],l,r);
    for(int i=belong[l]+1; i<belong[r]; i++){
        if( chapeo[i] == -1 )
            chapeo[i] = ac;
        else
            chapeo[i] = min( chapeo[i] , ac );
        mnb[i] = min( mnb[i] , chapeo[i] );
        ac = min( ac , mnb[i] );
    }
    if(belong[r] > belong[l])
        pushchapeo(belong[r],l,r);
}

int query(int l,int r){
    int res = inf;
    push(belong[l]);
    for(int i=l; belong[i]==belong[l] && i <= r; i++)
        if( res > a[i] )
            res = a[i];
    for(int i=belong[l]+1; i<belong[r]; i++)
        if( res > mnb[i] )
            res = mnb[i];
    if( belong[r] != belong[l] ){
        push(belong[r]);
        for(int i=r; belong[i]==belong[r]; i--)
            if( res > a[i] )
                res = a[i];
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.setf(ios::fixed); cout.precision(10);

    //freopen("a.in","r",stdin);
    //freopen("a.in","w",stdout);

    for(int i=0; i<maxk; i++)
        mnb[i] = inf;

    int n;
    cin >> n;

    K = max( 1 , (int)sqrt(n) / 2 );

    for(int i=0; i<n; i++){
        cin >> a[i];
        belong[i] = i / K;
        chapeo[belong[i]] = -1;
        sum[belong[i]] = 0;
        mnb[belong[i]] = min( mnb[belong[i]] , a[i] );
    }
    for(int i=n; i<=n+K; i++){
        a[i] = inf;
        belong[i] = i / K;
        chapeo[belong[i]] = -1;
        sum[belong[i]] = 0;
        mnb[belong[i]] = min( mnb[belong[i]] , a[i] );
    }

    int q;
    cin >> q;
    for(int i=0; i<q; i++){
        int t;
        cin >> t;
        if( t == 1 ){
            //suma
            int l, r, d;
            cin >> l >> r >> d;
            l --, r --;
            tsum(l,r,d);
        }
        if( t == 2 ){
            //chapeo
            int l, r;
            cin >> l >> r;
            l --, r --;
            tchapeo(l,r);
        }
        if( t == 3 ){
            //query de min
            int l, r;
            cin >> l >> r;
            l --, r --;
            cout << query(l,r) << '\n';
        }
    }

    return 0;
}
