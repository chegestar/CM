#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef __READER__H__
#define __READER__H__

class Reader {
 public:
  Reader() {}
  
  void destroy();
  void registerGraphics(std::string name,std::string file_name);
  void registerFont(std::string name,std::string file_name);
  void registerSong(std::string name,std::string file_name, bool repeat);

  const sf::Texture& getGraphics(std::string name);
  const sf::Font& getFont(std::string name);
  sf::Music* getSong(std::string name);

 private:
  std::map<std::string,sf::Texture> graphics;
  std::map<std::string,sf::Font> fonts;
  std::map<std::string,sf::Music*> songs;
};

#endif
