#include "Traffic.h"
void Traffic::addStreet(const Street& newStreet) {

	int seg_idx = 0;
	int vhead= addPoint(newStreet.head);
	for (auto seg : newStreet.segArray) {
		int vtail = addPoint(seg.tail);
		Route newRoute(newStreet, seg_idx);
		addRoute(vhead, vtail, newRoute);
		const int old_size = size;
		for (int o_vhead = 0; o_vhead < old_size; ++o_vhead) {
			if (o_vhead == vhead) continue;
			for (int o_vtail = 0; o_vtail < old_size; ++o_vtail) {
				if (o_vtail == vtail) continue;
				if (routeMatrix[o_vhead][o_vtail]) {
					Segment o_seg = routeMatrix[o_vhead][o_vtail]->getSegment();
					if (sf::Vector2f* intersection = seg.intersect(o_seg)) {

						Point intersectPt(*intersection);

						addIntersection(vhead, vtail, intersectPt, newRoute);
						addIntersection(o_vhead, o_vtail, intersectPt, newRoute);

					}

				}
			}
		}		
	}
}
void Traffic::addIntersection(int vhead, int vtail, const Point& pt, Route& route) {
	int vcut = addPoint(pt);
	vector<Route>divisions;
	route.divide(pt, divisions);
	addRoute(vhead, vcut, divisions[0]);
	addRoute(vcut, vtail, divisions[1]);
	deleteRoute(vhead, vtail);

}
void Traffic::deleteRoute(int vhead, int vtail) {
	Route **route = &routeMatrix[vhead][vtail];

	if (*route) {
		delete *route;
		*route = nullptr;
	} 
}
void Traffic::addRoute(int vhead, int vtail, const Route& newRoute) {
	routeMatrix[vhead][vtail] = new Route(newRoute);
}
int Traffic::addPoint(const Point& pt) {
	int vertex = getVertex(pt);
	if (vertex == -1) {
		size++;
		base.push_back(pt);
		routeMatrix.push_back(vector<Route*>());
		for (auto& vsrc : routeMatrix) {
			for (int i = vsrc.size(); i < size; i++) {
				vsrc.push_back(nullptr);
			}
		}
		vertex = base.size() - 1;
	}
	return vertex;

}
int Traffic::getVertex(const Point& pt) {
	for (auto i = 0; i < base.size(); ++i) {
		if (base[i].pos == pt.pos) return i;
	}
	return -1;
}
int Traffic::getNearVertex(const sf::Vector2f& pos) {
	int min_dist = 1000;
	int vertex = -1;
	for (auto i = 0; i < base.size(); ++i){
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

	//if (!graph.findPath(vstart, vdest, vertexSet)) return false;
	vertexSet.push_back(2);
	vertexSet.push_back(4);
	vertexSet.push_back(1);
	for (int i = 0; i < vertexSet.size()-1; i++) {
		int curr = vertexSet[i];
		int next = vertexSet[i + 1];
		path.push_back(Segment(base[curr], base[next]));
	}
	vector<Point>points;
	for (auto i : vertexSet) {
		points.push_back(base[i]);
	}
	
	//vehicle.follow(points);
	//vehicle.follow(path);
	return true;
}
