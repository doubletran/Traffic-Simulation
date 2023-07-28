#pragma once
#include <SFML/Graphics.hpp>
#include "StreetBuilding/Street.h"
#include "Auto.h"
#include "Traffic.h"

class System {
    Traffic traffic;
    vector<Auto> vehicles;
    
public:

    System();
    void run();
private:
    void processEvents();
    void update();
    void render();
public:
    void addStreet(const Street& newStreet);
    sf::RenderWindow window;
    
    
    void drawPath();
};
