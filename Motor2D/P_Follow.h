#pragma once
#ifndef _P_FOLLOW_H_
#define _P_FOLLOW_H_

#include "ParticleManager.h"
#include "SceneElements.h"

class Particle;

class P_Follow
{
public:
	P_Follow(SceneElement* element_to_follow, iPoint* object_follow, SDL_Texture* texture, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, int num_textures = 4, int num_particles = 20, bool active_ = false);
	~P_Follow();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);
	void MoveParticles();

	void Update_position(iPoint* pos);


public:
	SDL_Texture* texture;
	std::vector<Particle*> particle;
	SceneElement* element_to_follow;
	//Num of particles
	int number_particles;

	//iPoints
	iPoint* object_follow;
	iPoint area;
	iPoint timelife;

	//position
	fPoint pos;
	int size_rect;
	int n_textures;

	//velocity
	//fPoint speed;
	bool active;

	bool godelete;

};


#endif /*_P_FOLLOW_H_*/