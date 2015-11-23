#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <iostream>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Reader.h"
#include "DrawableObject.h"
#include "Map.hpp"
#include "MapDisplay.hpp"
#include "QuadTree.hpp"

class QuadTree;

class Level
{
public:
    Level();
    std::list<DrawableObject*> getObjects();
    void drawMap(sf::RenderWindow& window);
    int getSize();
    void setForeground(MapDisplay* _foreground);
    void setbackgroundLv1(MapDisplay* _backgroundLv1);
    void setbackgroundLv2(MapDisplay* _backgroundLv2);
    MapDisplay* getForeground() {return foreground;}
    MapDisplay* getBackgroundLv1() {return backgroundLv1;}
    MapDisplay* getBackgroundLv2() {return backgroundLv2;}
    QuadTree* createQuadTree();
    ~Level();

private:
    std::string path;
    std::string levelName;
    std::list<DrawableObject*> objects;
    MapDisplay* foreground;
    MapDisplay* backgroundLv1;
    MapDisplay* backgroundLv2;
};

#endif // LEVEL_HPP
