#pragma once
#ifndef _P_FIREWORK_H_
#define _P_FIREWORK_H_

#include "ParticleManager.h"
#include "SceneElements.h"

class Particle;

class P_Firework
{
public:
	//	P_Follow(iPoint* element, iPoint area, iPoint timelife, SDL_Texture* texture, int size_particle, int num_textures, int num_particles = 20, bool active_ = false);
	P_Firework(SceneElement* element, SDL_Texture* texture, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = W_NON);
	P_Firework(iPoint* element, SDL_Texture* texture, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = W_NON);
	P_Firework(iPoint pos, SDL_Texture* texture, iPoint area = { 12, 2 }, iPoint timelife = { 15,5 }, fPoint speed = { 0,0 }, P_Direction p_direction = P_NON, int num_particles = 20, int num_textures = 4, bool active_ = false, Wind dir = W_NON);
	~P_Firework();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	void render(fPoint pos);

	void MoveParticles();

public:
	SDL_Texture* texture;
	std::vector<Particle*> particle;
	SceneElement* element_to_follow;
	//Num of particles
	int number_particles;

	//test
	iPoint* object_follow;

	//wind
	Wind dir_wind;
	bool wind_speed;
	iPoint timelife;

	//position
	fPoint pos;
	int size_rect;
	int n_textures;
	iPoint area;

	//velocity
	fPoint speed;
	bool active;

	bool godelete;

	int cont_active_firework;

};


#endif /*_P_FIREWORK_H_*/