#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>
#define NULL_WEIGHT 100000
using namespace std;



template<typename Edge, typename Vertex >
class Graph
{
	//const int NULL_WEIGHT = 10000;
protected:
	int size;
	vector<vector<Edge*>> matrix;
	vector<Vertex>base;

public:
	Graph() {
		size = 0;
	}

	int addVertex(const Vertex& vertexObj) {
		int v = getVertex(vertexObj);
		if (v != -1) return v;
		size++;
		matrix.push_back(vector<Edge*>());
		base.push_back(vertexObj);

		for (auto& v : matrix) {
			for (int i = v.size(); i < size; i++) {
				v.push_back(nullptr);
			}
		}
		return size - 1;
	}
	int getVertex(const Vertex& vertex) {
		for (int i = 0; i < size; i++ ) {
			if (base[i] == vertex) return i;
		}
		return -1;
	}
	const Vertex& getVertex(const int idx) const {
		return base[idx];
	}
	void addEdge(const int v1, const int v2, const Edge& edge) {
		Edge** curr = &matrix[v1][v2];
		if (*curr) {
			delete* curr;
		}
		*curr = new Edge(edge);
	}
	void removeEdge(const int v1, const int v2) {
		Edge** curr = &matrix[v1][v2];
		if (*curr) {
			delete* curr;
			*curr = nullptr;
		}
		
	}
	int getWeight(const int v1, const int v2) {
		if (matrix[v1][v2]) return *matrix[v1][v2];
		else return NULL_WEIGHT;

	}
	bool peekEdge(const int vsrc, const int vdest) {
		return (matrix[vsrc][vdest]!= nullptr);
	}
	Edge* getEdge(const int vsrc, const int vdest) {
		return matrix[vsrc][vdest];
	}
	bool findPath(const int vsrc, const int vdest, vector <int>& path) {
		struct node {
			int vertex;
			bool visited = false;
			int prev_vertex;
			int weight;
		};
		vector<node> nodes;
		for (int i = 0; i < size; ++i) {
			node curr;
			curr.vertex = i;
			curr.prev_vertex = vsrc;
			curr.weight = getWeight(vsrc, i);
			nodes.push_back(curr);
		}
		nodes[vsrc].visited = true;

		for (int minv = 0; vdest != minv;) {
			minv = 0;
			for (int v = 0; v < size; v++) {
				if (nodes[v].visited) continue;
				minv = (nodes[minv].weight > nodes[v].weight) ? v : minv;
			}

			if (nodes[minv].visited == NULL_WEIGHT) return false;

			nodes[minv].visited = true;

			for (int u = 0; u < size; u++) {
				if (nodes[u].visited) continue;
				int max_weight = nodes[minv].weight + getWeight(minv, u);
				if (nodes[u].weight <= max_weight) continue;
				nodes[u].weight = max_weight;
				nodes[u].prev_vertex = minv;
			}
		}
		for (int vcurr = vdest; vcurr != vsrc; vcurr = nodes[vcurr].prev_vertex) {
			path.push_back(vcurr);
		}
		path.push_back(vsrc);
		reverse(path.begin(), path.end());

		return true;
	}

	void dfs(int v, vector<int>& visited) {
		visited.push_back(v);
		for (auto adj : matrix[v]) {
			if (!include(visited, v)) {
				dfs(adj, visited);
			}
		}

	}
	void bfs(int v) {
		vector<int>visited;
		queue<int>vqueue;
		vqueue.push(v);
		visited.push_back(v);
		while (!vqueue.empty()) {
			int vcurr = vqueue.front();
			vqueue.pop();
			int v = 0;
			for (auto adj : matrix[vcurr]) {
				if (adj) {
					if (!include(visited, v)) {
						visited.push_back(v);
						vqueue.push(v++);
					}
				}
			}
		}
	}


};
