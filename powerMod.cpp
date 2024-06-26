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
