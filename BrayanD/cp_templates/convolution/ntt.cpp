namespace ntt
{
    typedef long long ll;

    ll inv(ll b, ll M)
    {
        ll u = 1, x = 0, s = b, t = M;
        while (s)
        {
            ll q = t / s;
            swap(x -= u * q, u);
            swap(t -= s * q, s);
        }
        return (x %= M) >= 0 ? x : x + M;
    }

    ll pow(ll a, ll b, ll M)
    {
        ll x = 1;
        for (; b > 0; b >>= 1)
        {
            if (b & 1)
                x = (a * x) % M;
            a = (a * a) % M;
        }
        return x;
    }

    // fast modulo transform
    //   (1) n = 2^k < 2^23
    //   (2) only predetermined mod can be used
    void fmt(vector<ll> &x, ll mod, int sign = +1)
    {
        int n = x.size();
        ll h = pow(3, (mod - 1) / n, mod);
        if (sign < 0) h = inv(h, mod);
        for (int i = 0, j = 1; j < n - 1; ++j)
        {
            for (int k = n >> 1; k > (i ^= k); k >>= 1);
            if (j < i) swap(x[i], x[j]);
        }
        for (int m = 1; m < n; m *= 2)
        {
            ll w = 1, wk = pow(h, n / (2 * m), mod);
            for (int i = 0; i < m; ++i)
            {
                for (int j = i; j < n; j += 2 * m)
                {
                    ll u = x[j], d = x[j + m] * w % mod;
                    if ((x[j] = u + d) >= mod)
                        x[j] -= mod;
                    if ((x[j + m] = u - d) < 0)
                        x[j + m] += mod;
                }
                w = w * wk % mod;
            }
        }
        if (sign < 0)
        {
            ll n_inv = inv(n, mod);
            for (auto &a : x)
                a = (a * n_inv) % mod;
        }
    }

    // convolution via fast modulo transform
    vector<ll> conv(vector<ll> x, vector<ll> y, ll mod)
    {
        fmt(x, mod, +1);
        fmt(y, mod, +1);
        for (int i = 0; i < x.size(); ++i)
            x[i] = (x[i] * y[i]) % mod;
        fmt(x, mod, -1);
        return x;
    }

    // general convolution by using fmts with chinese remainder thm.
    vector<ll> convolution(vector<ll> x, vector<ll> y, ll mod)
    {
        for (auto &a : x) a %= mod;
        for (auto &b : y) b %= mod;
        int n = x.size() + y.size() - 1, size = n - 1;
        for (int s : { 1, 2, 4, 8, 16 })
            size |= (size >> s);
        size += 1;
        x.resize(size);
        y.resize(size);
        ll A = 167772161, B = 469762049, C = 1224736769, D = (A * B % mod);
        vector<ll> z(n), a = conv(x, y, A), b = conv(x, y, B), c = conv(x, y, C);
        for (int i = 0; i < n; ++i)
        {
            z[i] = A * (104391568ll * (b[i] - a[i]) % B);
            z[i] += D * (721017874ll * ( c[i] - (a[i] + z[i]) % C + C ) % C);
            if ((z[i] = (z[i] + a[i]) % mod) < 0)
                z[i] += mod;
        }
        return z;
    }
}
