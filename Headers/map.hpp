#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include "Reader.h"
#include "mapDisplay.hpp"
#include "Level.hpp"

#define largeurTile 32
#define hauteurTile 32

using namespace std;

class Level;

class Map : public sf::Drawable, public sf::Transformable, public Reader
{
public:
    Map(int largeur,int hauteur,string fichier, Level* lvl);
    bool load();
    void save();
    void charger(Level* lvl);
    void setTile(int nb);
    void setTileReel(int nb);
    void setTileArray(int *tab);
    void update(sf::RenderWindow &window,int valSprite, sf::Vector2u mouseMove, string ground, Level* lvl);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &_tileset;
        target.draw(_vertices, states);
    }
    void draw(sf::RenderWindow *window)
    {
        window->draw(_vertices);
    }
    ~Map();
    MapDisplay* createMap();
    MapDisplay* reloadMap();
    MapDisplay* createBackground(std::string lvl);
    MapDisplay* reloadBackground(std::string lvl);
    MapDisplay* getForeground() {return _foreground;}
    MapDisplay* getBackgroundLv1() {return _backgroundLv1;}
    MapDisplay* getBackgroundLv2() {return _backgroundLv2;}
private:
    void read();
    int _nbTile;
    int _nbTileReel;
    int *_tileArray;
    int _largeurMap;
    int _hauteurMap;
    string _filePath;
    string _filePathTileset;
    sf::Vector2i _mapSize;
    int *_mapArray;
    std::vector <int> _tabMap;
    std::vector <int> _tabForeground;
    std::vector <int> _tabBackgroundLv1;
    std::vector <int> _tabBackgroundLv2;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    MapDisplay* _foreground;
    MapDisplay* _backgroundLv1;
    MapDisplay* _backgroundLv2;

};

#endif // MAP_HPP_INCLUDED
