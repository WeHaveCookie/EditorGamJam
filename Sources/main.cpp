#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "edit.hpp"
#include "map.hpp"
#include "Level.hpp"
#include "MapDisplay.hpp"

#define MAX_LARGEUR_FENETRE 1400
#define MAX_HAUTEUR_FENETRE 900
#define MAX_LARGEUR_FENETRE2 192
#define MAX_HAUTEUR_FENETRE2 900
#define MAX_LARGEUR_FENETRE3 1200
#define MAX_HAUTEUR_FENETRE3 900

#define largeurMap 500//En nombre de tile
#define hauteurMap 30//En nombre de tile

string const tilesetName = "tileset.png"; // Nom du tileset a placer dans Tileset

//Création et positionnement des fenêtres
sf::RenderWindow window(sf::VideoMode(MAX_LARGEUR_FENETRE,MAX_HAUTEUR_FENETRE), "Map Editor V1.0");
sf::RenderWindow *window2;
sf::RenderWindow window3(sf::VideoMode(MAX_LARGEUR_FENETRE2,300), "Map Editor V1.2");

int main(int argc, char** argv)
{
    //window.setPosition(sf::Vector2i(240, 50));
    window.setFramerateLimit(30);
    window3.setFramerateLimit(30);
    sf::View view;
    sf::View view2;
    sf::FloatRect viewRect(0,0,MAX_LARGEUR_FENETRE,MAX_HAUTEUR_FENETRE);
    sf::FloatRect viewRect2(0,0,MAX_LARGEUR_FENETRE3,MAX_HAUTEUR_FENETRE3);
    view.reset(viewRect);
    view2.reset(viewRect2);
    window.setView(view);
    Level* lvl;
    lvl = new Level;
    //QuadTree* tree;
    //tree = lvl->createQuadTree();

    sf::Vector2u mouseMove(0,0);
    sf::Vector2u mouseMove2(0,0);

    float speedWin1(10.0);
    float speedWin2(10.0);


    bool targetWin2 = false;
    bool targetWin1 = true;
    string ground = "f";

    //Gestion du module éditeur
    Edit editeur(tilesetName);
    sf::Texture texture;//texture pour la fenetre de droite
    texture.loadFromFile("Util/tile.png");
    sf::Sprite sprite(texture);
    window2 = new sf::RenderWindow(sf::VideoMode(/*editeur.getSize().x,editeur.getSize().y*/MAX_LARGEUR_FENETRE3,MAX_HAUTEUR_FENETRE3), "Map Editor V1.1");
    window2->setView(view2);
    window3.setPosition(sf::Vector2i(window2->getPosition().x,window2->getPosition().y+editeur.getSize().y + 40));

    //Gestion du module map
    int currSprite(0);
    Map village(largeurMap,hauteurMap,tilesetName,lvl);
    village.setTile(editeur.getTile());

    //Gestion des instructions
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("S : Sauvegarder la map");
    text.setCharacterSize(18);
    text.setColor(sf::Color::Red);
    text.setPosition(0,200);
    sf::Text text1;
    text1.setFont(font);
    text1.setString("L : Charger la map");
    text1.setCharacterSize(18);
    text1.setColor(sf::Color::Red);
    text1.setPosition(0,218);

    while (window.isOpen() && window2->isOpen()&& window3.isOpen())
    {
        currSprite = (editeur.getPositionShape().x + editeur.getPositionShape().y * (editeur.getSize().x/32))/32;

        sf::Event event;
        sf::Event event2;
        sf::Event event3;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                village.save();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                village.charger(lvl);
            if (event.type == sf::Event::LostFocus)
                targetWin1 = false;
            if (event.type == sf::Event::GainedFocus)
                targetWin1 = true;
            if (targetWin1 && !targetWin2)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    view.move(-speedWin1,0.0);
                    viewRect.left = viewRect.left-speedWin1;
                    mouseMove.x -= speedWin1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    view.move(speedWin1,0.0);
                    viewRect.left = viewRect.left+speedWin1;
                    mouseMove.x += speedWin1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    view.move(0.0,-speedWin1);
                    viewRect.top = viewRect.top-speedWin1;
                    mouseMove.y -=speedWin1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    view.move(0.0,speedWin1);
                    viewRect.top = viewRect.top+speedWin1;
                    mouseMove.y += speedWin1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                    {view.zoom(0.9f);}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    {view.zoom(1.1f);}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    {speedWin1 += 5;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                    {speedWin1 -= 5;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    ground = "f";
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    ground = "b1";
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    ground = "b2";
                }
            }
        }
        while (window2->pollEvent(event2))
        {
            if (event2.type == sf::Event::Closed)
                window2->close();
            if (event2.type == sf::Event::LostFocus)
                targetWin2 = false;
            if (event2.type == sf::Event::GainedFocus)
                targetWin2 = true;
            if (targetWin2)
            {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    view2.move(-speedWin2,0.0);
                    viewRect2.left = viewRect2.left-speedWin2;
                    mouseMove2.x -= speedWin2;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    view2.move(speedWin2,0.0);
                    viewRect2.left = viewRect2.left+speedWin2;
                    mouseMove2.x += speedWin2;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    view2.move(0.0,-speedWin2);
                    viewRect2.top = viewRect2.top-speedWin2;
                    mouseMove2.y -=speedWin2;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    view2.move(0.0,speedWin2);
                    viewRect2.top = viewRect2.top+speedWin2;
                    mouseMove2.y += speedWin2;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                    {view2.zoom(0.9f);}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    {view2.zoom(1.1f);}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    {speedWin2 += 5;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                    {speedWin2 -= 5;}
            }
        }
        while (window3.pollEvent(event3))
        {
            if (event3.type == sf::Event::Closed)
                window3.close();
        }


        view2.reset(viewRect2);
        window2->setView(view2);
        window2->clear();
        window2->draw(editeur);
        if (targetWin2)
        {
            editeur.update(*window2,mouseMove2);
        }
        window2->display();

        //view.reset(viewRect);
        window.setView(view);
        window.clear();
        //window.draw(*(village.getBackgroundLv2()));
        //window.draw(*(village.getBackgroundLv1()));
        window.draw(*(lvl->getBackgroundLv2()));
        window.draw(*(lvl->getBackgroundLv1()));
        window.draw(*(lvl->getForeground()));


        /*lvl->getBackgroundLv2()->draw(&window);
        lvl->getBackgroundLv1()->draw(&window);
        lvl->getForeground()->draw(&window);*/
        //window.draw(village);

        window.display();
        //window.draw(village);
        if (targetWin1)
        {
            village.update(window,currSprite,mouseMove,ground,lvl);
        }


        window3.clear();
        window3.draw(sprite);
        window3.draw(*editeur.getSprite());
        window3.draw(text);
        window3.draw(text1);
        window3.display();

        village.setTileReel(editeur.getNombreTileReel());
        village.setTileArray(editeur.getArray());
    }

    return EXIT_SUCCESS;
}
