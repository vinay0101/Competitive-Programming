#include<bits/stdc++.h>
using namespace std;

const static int MAX = 1e5+5;
bool prime[MAX]; //Is that number prime or not
int spf[MAX]; //Smallest prime factor of that number

void sieve(){
	fill(prime, prime+MAX, true);
	for(int i=1; i<MAX; i++)
		spf[i] = i;
	prime[0] = prime[1] = false;

	for(int i=2; i*i<MAX; i++){
		if(prime[i]){
			for(int j=i*i ;j<MAX; j+=i){
				if(prime[j])
					spf[j]=i;
				prime[j] = false;
			}
		}
	}
}

vector<int> getFactorisation2(int x){
	vector<int> ret;
	unordered_map<int,int> mp;
	while(x != 1){
		mp[spf[x]]++;
		x = x / spf[x];
	}
	for(auto p: mp) ret.push_back(p.first);
	return ret;
}

bool isPrime(int n){
	if(n==1) return false;

	for(int i=2; i*i<=n; i++){
		if(n%i==0)
			return false;
	}
	return true;
}

vector<pair<int,int>> primeFactors(int n){
	vector<pair<int,int>> ans;
	for(int i=2; i*i<=n; i++){
		if(n%i==0){
			int cnt=0;
			while(n%i==0){
				cnt++;
				n=n/i;
			}
			ans.push_back({i,cnt});
		}
	}
	if(n>2) ans.push_back({n,1});
	return ans;
}

vector<bool> sieve(int n){
	vector<bool> isPrime(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i=2; i*i<=n; i++){
		if(isPrime[i]){
			for(int j=i*i; j<=n; j++){
				isPrime[j] = false;
			}
		}
	}
	return isPrime;
}

vector<bool> getPrimesInRange(long long L, long long R){
	vector<bool> prime = sieve(sqrt(R));
	vector<bool> isPrime(R-L+1, true);

	for(long long i=2; i*i<=R; i++){
		if(!isPrime[i]) continue;
		for(long long j= max(i*i, (L+i-1)/i*i); j<=R; j+=i){
			isPrime[j-L] = false;
		}
	}
	if(L==1) isPrime[0] = false;
	return isPrime;
}
