#include "map.hpp"

Map::Map(int largeur, int hauteur, string fichier, Level* lvl)
: Reader(), _foreground(), _backgroundLv1(), _backgroundLv2()
{
    string chemin = "Tileset/"+fichier;
    _filePathTileset = "Tileset/"+fichier;
    _tileset.loadFromFile(chemin.c_str());
    _largeurMap = largeur;
    _hauteurMap = hauteur;
    _mapSize = sf::Vector2i(_largeurMap*32,_hauteurMap*32);
    _filePath = fichier;
    _mapArray = new int [_largeurMap*_hauteurMap];
    for (int i(0);i<_largeurMap*_hauteurMap;i++)
    {
        _mapArray[i] = 121;
        _tabMap.push_back(1024);
        _tabForeground.push_back(1024);
        _tabBackgroundLv1.push_back(1024);
        _tabBackgroundLv2.push_back(1024);
    }
    lvl->setForeground(createMap());
    lvl->setbackgroundLv1(createBackground("Lv1"));
    lvl->setbackgroundLv2(createBackground("Lv2"));
    //load();
}

bool Map::load()
{

}

void Map::update(sf::RenderWindow &window,int valSprite, sf::Vector2u mouseMove, string ground, Level* lvl)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        //Récupération du numero du tile avec la souris
        //x = position.x/32
        //y = position.y/32
        if ((position.x+mouseMove.x) >= 0 && (position.y+mouseMove.y) >= 0 && position.x+mouseMove.x <= _largeurMap*32 && position.y+mouseMove.y <= _hauteurMap*32)
        {
            //_mapArray[(position.x+mouseMove.x)/32+((position.y+mouseMove.y)/32)*_largeurMap] = valSprite;
            if (ground == "f")
            {
                std::cout << "Fore modifie" << std::endl;
                _tabForeground[(position.x+mouseMove.x)/32+((position.y+mouseMove.y)/32)*_largeurMap] = valSprite+1;
                lvl->setForeground(reloadMap());
            }
            else if (ground =="b1")
            {
                std::cout << "b1 modifie" << std::endl;
                _tabBackgroundLv1[(position.x+mouseMove.x)/32+((position.y+mouseMove.y)/32)*_largeurMap] = valSprite+1;
                lvl->setbackgroundLv1(reloadBackground("Lv1"));
            }
            else if (ground == "b2")
            {
                std::cout << "b2 modifie" << std::endl;
                _tabBackgroundLv2[(position.x+mouseMove.x)/32+((position.y+mouseMove.y)/32)*_largeurMap] = valSprite+1;
                lvl->setbackgroundLv2(reloadBackground("Lv2"));
            }



            /*_tabMap[(position.x+mouseMove.x)/32+((position.y+mouseMove.y)/32)*_largeurMap] = valSprite;
            sf::Vertex* quad = &_vertices[((position.x+mouseMove.x)/32 + (position.y+mouseMove.y)/32 * _largeurMap) * 4];
            int tu = valSprite % (_tileset.getSize().x / largeurTile);
            int tv = valSprite / (_tileset.getSize().x / largeurTile);
            // on d�finit ses quatre coordonn�es de texture
            quad[0].texCoords = sf::Vector2f(tu * largeurTile, tv * hauteurTile);
            quad[1].texCoords = sf::Vector2f((tu + 1) * largeurTile, tv * hauteurTile);
            quad[2].texCoords = sf::Vector2f((tu + 1) * largeurTile, (tv + 1) * hauteurTile);
            quad[3].texCoords = sf::Vector2f(tu * largeurTile, (tv + 1) * hauteurTile);*/
        }
    }
    //load();
}

void Map::save()
{
    string creator,mapName,pathSprite;
    int initPosCharX, initPosCharY;
    cout << "Choix du nom de map : ";
    getline(cin,mapName);
    string chemin = "Save/"+mapName;
    cout << endl << "Enregistrement en cours ..." << endl;
    ofstream fichier(chemin.c_str(), ios::out);// On ouvre le fichier en écriture
    cout << "Creator : ";
    getline(cin,creator);
    fichier << "CreateBy : ";
    fichier << creator+"\n";
    fichier << "MapName : " << mapName << "\n";
    fichier << "SizeMap : " << _largeurMap*32 << " " << _hauteurMap*32 << "\n";
    fichier << "InitPosChar : 0 0\n";
    fichier << "PathSprite : " << _filePath+"\n";
    fichier << "Map : ";
    for (int i(0);i<_tabForeground.size();i++)
    {
        if (i%(_largeurMap)==0)
        {
            fichier << "\n";
        }
        if (_tabForeground[i] == 1024)
        {
            fichier << "0" << "\t\t";
        }
        else
        {
            fichier << _tabForeground[i] << "\t\t";
        }
    }
    fichier << "\n\n" <<"BackgroundLv1 : ";
    for (int i(0);i<_tabBackgroundLv1.size();i++)
    {
        if (i%(_largeurMap)==0)
        {
            fichier << "\n";
        }
        if (_tabBackgroundLv1[i] == 1024)
        {
            fichier << "0" << "\t\t";
        }
        else
        {
            fichier << _tabBackgroundLv1[i] << "\t\t";
        }
    }
    fichier <<"\n\n" << "BackgroundLv2 : ";
    for (int i(0);i<_tabBackgroundLv2.size();i++)
    {
        if (i%(_largeurMap)==0)
        {
            fichier << "\n";
        }
        if (_tabBackgroundLv2[i] == 1024)
        {
            fichier << "0" << "\t\t";
        }
        else
        {
            fichier << _tabBackgroundLv2[i] << "\t\t";
        }
    }

    fichier.close();
    cout << "Enregistrement termine." << endl;
}

