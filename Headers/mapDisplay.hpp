#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <iostream>
#include <Vector>
#include <List>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "QuadTree.hpp"



class MapDisplay : public sf::Drawable, public sf::Transformable
{
public:
    MapDisplay(const std::string & filePath, std::vector <int> tabMap, sf::Vector2i mapSize, sf::Vector2u spriteSize, sf::Vector2f initPosChar);
    MapDisplay(const std::string & filePath, std::vector <int> tabMap, sf::Vector2i mapSize, sf::Vector2u spriteSize);
    MapDisplay();
    ~MapDisplay();

    void createMap();
    int getSize();
    QuadTree* createQuadtree();
    bool loadVertice();
    void reload(std::vector <int> _tabMap, sf::Vector2i mapSize);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

    void draw(sf::RenderWindow* window) { loadVertice();window->draw(m_vertices);}

protected:
private:
    sf::Texture m_tileset;
    std::string m_filePath;
    std::vector <int> m_tabMap;
    sf::Vector2f m_initPosChar;
    sf::Vector2i m_mapSize;
    sf::Vector2u m_spriteSize;
    sf::VertexArray m_vertices;
};

#endif // MAP_H_INCLUDED
