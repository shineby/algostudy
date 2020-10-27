#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
// https://www.acmicpc.net/problem/1260
// n�� ������ ����, m�� ������ ����
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
				check[next_node] = true; // �湮 �Ϸ�
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

			// �湮���� �ʾҴٸ�
			if (check[graph[tmp][i]] == false) {
				// ť�� �־��ְ� �湮������ ǥ���Ѵ�.
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

	bool check[1000]; // �湮 ���θ� Ȯ���ϴ� array
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