#include "edit.hpp"

Edit::Edit(string name)
{
    string chemin = "Tileset/"+name;
    _texture.loadFromFile(chemin.c_str());
    _sprite.setTexture(_texture);
    _sprite.setPosition(0,0);

    _shape.setSize(sf::Vector2f(32,32));
    _shape.setFillColor(sf::Color(0,0,0,0));
    _shape.setOutlineThickness(1);
    _shape.setOutlineColor(sf::Color(255,255,255));
    _shape.setPosition(0,0);

    _spriteSelec = new sf::Sprite(_texture);
    _spriteSelec->setTextureRect(sf::IntRect(_shape.getPosition().x,_shape.getPosition().y,32,32));
    _spriteSelec->setPosition(80,150);

    _nbTile = (_texture.getSize().x/32) *(_texture.getSize().y/32);
    _tileArray = new int[_nbTile];
    for(int i(0);i<_nbTile;i++)
    {
        _tileArray[i] = 0;
    }
    _textureBloquant.loadFromFile("Util/bloquant.png");
    _bloquantArray = new sf::Sprite[_nbTile*3];
    //0 => rond
    //1 => croix
    //2 => rectangle
    for (int i(0);i<_nbTile*3;i+=3)
    {
        _bloquantArray[i].setTexture(_textureBloquant);
        _bloquantArray[i].setTextureRect(sf::IntRect(32,0,32,32));
        _bloquantArray[i].setPosition(i/3%(_texture.getSize().x/32)*32,i/3/(_texture.getSize().x/32)*32);
        _bloquantArray[i+1].setTexture(_textureBloquant);
        _bloquantArray[i+1].setTextureRect(sf::IntRect(0,0,32,32));
        _bloquantArray[i+1].setPosition(i/3%(_texture.getSize().x/32)*32,i/3/(_texture.getSize().x/32)*32);
        _bloquantArray[i+2].setTexture(_textureBloquant);
        _bloquantArray[i+2].setTextureRect(sf::IntRect(64,0,32,32));
        _bloquantArray[i+2].setPosition(i/3%(_texture.getSize().x/32)*32,i/3/(_texture.getSize().x/32)*32);
    }

    ready = 0;
    isReady = true;

}

void Edit::update(sf::RenderWindow &window, sf::Vector2u mouseMove)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        //Récupération du numero du tile avec la souris
        //x = position.x/32
        //y = position.y/32
        if (position.x+mouseMove.x >= 0 && position.y+mouseMove.y >= 0 )
        {
            _shape.setPosition(((position.x+mouseMove.x)/32)*32,((position.y+mouseMove.y)/32)*32);
            //Sélection du tile sur le tileset
            _spriteSelec->setTextureRect(sf::IntRect(_shape.getPosition().x,_shape.getPosition().y,32,32));
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)&& isReady)
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        //Récupération du numero du tile avec la souris
        //x = position.x/32
        //y = position.y/32
        if (position.x+mouseMove.x >= 0 && position.y+mouseMove.y >= 0 && position.y+mouseMove.y <= _texture.getSize().y && position.x+mouseMove.x <= _texture.getSize().x)
        {
            _tileArray[(position.x+mouseMove.x)/32 + (position.y+mouseMove.y)/32 * _texture.getSize().x/32]++;
            if(_tileArray[(position.x+mouseMove.x)/32 + (position.y+mouseMove.y)/32 * _texture.getSize().x/32] == 3)
                _tileArray[(position.x+mouseMove.x)/32 + (position.y+mouseMove.y)/32 * _texture.getSize().x/32] = 0;
        }
        isReady = false;
    }
    if (!isReady)
    {
        ready++;
        if(ready >= 10)
        {
            ready = 0;
            isReady = true;
        }
    }

}

int* Edit::getArray()
{
    return _tileArray;
}

int Edit::getNombreTileReel()
{
    int a(0);
    for (int i(0);i<_nbTile;i++)
    {
        if(_tileArray[i]==2)
            a++;
    }
    return _nbTile-a;
}

int Edit::getTile()
{
    return _nbTile;
}

sf::Sprite* Edit::getSprite()
{
    return _spriteSelec;
}

sf::Texture* Edit::getTexture()
{
    return &_texture;
}

sf::Vector2u Edit::getSize()
{
    return _texture.getSize();
}

sf::Vector2f Edit::getPositionShape()
{
    return _shape.getPosition();
}
