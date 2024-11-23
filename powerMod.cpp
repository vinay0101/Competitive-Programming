ll powMod(ll x, ll p, ll modulus){
    ll result =1;

    while(p>0){
        // If p is odd, multiply result with x.
        if(p%2==1){
            result = ((result%modulus) * (x%modulus))%modulus;
        }

        // Square x and divide p by 2.
        x = (x*x) % modulus;
        p= p/2;
    }
    return result;
}

int powMod(int a, ll b, int mod){
    if(b == 0) return 1;
    if(b%2 == 0){
        //even 
        int p = powMod(a, b/2, mod);
        return 1LL * p * p % mod;
    }
    else{
        int p = powMod(a, (b-1)/2, mod);
        return 1LL * p * p % mod * a % mod;   
    }
}
