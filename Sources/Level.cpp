#include "Level.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
Level::Level()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Level::drawMap(sf::RenderWindow& window)
{
    std::cout << "Ok fin 70 " << std::endl;
    window.draw(*backgroundLv2);
    std::cout << "Ok fin 75 " << std::endl;
    window.draw(*backgroundLv1);
    window.draw(*foreground);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
QuadTree* Level::createQuadTree()
{
    return foreground->createQuadtree();
}

int Level::getSize()
{
    return foreground->getSize();
}

void Level::setForeground(MapDisplay* _foreground)
{
    foreground = _foreground;
}

void Level::setbackgroundLv1(MapDisplay* _backgroundLv1)
{
    backgroundLv1 = _backgroundLv1;
}

void Level::setbackgroundLv2(MapDisplay* _backgroundLv2)
{
    backgroundLv2 = _backgroundLv2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
std::list<DrawableObject*> Level::getObjects()
{
    return objects;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Level::~Level()
{
    objects.clear();
}
