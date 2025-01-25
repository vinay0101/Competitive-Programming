#include <iostream>
#include <vector>
using namespace std;

const int mod = 1e9 + 7; // Define your modulo value

// Function to compute x^y under modulo mod
long long modPow(long long x, long long y, long long mod) {
    long long result = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1) {
            result = (result * x) % mod;
        }
        x = (x * x) % mod;
        y >>= 1;
    }
    return result;
}

// Function to compute modular inverse using Fermat's Little Theorem
long long modInverse(long long x, long long mod) {
    return modPow(x, mod - 2, mod);
}

// Precompute factorials and modular inverses
void precomputeFactorials(vector<long long>& fact, vector<long long>& invFact, int n, int mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = modInverse(fact[n], mod);
    for (int i = n - 1; i >= 0; --i) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

// Function to compute nCr % mod
long long nCr(int n, int r, const vector<long long>& fact, const vector<long long>& invFact, int mod) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}

int main() {
    int n, r;
    cin >> n >> r;

    // Maximum value of n you need to support
    int maxN = 1e5;

    // Precompute factorials and modular inverses
    vector<long long> fact(maxN + 1), invFact(maxN + 1);
    precomputeFactorials(fact, invFact, maxN, mod);

    // Compute nCr % mod
    cout << nCr(n, r, fact, invFact, mod) << endl;

    return 0;
}
