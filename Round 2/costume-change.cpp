// Copyright (c) 2018 kamyu. All rights reserved.

/*
 * Google Code Jam 2018 Round 2 - Problem B. Graceful Chainsaw Jugglers
 * https://codejam.withgoogle.com/2018/challenges/0000000000007706/dashboard/00000000000459f3
 *
 * Time:  O(N^3 * sqrt(N))
 * Space: O(N)
 *
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

bool dfs(const vector<vector<int>>& edge,
         int u,
         const vector<int>& level,
         vector<bool> *vis,
         vector<int> *pr,
         vector<int> *pr2) {
	(*vis)[u] = true;
	for (auto it = edge[u].begin(); it != edge[u].end(); ++it) {
		int v = (*pr2)[*it];
		if (v == -1 || (!(*vis)[v] && level[u] < level[v] &&
                         dfs(edge, v, level, vis, pr, pr2))) {
			(*pr)[u] = *it, (*pr2)[*it] = u;
			return true;
		}
	}
	return false;
}

int hopcroftKarp(const vector<vector<int>>& edge) {
    const int n = edge.size();
    vector<bool> vis(n);
    vector<int> level(n);
    vector<int> pr(n, -1);
    vector<int> pr2(n, -1);
    
	for (int match = 0; ;) {
		queue<int> Q;
		for (int i = 0; i < n; ++i) {
			if (pr[i] == -1) {
				level[i] = 0;
				Q.emplace(i);
			} else {
                level[i] = -1;
            }
		}
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (auto it = edge[u].begin(); it != edge[u].end(); ++it) {
				int v = pr2[*it];
				if (v != -1 && level[v] < 0) {
					level[v] = level[u] + 1;
					Q.emplace(v);
				}
			}
		}
		for (int i = 0; i < n; ++i) {
            vis[i] = false;
        }
		int d = 0;
		for (int i = 0; i < n; ++i) {
            if (pr[i] == -1 && dfs(edge, i, level, &vis, &pr, &pr2)) {
                ++d;
            }
        }
		if (d == 0) {
            return match;
        }
		match += d;
	}
}

int costume_change() {
    int N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }
    int keep = 0;
    for (int color = -N; color <= N; ++color) {
        vector<vector<int>> edge(2 * N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] == color) {
                    edge[i + N].emplace_back(j);
                }
            }
        }
        keep += hopcroftKarp(edge);
    }
    return N * N - keep;
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++test) {
        cout << "Case #" << test << ": " << costume_change() << endl;
    }
    return 0;
}
