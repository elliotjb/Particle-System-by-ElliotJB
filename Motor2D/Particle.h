#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "ParticleManager.h"

class Particle
{
public:
	//Initialize position and animation
	//Constructor Particle
	Particle(fPoint respawn, iPoint area_respawn = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int size = 2, int num_tex_p = 4, bool active = false, Wind dir = W_NON, iPoint num_tex = { 0,0 });

	//Reactive this only when the particle is created
	bool Modify(fPoint respawn, iPoint area_respawn = { 12, 2 }, iPoint timelife = { 15,5 }, iPoint num_tex_p = { 0, 4 });

	//Checks if particle is dead
	bool isDead();

	//render particle
	void render(SDL_Texture* texture);

	//Move particles
	void Move(fPoint speed, Wind dir = W_NON, bool Move_alternative = false);
	//GetPosition
	fPoint GetPosition();

	fPoint GetSpeed();
	void SetSpeedGreavity(fPoint speed);

	void SetRepeat(bool);
	bool GetRepeat();

private: //private??
		 //Offsets
	fPoint position;

	//Texture
	SDL_Rect rect;
	SDL_Rect area_respawn;

	//velocity
	fPoint speed;
	int size_rect;


	bool not_repeat; //ONLY FIREWORK

	//int
	iPoint degrade;
};

#endif /*_PARTICLE_H_*/