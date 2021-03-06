#pragma once

#include <SFML/Graphics.hpp>
#include "maths.h"
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem
{
public:
	enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT };

	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void render(sf::RenderWindow &window);
	static sf::Color getColor(TILE t);
	static void setColor(TILE t);
	static void setColor(TILE t, sf::Color c);
	static size_t getHeight() { return _height; }
	static size_t getWidth() { return _width; }
	//Get Tile at grid coordinate
	static TILE getTile(sf::Vector2ul);
	//Get Screenspace coordinate of tile
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	//get the tile at screenspace pos
	static TILE getTileAt(sf::Vector2f);

protected:
	static std::unique_ptr<TILE[]> _tiles; //Internal array of tiles
	static size_t _width; //how many tiles wide is a level
	static size_t _height; //how many tiles high is a level
	static sf::Vector2f _offset; //Screenspace offset of level, when rendered.
	static float _tileSize; //Screenspace size of each tile, when rendered.
	static std::map<TILE, sf::Color> _colours; //colour of each tile type

	//array of sfml sprites of each tile
	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
	//generatire the _sprites array
	static void buildSprites();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};