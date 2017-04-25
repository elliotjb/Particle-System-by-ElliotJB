#pragma once
#ifndef _P_EXPLOSION_H_
#define _P_EXPLOSION_H_

#include "ParticleManager.h"
#include "SceneElements.h"

enum Explosion_Type { CIRCLE, CROSS, RANDOM  };

class Particle;

class P_Explosion
{
public:
	P_Explosion(SceneElement* element, SDL_Texture* texture, Explosion_Type type, iPoint perimeter = { 20, 20 }, iPoint timelife = { 20,10 }, fPoint speed = { 0,0 }, int num_particles = 20, int size_particle = 2, int num_textures = 4);
	P_Explosion(iPoint* element, SDL_Texture* texture, Explosion_Type type, iPoint perimeter = { 20, 20 }, iPoint timelife = { 20,10 }, fPoint speed = { 0,0 }, int num_particles = 20, int size_particle = 2, int num_textures = 4);
	P_Explosion(iPoint pos, SDL_Texture* texture, Explosion_Type type, iPoint perimeter = { 20, 20 }, iPoint timelife = { 20,10 }, fPoint speed = { 0,0 }, int num_particles = 20, int size_particle = 2, int num_textures = 4);
	~P_Explosion();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void Update_position(iPoint* pos);

	void MoveParticles();

public:
	SDL_Texture* texture;
	std::vector<Particle*> particle;
	SceneElement* element_to_follow;
	//Num of particles
	int number_particles;

	//test
	iPoint* object_follow;

	//timelife
	iPoint timelife;

	//position
	fPoint pos;
	int size_rect;

	//velocity
	fPoint speed;
	bool active;

	bool godelete;

};


#endif /*_P_EXPLOSION_H_*/