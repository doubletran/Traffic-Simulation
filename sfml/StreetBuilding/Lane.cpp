#include "Lane.h"
Lane::Lane() : Segment() {};
Lane::Lane(const Point& start, const Point& end) : Segment(start, end) {
	segArray.emplace_back(*this);
}

Lane::Lane(const Lane& lane) : Segment(lane) {
	*this = lane;
}

const Lane& Lane::operator= (const Lane& lane) {
	if (this == &lane) return *this;
	segArray = lane.segArray;
	update();
	return *this;
}


void Lane::add(const Point& pt) {
	segArray.push_back({ tail, pt });
	update();
}

void Lane::update() {
	this->head = segArray.front().head;
	this->tail = segArray.back().tail;
}

/*Spawning*/
const Lane LaneSpawner::get() const {
	return Lane(*this);
}
void Lane::setSprite(LanePos pos) {
	for (auto &seg : segArray) {;
		switch (pos) {
		case RIGHT:
			seg.drawEdgeMarking(pos);
			break;
		case LEFT:
			seg.drawEdgeMarking(pos);
		default:
			seg.drawLaneMarking();
		}
		
	}
}