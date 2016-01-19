#ifndef __UTILITIES__H__
#define __UTILITIES__H__

#include <Actor.h>

#include <Line.h>
#include <Circle.h>
#include <ReaderClass.h>
#include <iostream>
#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

float getPi();

int getApproachDir(Actor* a1, Actor* a2);

bool isRectangularHit(Actor* a1,Actor* a2);

float getAngleTo(Actor* a1,Actor* a2);

bool hitTest(Actor* a1,Actor* a2);

void getObjectCenter(Actor* a,float& cx,float& cy);

int getRandInt(int low, int high);

float getRand(float low,float high);


void addGraphic(std::string name,std::string file_name,bool isRepeated=false);

const sf::Texture& getGraphic(std::string name);

void addFont(std::string name,std::string file_name);

const sf::Font& getFont(std::string name);

void addSong(std::string name,std::string file_name, bool repeat);

sf::Music* getSong(std::string name);

void destroySongs();

#endif
