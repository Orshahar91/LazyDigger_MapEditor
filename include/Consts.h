#pragma once

#include <string>
using std::string;

const string TILE_PNG_FILEPATH = "Empty.png";
const string DIGGER_PNG_FILEPATH = "Digger.png";
const string MONSTER_PNG_FILEPATH = "Monster.png";
const string STONE_PNG_FILEPATH = "Stone.png";
const string DIAMOND_PNG_FILEPATH = "Diamond.png";
const string WALL_PNG_FILEPATH = "Wall.png";
const string CLEAR_PNG_FILEPATH = "Clear.png";
const string SAVE_PNG_FILEPATH = "Save.png";
const string ERASE_PNG_FILEPATH = "Erase.png";
const string MESSAGE_PNG_FILEPATH = "Message.png";

const unsigned  SCREEN_WIDTH = 1280;
const unsigned  SCREEN_HEIGHT = 720;

const string APP_NAME = "Dogger_Editor";
const string FILE_NAME = "Board.txt";

const unsigned NUM_OF_BUTTONS = 8;

const unsigned TILE_SIZE = 35;	// The tile's size (in pixels).

// Enum for each object by his char representation.
enum Char_t
{
	C_EMPTY = ' ', C_DIGGER = '/', C_WALL = '#', C_MONSTER = '!', C_DIAMOND = 'D', C_STONE = '@'
};

// Enum for each object in the project. 
enum Object_t
{
	O_ERASE, O_DIGGER, O_MONSTER, O_WALL, O_STONE, O_DIAMOND, O_CLEAR, O_SAVE, O_TILE, O_MESSAGE
};
