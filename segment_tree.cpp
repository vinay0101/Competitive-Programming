#include <bits/stdc++.h>
 
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
// template <class T> void _print(ordered_set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

class SGTree{
    vector<int> seg;
public:
    SGTree(int n){
        seg.resize(4*n+1);
    }

    void build(int ind, int low, int high, vector<int> arr){
        if(low==high){
            seg[ind] = arr[low];
            return;
        }
        int mid = (low+high)/2;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }

    int query(int ind, int low, int high, int l, int r){
        // no overlap
        // l r low high or low high l r
        if(high<l || r<low) return INT_MAX;

        // complete overlap
        // [l low high r]
        if(l<=low && high<=r) return seg[ind];

        int mid = (low+high)/2;
        int left = query(2*ind+1, low, mid, l, r);
        int right = query(2*ind+2, mid+1, high, l, r);
        return min(left, right); 
    }

    void update(int ind, int low, int high, int i, int val){
        if(low==high){
            seg[ind] = val;
            return;
        }

        int mid = (low+high)/2;
        if(i<=mid) update(2*ind+1, low, mid, i, val);
        else update(2*ind+2, mid+1, high, i, val);
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }
};
 
void solve(){
    int n, q;
    cin>> n>>q;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    SGTree s1(n);
    s1.build(0,0,n-1,arr);
    for(int i=0;i<q;i++){
        int t;
        cin>>t;
        if(t==1){
            int l, r;
            cin>>l>>r;
            cout<<s1.query(0,0,n-1,l,r)<<endl;
        }
        else{
            int j,val;
            cin>>j>>val;
            s1.update(0,0,n-1,j,val);
            arr[j]=val;
        }
    }
}
 
int main(){
    #ifndef ONLINE_JUDGE
        freopen("Error.txt", "w", stderr);
    #endif
    ios_base::sync_with_stdio(false);cin.tie(NULL);
 
    int t;
    cin >> t;
 
    while(t--){
        solve();
    }
}
