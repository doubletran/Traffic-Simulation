#include "Street.h"


Street::Street(const Point& start, const Point& end, const char* name): Lane(start, end) {

	lane++;
	laneArray.emplace_back(*this);
	setName(name);
	update();
}
Street::Street(const Street& street): Lane(street) {
	//laneArray.push_back(*this);
	*this = street;
}

const Street& Street::operator= (const Street& street) {
	if (this == &street) return *this;

	laneArray = street.laneArray;
	update();
	return *this;

}

void Street::add(const Point& pt) {
	//add all spawned segmnet to the end of each lane
	add(pt);
	SegmentSpawner spawner(segArray.back());
	for (int i = 0; i < lane; ++i) {
		laneArray[i].add(spawner.getTail(i));
	}
}
void Street::add(const Point& pt, int laneIdx) {
	SegmentSpawner spawner(laneArray[laneIdx].segArray.back());
	laneArray[laneIdx].add(pt);
}
void Street::addLane() {
	LaneSpawner newLane(laneArray[0], lane);
	laneArray.push_back(newLane.get());
	lane++;

}

void Street::setName(const char* name) {
	if (!name) return;
	if (this->name) {
		delete this->name;
		this->name = NULL;
	}
	this->name = new char[strlen(name)];
	//strcpy(this->name, name);

}


int Street::getLaneIdx(LanePos lane_pos) {
	if (lane_pos == LEFT) { return 0; }
	if (lane_pos == RIGHT) { return lane - 1; }
	return (1);
}
LanePos Street::getLanePos(int lane_idx) {
	if (lane_idx == 0) { return LEFT; }
	else if (lane_idx == lane - 1) { return RIGHT; }
	return MIDDLE;
}