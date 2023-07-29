#include "Route.h"
Route::Route() {};
Route::Route(const Street& str, int seg_idx) {
	street = new Street(str);
	segment = street->segArray[seg_idx];
	this->seg_idx = seg_idx;
}
Route::Route(const Route& route) {

	street = new Street(*route.street);
	segment = route.segment;
	seg_idx = route.seg_idx;
	lane_pos = route.lane_pos;
	lane_idx = route.lane_idx;

}

Point Route::getTail(const int idx) const {
	return street->laneArray[idx].segArray[seg_idx].tail;
}
Point Route::getHead(const int idx) const {
	return street->laneArray[idx].segArray[seg_idx].head;
}
Segment Route::getSegment(const int lane_idx) const {
	return street->laneArray[lane_idx].segArray[seg_idx];
}
Segment Route::getSegment() const {
	return street->laneArray[this->lane_idx].segArray[seg_idx];
}

LanePos Route::getNearestLane(const Route& next) const {
	Point target = next.getHead(0);
	return getNearestLane(target.pos);

}
LanePos Route::getNearestLane(const sf::Vector2f targetPos) const {
	Point leftTail = getTail(0);
	Point rightTail = getTail(street->lane);
	float left_dist = dist(leftTail.pos, targetPos);
	float right_dist = dist(rightTail.pos, targetPos);
	if (left_dist < right_dist) {
		return LEFT;
	}
	else {
		return RIGHT;
	}

}
void Route::setLane(const int lane) {
	this->lane_idx = lane;
	lane_pos = street->getLanePos(lane);


}
void Route::setLane(const sf::Vector2f pos) {
	lane_pos = getNearestLane(pos);
	this->lane_idx = street->getLanePos(lane_pos);
}
bool Route::endRoute(const sf::Vector2f pos) {
	if (dist(getTail(lane_idx).pos, pos) < 10) {
		return true;
	}
	return false;
}
bool Route::divide(const Point& cutoff, vector<Route>& pieces) {

	Route division{ *street, seg_idx };
	division.segment = Segment(segment.head, cutoff);
	pieces.push_back(division);
	division.segment = Segment(cutoff, segment.tail);
	pieces.push_back(division);
	return true;

}
bool Route::divide(vector<Point> pts, vector<Route>& pieces) {
	Point head = segment.head;
	Route division { *street, seg_idx };

	for (auto pt : pts) {
	
		division.segment = Segment(head, pt);
		pieces.push_back(division);
		head = pt;
	}
	division.segment = Segment(head, segment.tail);
	pieces.push_back(division);
	return true;
	

}