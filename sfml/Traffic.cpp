#include "Traffic.h"
void Traffic::addStreet(const Street& newStreet) {
	streetArray.push_back(newStreet);

	int seg_idx = 0;
	int vhead= addVertex(newStreet.head);
	for (auto seg : newStreet.segArray) {
		int vtail = addVertex(seg.tail);
		Route newRoute(newStreet, seg_idx);
		addEdge(vhead, vtail, newRoute);
		const int old_size = size;
		for (int o_vhead = 0; o_vhead < old_size; ++o_vhead) {
			if (o_vhead == vhead) continue;
			for (int o_vtail = 0; o_vtail < old_size; ++o_vtail) {
				if (o_vtail == vtail) continue;
				Route* o_route = matrix[o_vhead][o_vtail];
				if (!o_route) continue;
				Segment o_seg = o_route->getSegment();
				if (sf::Vector2f* intersection = seg.intersect(o_seg)) {
					Point intersectPt(*intersection);

					addIntersection(vhead, vtail, intersectPt, newRoute);
					addIntersection(o_vhead, o_vtail, intersectPt, *o_route);

				}

			}
		}		
	}
}
void Traffic::addIntersection(int vhead, int vtail, const Point& pt, Route& route) {

	int vcut = addVertex(pt);
	vector<Route>divisions;
	route.divide(pt, divisions);
	addEdge(vhead, vcut, divisions[0]);
	addEdge(vcut, vtail, divisions[1]);
	removeEdge(vhead, vtail);

}

int Traffic::getNearVertex(const sf::Vector2f& pos) {
	int min_dist = 1000;
	int vertex = -1;
	for (auto i = 0; i < size; ++i) {
		int curr_dist = dist(base[i].pos, pos);
		if (curr_dist < min_dist) {
			min_dist = curr_dist;
			vertex = i;
		}
	}
	return vertex;
}
 bool Traffic::guide(Auto& vehicle, const sf::Vector2f& dest) {
	vector<int>vertexSet;
	vector<Segment>path;
	int vstart = getNearVertex(vehicle.pos);
	int vdest = getNearVertex(dest);

	if (!findPath(vstart, vdest, vertexSet)) return false;

	for (int i = 0; i < vertexSet.size()-1; i++) {
		int curr = vertexSet[i];
		int next = vertexSet[i + 1];
		path.push_back(matrix[curr][next]->getSegment());
	}
	vector<Point>points;
	for (auto i : vertexSet) {
		points.push_back(base[i]);
	}
	
	//vehicle.follow(points);
	vehicle.follow(path);
	return true;
}
