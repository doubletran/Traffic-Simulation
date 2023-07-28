#pragma once
#include "../Lib.h"
struct Marking :public sf::Drawable, sf::Transformable {
	vector<sf::RectangleShape> spriteArray;


	void addSprite(sf::Vector2f pos, float length);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		for (auto line : spriteArray) {
			target.draw(line, states);
		}
	}
};
struct Segment: public sf::Drawable, sf::Transformable {
	

	float length;
	float angle;
	Point head;
	Point tail;
	Marking marking;
	sf::Vector2f origin;
	sf::RectangleShape sprite;
	
	/*Constructor*/
	Segment();
	Segment(const Point& start, const Point& end);
	Segment(const Segment& segment);

	const Segment& operator= (const Segment& segment);

	/*Method*/
	bool operator==(const Segment& segment) const;
	sf::Vector2f* intersect(const Segment& seg);
	void setTail(const Point& end);

	/*Method for drawing*/
	void setSprite();
	void drawLaneMarking(LanePos pos = RIGHT);
	void drawEdgeMarking(LanePos pos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(sprite, states);
	}

};

struct SegmentSpawner : public::Segment {
	sf::Vector2f offset;
	float laneOffset;

	SegmentSpawner(const Segment& base);

	void setOffset(float idx);
	const Segment get(float idx ) const;
	const Point getTail(float idx ) const;
	const Point getHead(float idx ) const;

};

bool contain(const  sf::Vector2f& pt);