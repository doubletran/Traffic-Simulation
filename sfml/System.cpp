#include "System.h"

System::System()
    :window(sf::VideoMode(WIDTH, HEIGHT), "BROOKWOOD")
    , traffic()
{
    Point pt1(0, HEIGHT / 2);
    Point pt2(WIDTH / 2, HEIGHT);

    Point pt3(WIDTH, 10);
    Point pt4(WIDTH, HEIGHT / 2);

    Street str1(pt2, pt3, "TEN");
    Auto car(pt1.pos);
    vehicles.emplace_back( car);
    str1.addLane();
     Street str2(pt1, pt4, "MAXWELL");
  // traffic.addStreet(Highway)
     str2.addLane();
     traffic.addStreet(str1);
    traffic.addStreet(str2);
   
}



void System::addStreet(const Street& newStreet) {



}
void System::drawPath() {

}
void System::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}
void System::render() {
	window.clear(sf::Color::White);
   window.draw(traffic);  
    for (auto  &vehicle : vehicles) {
       // cout << vehicle.pos.y << " " << vehicle.pos.y << endl;
        window.draw(vehicle);
    }

	window.display();
}
void System::update() {
	//car.seek(sf::Vector2f(0, 0));
    
    for (auto& vehicle : vehicles) {
        traffic.guide(vehicle, sf::Vector2f(WIDTH / 2, 15));
        //vehicle.follow(traffic.streetArray[0].segArray[0]);
        vehicle.update();
    }
    
}
void System::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}


int main()
{

   
    /*
    vector<Point> pts;

    for (int x = 0; x < WIDTH; x += WIDTH / SPACE)
        {
        for (int y = 0; y < HEIGHT; y += HEIGHT / SPACE) {
            pts.push_back(Point(x, y));
         }
    }
    for (auto pt : pts) {
        graph.add(pt);
    }

    Point pt1(1, 1);
    Point pt2(2, 2);
    Point pt3(3, 3);
    graph.add(pt1);
    graph.add(pt2);
    graph.add(pt3);
    graph.connect(pt1, pt2, 2);
    graph.connect(pt2, pt3, 3);
    graph.connect(pt1, pt3, 6);
    vector<Point> shortPath;
    graph.findPath(pt1, pt3, shortPath);
    */
    System Brookwood;

    Brookwood.run();


    return 0;
}