// Leetcode: 2203. Minimum Weighted Subgraph With the Required Paths
class Solution {
public:
    const long long kInf = 1e18;
    void dijkstra(vector<vector<pair<int,int>>>& graph,int src,vector<long>& w){
        w[src]=0;
        // auto comp = [&w](int n1,int n2){
        //     return w[n1]>w[n2];
        // };>
        priority_queue<pair<long,int>,vector<pair<long,int>>,greater<pair<long,int>>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            auto [wt, minNode] = pq.top();
            pq.pop();
            // 2 benefits of storing weight in pq
            // 1.automatically sort with first value
            // 2.avoid re-execution for older node in pq which has been 
            //   relaxed recently & also present in pq. We could also use set to replace older one with the new
            if(wt!=w[minNode]) continue; // second benefit e.g. [[0,2,4], [0,1,1],[1,2,1]] src: 0, pq: [{2,2}, {4,2}]  
            for(pair<int,int> adj: graph[minNode]){
                int node = adj.first,edgeW = adj.second;
                if(w[node]>w[minNode]+long(edgeW)){
                    w[node] = w[minNode]+long(edgeW);
                    pq.push({w[node],node});
                }
            }
        }
    }
    
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<long>d1(n,kInf);
        vector<long>d2(n,kInf);
        vector<long>dd(n,kInf);
        vector<vector<pair<int,int>>> graph(n), revGraph(n);
        
        for(vector<int> edge: edges){
            int from = edge[0],to = edge[1], wt = edge[2];
            graph[from].push_back({to,wt});
            revGraph[to].push_back({from,wt});
        }
        dijkstra(graph,src1,d1);
        dijkstra(graph,src2,d2);
        dijkstra(revGraph,dest,dd);
        
    
        long long res = kInf;
        for(int i=0;i<n;i++){
            
                if(d1[i]+d2[i]+dd[i]<res)
                    res = d1[i]+d2[i]+dd[i];
            
            // catch(const runtime_error& error){
            //     if(d1[i]<res-d2[i] && d1[i]<res-dd[i] && d1[i]<res-d1[i]-dd[i])
            //         res = d1[i]+d2[i]+dd[i];
            // }
        }
        return res>=kInf?-1:res;
    }
};
