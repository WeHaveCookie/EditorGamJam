#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
//#include <list.h>
#include <list>
#include <vector>
#include <iostream>
#include <string.h>
#include <time.h>
#include "constantes.hpp"


using namespace std;
class QuadTree
{

    public:

    QuadTree(float x, float y, float width, float height, int level, int maxLevel);

    ~QuadTree();

    void	AddObject(sf::Sprite *object);
    list<sf::Sprite*>	GetObjectsAt(float x, float y);
    list<sf::Sprite*>	GetObjects(float x, float y);
    void	Clear();
    void    AfficherTree();
    void	Draw(sf::RenderWindow* window);
    void    SetColor(sf::Color couleur);
    void    Disable();

    private:

    bool enable;
    float	x;
    float	y;
    float	width;
    float	height;
    int	level;
    int	maxLevel;
    list<sf::Sprite*>	objects;
    sf::Color color;

    QuadTree *	parent;
    QuadTree *	NW;
    QuadTree *	NE;
    QuadTree *	SW;
    QuadTree *	SE;

    sf::RectangleShape	shape;

    bool	contains(QuadTree *child, sf::Sprite *object);

};

#endif
