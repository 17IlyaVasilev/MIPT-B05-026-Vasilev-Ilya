#include<iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;


class Graph {
private:
    vector<vector<int>> list;

public:
    Graph() = default;

    Graph(const int& n) {
        list.assign(n + 1, vector<int>(0));
    }

    ~Graph() {}

    void insert(const int& a, const int& b) {
        list[a].push_back(b);
    }

    vector<vector<int>> get() {

        return list;
    }


};


void dfs(int v, vector<vector<int>>& list, vector<int>& used, vector<int>& path, bool& flag) {
    used[v] = 1;
    path.push_back(v);
    for (int i = 0; i < list[v].size(); i++) {
        if (flag)
            break;
        if (used[list[v][i]] == 1) {
            path.push_back(list[v][i]);
            flag = true;
            return;
        }
        else dfs(list[v][i], list, used, path, flag);
    }
    if (!flag) {
        used[v] = 2;
        path.pop_back();
    }
}


pair<string, vector<int>> result(Graph& graph, const int& n, const int& m) {
    vector<vector<int>> list = graph.get();
    bool flag = false;
    vector<int> used(n + 1, 0);
    vector<int> path;
    string res_str;
    vector<int> res_vec;

    for (int i = 1; i <= n; ++i) {
        if (used[i] == 0) {
            dfs(i, list, used, path, flag);
            if (flag == 1) {
                break;
            }
        }
    }

    if (flag) {
        int i = path.size() - 2;
        while (path[i] != path[path.size() - 1]) {
            i--;
        }
        res_str = "YES";
        for (; i < path.size() - 1; ++i) {
            res_vec.push_back(path[i]);
        }
    }
    else {
        res_str = "NO";
    }

    return { res_str, res_vec };
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph.insert(a, b);
    }

    auto ans = result(graph, n, m);
    cout << ans.first << endl;

    for (int i = 0; i < ans.second.size(); ++i) {
        cout << ans.second[i] << ' ';
    }

    return 0;
}