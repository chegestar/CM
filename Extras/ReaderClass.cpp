#include "stdafx.h"
#include "ReaderClass.h"
#include <stdexcept>

void Reader::registerGraphics(std::string name,std::string file_name) {
  sf::Texture text;
  text.loadFromFile(file_name);
  graphics.insert(std::make_pair(name,text));
}
void Reader::registerFont(std::string name,std::string file_name) {
  sf::Font font;
  font.loadFromFile(file_name);
  fonts.insert(std::make_pair(name,font));
}
void Reader::registerSong(std::string name,std::string file_name, bool repeat) {
  sf::Music* song = new sf::Music;
  song->openFromFile(file_name);
  song->setLoop(repeat);
  songs.insert(std::make_pair(name,song));
}

const sf::Texture& Reader::getGraphics(std::string name) {
  std::map<std::string,sf::Texture>::iterator itr = graphics.find(name);
  if (itr==graphics.end())
    throw std::runtime_error("Graphic not loaded into reader");
  return itr->second;
}
const sf::Font& Reader::getFont(std::string name) {
  std::map<std::string,sf::Font>::iterator itr = fonts.find(name);
  if (itr==fonts.end())
    throw std::runtime_error("Font not loaded into reader");
  return itr->second;
}
sf::Music* Reader::getSong(std::string name) {
  std::map<std::string,sf::Music*>::iterator itr = songs.find(name);
  if (itr==songs.end())
    throw std::runtime_error("Music not loaded into reader");
  return itr->second;
}

void Reader::destroy() {
  std::map<std::string,sf::Music*>::iterator itr;
  for (itr=songs.begin();itr!=songs.end();itr++)
    delete itr->second;
  songs.clear();
}
