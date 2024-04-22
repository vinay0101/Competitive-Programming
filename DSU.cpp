class DSU {
public:
    vector<int> parent, rank;
    DSU(ll n){
        parent.resize(n, 0);
        rank.resize(n, 0);
        
        for(int i=0;i<n;i++) parent[i] = i;
    }
    
    ll Find(ll x){
        return parent[x] = parent[x] == x ? x : Find(parent[x]);
    }
    
    bool Union(int x, int y){
        ll xset = Find(x), yset = Find(y);
        if(xset != yset){
            rank[xset] < rank[yset] ? parent[xset] = yset : parent[yset] = xset;
            rank[xset] += rank[xset] == rank[yset];
            return true;
        }
        return false;
    }
};

// DSU dsu(n);
// dsu.Union(edgeList[i][0], edgeList[i][1]); // Connect 2 nodes
// if(dsu.Find(q[0]) == dsu.Find(q[1])) // Find will go to the Parent : Same Component - Same Parent
