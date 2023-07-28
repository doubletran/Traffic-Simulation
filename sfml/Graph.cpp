#include "Graph.h"
RouteGraph::RouteGraph() {
	size = 0;

}

void RouteGraph::add() {
	size++;
	matrix.push_back(vector<int>(0));
	for (auto& v : matrix) {
		for (int i = v.size(); i < size; i++) {
			v.push_back(1000);
		}
	}
}

void RouteGraph::setEdge(const int vsrc, const int vdest, const int edge) {
	matrix[vsrc][vdest] = edge;
}

bool include(const vector<int>&src, int target) {
	for (auto item : src) {
		if (item == target) return true;
	}
	return false;
}
bool RouteGraph::findPath(const int vsrc, const int vdest, vector <int>& vertexSet) {
	vertexSet.push_back(vsrc);
	vector <int> weight;

	for (int i = 0; i < size; ++i) {
		weight.push_back(matrix[vsrc][i]);
	}
	int minv = 0;
	while ((vdest != minv) || (vertexSet.size() < size) || (vertexSet.size() == 2)) {
		minv = 0;
		for (int v = 0; v < size; v++) {
			if (!include(vertexSet, v)) {

				minv = ((weight[minv] > weight[v]) ||(minv == 0)) ? v : minv;
			}
			if (v == size - 1) {
				if (weight[minv] == 1000) return false;
				vertexSet.push_back(minv);
				for (int u = 0; u < size; u++) {
					if (!include(vertexSet, u)) {
						if (weight[u] > weight[minv] + matrix[minv][u]) {
							weight[u] = weight[minv] + matrix[minv][u];
						}
					}
				}
			}
		}
	}
	if (vdest != minv) return false;
	return true;
}