void Map::read()
{
    _tabForeground.clear();
    _tabBackgroundLv1.clear();
    _tabBackgroundLv2.clear();
    while (m_curChar != EOF)
    {
        m_curWord = nextWord();
        if (m_curWord == "CreateBy")
        {
            skipSeparator();
            std::cout << "CreateBy ok" << std::endl;
        }
        else if (m_curWord == "MapName")
        {
            skipSeparator();
            std::cout << "MapName ok" << std::endl;
        }
        else if (m_curWord == "SizeMap")
        {
            skipSeparator();
            std::istringstream x(nextWord());
            x >> _mapSize.x;
            _largeurMap = _mapSize.x/32;
            std::istringstream y(nextWord());
            y >> _mapSize.y;
            _hauteurMap = _mapSize.y/32;
            std::cout << "SizeMap ok" << std::endl;
        }
        else if (m_curWord == "InitPosChar")
        {
            skipSeparator();
            std::cout << "Init ok" << std::endl;
        }
        else if (m_curWord == "PathSprite")
        {
            skipSeparator();
            _filePathTileset = "Tileset/"+nextWord();
            _tileset.loadFromFile(_filePathTileset);
            std::cout << "PathSprite ok" << std::endl;
        }
        else if (m_curWord == "Map")
        {
            skipSeparator();
            //unsigned int i = 0;
            m_curWord = nextWord();
            while (m_curWord != "BackgroundLv1" )
            {

                unsigned int numSprite;
                std::istringstream re(m_curWord);
                re >> numSprite;
                if (m_curWord == "0")
                {
                    numSprite = 1024;
                }
                _tabForeground.push_back(numSprite);
                skipSeparator();
                m_curWord = nextWord();
                //i += 1;
            }
            std::cout<<"Fore Load\n";
        }
        if (m_curWord == "BackgroundLv1")
        {
            skipSeparator();
            //unsigned int i = 0;
            m_curWord = nextWord();
            while(m_curWord != "BackgroundLv2")
            {
                unsigned int numSprite;
                std::istringstream re(m_curWord);
                re >> numSprite;
                if (m_curWord == "0")
                {
                    numSprite = 1024;
                }
                _tabBackgroundLv1.push_back(numSprite);
                skipSeparator();
                m_curWord = nextWord();
                //i += 1;
            }
            std::cout<<"Back1 Load\n";
        }
        if (m_curWord == "BackgroundLv2")
        {
            skipSeparator();
            //unsigned int i = 0;
            m_curWord = nextWord();
            while(m_curWord != "")
            {
                unsigned int numSprite;
                std::istringstream re(m_curWord);
                re >> numSprite;
                if (m_curWord == "0")
                {
                    numSprite = 1024;
                }
                _tabBackgroundLv2.push_back(numSprite);
                skipSeparator();
                m_curWord = nextWord();
                //i += 1;
            }
            std::cout<<"Back2 Load\n";
        }
    }
}

void Map::charger(Level* lvl)
{

    int nbTileLarg(0),nbTileLong(0),complement(0);
    int currVal(0);
    string nomMap;
    string lecture = "";
    cout << "Choix du nom de la sauvegarde : ";
    getline(cin,nomMap);
    string chemin = "Load/"+nomMap;
    cout << endl << "Ouverture en cours ..." << endl;
    this->open(chemin);
    read();
    lvl->setForeground(reloadMap());
    lvl->setbackgroundLv1(reloadBackground("Lv1"));
    lvl->setbackgroundLv2(reloadBackground("Lv2"));
    cout << "Map chargee" << endl;
}


void Map::setTile(int nb)
{
    _nbTile = nb;
}

void Map::setTileReel(int nb)
{
    _nbTileReel = nb;
}

void Map::setTileArray(int *tab)
{
    _tileArray = tab;
}

Map::~Map()
{

}

MapDisplay* Map::createMap()
{
    _foreground = new MapDisplay(_filePathTileset,_tabForeground,_mapSize,sf::Vector2u(32,32),sf::Vector2f(0.0,0.0));
    _foreground->createMap();
    return _foreground;
}


MapDisplay* Map::reloadMap()
{
    std::cout << "reload" << std::endl;
    _foreground->reload(_tabForeground,_mapSize);
    return _foreground;
}

MapDisplay* Map::createBackground(std::string lvl)
{
    if (lvl == "Lv1")
    {
        _backgroundLv1 = new MapDisplay(_filePathTileset,_tabBackgroundLv1,_mapSize,sf::Vector2u(32,32));
        _backgroundLv1->createMap();
        return _backgroundLv1;
    }
    else if (lvl == "Lv2")
    {
        _backgroundLv2 = new MapDisplay(_filePathTileset,_tabBackgroundLv2,_mapSize,sf::Vector2u(32,32));
        _backgroundLv2->createMap();
        return _backgroundLv2;
    }
    else
    {
        return NULL;
    }
}

MapDisplay* Map::reloadBackground(std::string lvl)
{
    if (lvl == "Lv1")
    {
        _backgroundLv1->reload(_tabBackgroundLv1,_mapSize);
        return _backgroundLv1;
    }
    else if (lvl == "Lv2")
    {
        _backgroundLv2->reload(_tabBackgroundLv2,_mapSize);
        return _backgroundLv2;
    }
    else
    {
        return NULL;
    }
}
