#include <bits/stdc++.h>
using namespace std;
#define int long long

struct SparseTable{
	int n,l;
	vector<vector<int>> sp;

	inline int combine(int x, int y){
		// fill this in
		return __gcd(x,y);
	}

	inline void init(int nn, vector<int> v){
		n = nn;

		l=0;
		while((1 << l) <= n){
			l++;
		}

		sp = vector<vector<int>>(l, vector<int> (n));

		for(int i=0;i<n;i++){
			sp[0][i] = v[i];
		}

		for(int i=1;i<l;i++){
			for(int j=0;j<n;j++){
				int who = j + (1 << (i-1));
				if(who < n)
					sp[i][j] = combine(sp[i - 1][j], sp[i - 1][who]);
			}
		}
	}

	inline int query(int l, int r){
		int i = log2(r - l + 1);
		int v = combine(sp[i][l], sp[i][r + 1 - (1 << i)]);
		return v;
	}
};
