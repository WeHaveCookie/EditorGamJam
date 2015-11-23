#ifndef EDIT_HPP_INCLUDED
#define EDIT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;

class Edit : public sf::Drawable, public sf::Transformable
{

public:
    Edit(string name);
    void update(sf::RenderWindow &window,sf::Vector2u mouseMove);
    int getTile();
    int getNombreTileReel();
    int* getArray();
    sf::Sprite* getSprite();
    sf::Texture* getTexture();
    sf::Vector2u getSize();
    sf::Vector2f getPositionShape();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(_sprite,states);
        target.draw(_shape,states);
        for (int i(0);i<_nbTile*3;i+=3)
        {
            target.draw(_bloquantArray[i+_tileArray[i/3]]);
        }
    }
    ~Edit(){}
private:
    int _nbTile;
    int *_tileArray;
    sf::Texture _textureBloquant;
    sf::Sprite *_bloquantArray;
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Sprite *_spriteSelec;
    sf::RectangleShape _shape;
    int ready;
    bool isReady;

};

#endif // EDIT_HPP_INCLUDED
