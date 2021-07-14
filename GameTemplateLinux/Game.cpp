#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <iostream>

#include <time.h>
#include <stdio.h>
#include <math.h>

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  schedule_quit_game() - quit game after act()
int Score = 0;

#include"vector2.hpp"
#include"gameObject.hpp"
#include"asteroid.hpp"
#include"bullet.hpp"
#include"text.hpp"
#include"player.hpp"
#include"manager.hpp"


const int BulletMax = 20;
const int AsteroidMax = 30;
Bullet* bullets = NULL;
Asteroid* asteroids = NULL;
const float AsteroidCooldown = 0.5;
float TimeFromLastAsteroid = 1;


Player player(10, Vector2 (700, 700), 0x0000ff00);
Manager manager(&player);

// initialize game data in this function
void initialize()
{
    srand((int) time(0));

    bullets = new Bullet [BulletMax];
    asteroids = new Asteroid [AsteroidMax];

     
    // add all to manager to do the magic
    manager.addObjArray((void*)bullets, BulletMax, sizeof(Bullet));
    manager.addObjArray((void*)asteroids, AsteroidMax, sizeof(Asteroid));
    //manager.addObjArray((void*) &player, 1, sizeo);
    
    player.setShootCooldown(0.1);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
	if (is_key_pressed(VK_ESCAPE))
		schedule_quit_game();

    if (!player.isAlive()) 
        return;
		
	if (is_key_pressed(VK_UP))
		player.updSpeed(dt);
		
	if (is_key_pressed(VK_RIGHT))
		player.rotate(dt, Right);
	
	if (is_key_pressed(VK_LEFT))
		player.rotate(dt, Left);
		
	if (is_key_pressed(VK_SPACE))
	    player.shoot(bullets, BulletMax);
		
		

    // TODO add cooldown on spawn
    allBulletsHitAsteroid(bullets, BulletMax, asteroids, AsteroidMax);    
    player.checkHitByAsteroids(asteroids, AsteroidMax);

    TimeFromLastAsteroid += dt;

    if(TimeFromLastAsteroid > AsteroidCooldown)
    {
        addRandomAsteroid(asteroids, AsteroidMax);
        TimeFromLastAsteroid = 0;
    }

    // manager do all work and ✨️magic✨️ here
    manager.updateAll(dt);
    manager.moveAll(dt);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
	// clear backbuffer
	memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
	
	// and here some ✨️magic✨️ too
	manager.drawAll();
	
	int hp = player.getHp();
	
	for(int i = 0; i != hp; i++)
	    drawHp(Vector2 (10, 10 + 12 * i));
	    
	drawNum(Vector2 (10, 500), Score);
}

// free game data in this function
void finalize()
{
    delete [] asteroids;
    delete [] bullets;
}

