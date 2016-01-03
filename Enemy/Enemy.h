#include <Mover.h>
#include <Die.h>

#ifndef __ENEMY__H__
#define __ENEMY__H__

class Bob;

class Enemy : public Die, public Mover {
public:
    /**
     * Constructs a new Enemy, which is an actor that can kill Bob and can move.
     *
     * @param[in] l The level to add the enemy to
     * @param[in] x The x (horizontal) coordinate of the position for the enemy
     * @param[in] y The y (vertical coordinate of the) position for the enemy
     * @param[in] w The width of the enemy
     * @param[in] h The height of the enemy
     */
    Enemy(Level *l, float x, float y, float w, float h);

    /**
     * Handles acting for the Enemy. Note: virutal required so that subclasses
     * can define their own acting specifications.
     */
    virtual void act();

    /**
     * Renders the enemy in the window provided.
     *
     * @param[in/out] window The window that the enemy will be added to
     */
    void render(sf::RenderWindow &window);
};

#endif
