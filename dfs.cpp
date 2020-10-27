#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
// https://www.acmicpc.net/problem/1260
// n은 정점의 개수, m은 간선의 개수
// <input>
// 4 5 1
// 1 2 
// 1 3
// 1 4
// 2 4
// 3 4
// <result>
// DFS {1, 2, 4, 3}
// BfS {1, 2, 3, 4}

void recursive_dfs(int start, vector<int> graph[], bool check[]) {
	check[start] = true;
	printf("%d ", start);

	for (int i = 0; i < graph[start].size(); i++) {
		int next_node = graph[start][i];
		if (check[next_node] == false) {
			recursive_dfs(next_node, graph, check);
		}
	}
}

void dfs(int start, vector<int> graph[], bool check[]) {
	stack<int> s;
	s.push(start);
	check[start] = true;
	printf("%d ", start);

	while (!s.empty()) {
		int cur_node = s.top();
		s.pop();
		for (int i = 0; i < graph[cur_node].size(); i++) {
			int next_node = graph[cur_node][i];
			if (check[next_node] == false) {
				// not visisted node
				printf("%d ", next_node);
				check[next_node] = true; // 방문 완료
				s.push(cur_node);
				s.push(next_node);
				break;
			}
		}
	}

}

void bfs(int start, vector<int> graph[], bool check[]) {
	queue<int> q;

	q.push(start);
	check[start] = true;

	while (!q.empty()) {
		int tmp = q.front();
		q.pop();
		printf("%d ", tmp);
		for (int i = 0; i < graph[tmp].size(); i++) {

			// 방문하지 않았다면
			if (check[graph[tmp][i]] == false) {
				// 큐에 넣어주고 방문했음을 표시한다.
				q.push(graph[tmp][i]);
				check[graph[tmp][i]] = true;
			}
		}
	}

}



int main() {
	int n, m, start;
	cin >> n >> m >> start;

	vector<int>* graph = new vector<int>[n + 1];
	// graph[0] = vector<int>
	// graph[1] = vector<int>
	// graph[n] = vector<int>

	bool check[1000]; // 방문 여부를 확인하는 array
	fill(check, check + n + 1, false);

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;

		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	recursive_dfs(start, graph, check);
}