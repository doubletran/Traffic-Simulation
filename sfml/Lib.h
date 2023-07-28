#pragma once

#include <iostream>
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>

#define WIDTH 1000
#define HEIGHT 1000
#define PI 3.141592653
#define LANE 40
#define LINE_WIDTH 5
#define DASH_LENGTH 10

using namespace std;

float dist(const sf::Vector2f& v1, const sf::Vector2f& v2);
float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
void calcEquation(const sf::Vector2f& v1, const sf::Vector2f& v2, float &slope, float &intercept);
float lineSlope(const sf::Vector2f& v1, const sf::Vector2f& v2);
void limit(sf::Vector2f& vector, float max = 1);

struct Point {
	sf::Vector2f pos;
	Point() {};
	Point(const sf::Vector2f & init) {
		pos = init;
	}

	Point(int x_, int y_) {
		pos.x = (float)x_;
		pos.y = (float)y_;

	}
	bool operator==(const Point& pt) const {
		return (pos == pt.pos);
	}
};
//enum dir{ LEFT = 0, RIGHT };
enum LanePos {LEFT, RIGHT, MIDDLE};
bool within(float x, float a, float b);

sf::Vector2f getNormalPoint(const sf::Vector2f& pt, const sf::Vector2f& start, const sf::Vector2f& end);