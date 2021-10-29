#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 998244353;

int C[1005];
vector<pair<int, int>> G[1005];

bool dfs(int pre, int now, int tar){
    if(now == tar){
        return true;
    }
    for(auto [nxt, i] : G[now]){
        if(nxt == pre) continue;
        if(dfs(now, nxt, tar)){
            C[i]++;
            return true;
        }
    }
    return false;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(C, 0, sizeof(C));

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> P(M);
    for(int i = 0; i < M; i++){
        cin >> P[i];
    }
    
    for(int i = 0; i < N - 1; i++){
        int U, V;
        cin >> U >> V;
        G[U].push_back({V, i});
        G[V].push_back({U, i});
    }
    
    for(int i = 0; i < M - 1; i++){
        dfs(P[i], P[i], P[i + 1]);
    }

    int tot = 0;
    for(int i = 0; i < N - 1; i++){
        tot += C[i];
    }
    if((tot + K) % 2 || tot + K < 0){
        cout << 0;
        return 0;
    }
    
    int target = (tot + K) / 2;
    vector<long long> f(target + 1, 0);
    // f[i][j] = f[i - 1][j - C[i]]
    f[0] = 1;
    for(int j = 0; j < N - 1; j++){
        for(int i = target; i >= C[j]; i--){
            f[i] += f[i - C[j]];
            f[i] %= MOD;
        }
    }
    cout << f[target];
    return 0;
}
