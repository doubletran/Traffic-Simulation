#include "Lib.h"
float dist(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}
float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
void limit(sf::Vector2f& vector, float max) {
	float ratio = vector.x / vector.y;
	float y = sqrt(pow(max, 2) / (pow(ratio, 2) + 1));
	y = (vector.y > 0) ? y : -y;
	float x = (vector.y!= 0) ?  ratio * y : max;
	vector = sf::Vector2f(x, y);

}
float lineSlope(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return (v2.y - v1.y) / (v2.x - v1.x);
}
void calcEquation(const sf::Vector2f& v1, const sf::Vector2f& v2, float& slope, float& intercept) {
	slope = lineSlope(v1, v2);
	intercept = v1.y - (slope * v1.x);
}
sf::Vector2f getNormalPoint(const sf::Vector2f& pt, const sf::Vector2f& start, const sf::Vector2f& end) {

	/*get normal point*/
	sf::Vector2f hyp = pt - start;
	sf::Vector2f adj = end - start;
	limit(adj);
	//dot a . b = |a| |b| cos (theta)
	//|a| cos (theta) = normal Point
	adj *= dot(hyp, adj);
	return adj + start;

}
bool within(float x, float a, float b) {
	float* low, * high;

	if (a < b) {
		low = &a;
		high = &b;
	}
	else {
		low = &b;
		high = &a;
	}
	if ((x < *low) || (x > *high)) return false;
	return true;
	

}