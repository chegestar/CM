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

}

/**
 * Calls the superclass functions for act(). Any Enemy-specific acting would
 * take place here.
 */
void Enemy::act() {
  Mover::act();
  Die::act();
}

