#include "Segment.h"
Segment::Segment() : head(), tail(){
	length = 0;
	angle = 0;
}
Segment::Segment(const Point& start, const Point& end) : head(start), tail(end) {
	length = dist(start.pos, end.pos);
	angle = asin((end.pos.y - start.pos.y) / length) * 180 / PI;

}

Segment::Segment(const Segment& segment) : head(segment.head), tail(segment.tail){
	*this = segment;
}


const Segment& Segment::operator= (const Segment& segment) {

	if (this == &segment) return *this;
	sprite = segment.sprite;
	marking = segment.marking;
	length = segment.length;
	angle = segment.angle;
	head = segment.head;
	tail = segment.tail;
	return *this;
}
bool Segment::operator==(const Segment& segment) const {
	if ((head == segment.head) && (tail == segment.tail)) return true;
	return false;
}

void Segment::setTail(const Point& end)  {
	tail = { end };
}
sf::Vector2f* Segment::intersect(const Segment& seg) {

	float slope1, slope2;
	float intercept1, intercept2;
	//intersection point
	calcEquation(head.pos, tail.pos, slope1, intercept1);
	calcEquation(seg.head.pos, seg.tail.pos, slope2, intercept2);
	float interX = (intercept2 - intercept1) / (slope1 - slope2);
	float interY = interX * slope1 + intercept1;
	sf::Vector2f inter(interX, interY);
	if (!within(interX, head.pos.x, tail.pos.x)) return nullptr;
	if (!within(interX, seg.head.pos.x, seg.tail.pos.x)) return nullptr;
	return &inter;
}

/*----------- DRAWiNG ---------*/

void Segment::setSprite() {
	sf::Color ROAD_COLOR(128, 128, 128);
	sprite.setSize(sf::Vector2f(length, LANE));
	sprite.setFillColor(ROAD_COLOR);

}
void Segment::drawLaneMarking(LanePos side) {
	for (int i = 0; i < length; i += DASH_LENGTH * 2) {
		sf::Vector2f pos((float)i, (float)1 * LANE);
		marking.addSprite(pos, DASH_LENGTH);
	}
}
void Segment::drawEdgeMarking(LanePos side) {
	marking.addSprite(sf::Vector2f(0, side * LANE), length);
}


/*SPAWNING*/
SegmentSpawner::SegmentSpawner(const Segment& base) : Segment(base.head, base.tail) {
	laneOffset = 0;
	float x_offset = (float)sin(abs(base.angle) * PI / 180) * LANE;
	float y_offset = (float)cos(abs(base.angle) * PI / 180) * LANE;
	offset = { x_offset, y_offset };
}
const Segment SegmentSpawner::get(float idx) const {
	return Segment(getHead(idx), getTail(idx));
}
const Point SegmentSpawner::getTail(float idx) const {
	return Point(tail.pos + offset * idx);
}
const Point SegmentSpawner::getHead(float idx) const {
	return Point(head.pos + (offset * idx));
}
void SegmentSpawner::setOffset(float idx) {
	laneOffset = idx;
}

void Marking::addSprite(sf::Vector2f pos, float length) {
	sf::RectangleShape sprite;
	sprite.setSize(sf::Vector2f(length, LINE_WIDTH));
	sprite.setPosition(pos);
	sprite.setFillColor(sf::Color::White);
	spriteArray.push_back(sprite);
}