#include "Enemy.h"
#include <Bob.h>
#include <utilities.h>
#include <Level.h>

/**
 * Superclass constructors for Actor, Die, and Mover handle all common tasks
 * that don't differ for Enemy objects. Then, a red circle shape is created.
 */
Enemy::Enemy(Level *l, float x, float y, float w, float h) :
    Actor(l, x, y, w, h), Die(l, x, y, w, h), Mover(l, x, y, w, h) {

  static_cast<sf::CircleShape *>(shape)->setFillColor(sf::Color(255, 0, 0));
}

/**
 * Calls the superclass functions for act(). Any Enemy-specific acting would
 * take place here.
 */
void Enemy::act() {
  Mover::act();
  Die::act();
}

/**
 * Renders the enemy using the shape created from the constructor, and sets
 * the position to the x1, y1 provided via the constructor. Then, the window
 * draws the enemy.
 */
void Enemy::render(sf::RenderWindow &window) {
  // TODO: Is this function still needed here?
  static_cast<sf::CircleShape *>(shape)->setPosition(getX1(), getY1());
  window.draw(*shape);
}