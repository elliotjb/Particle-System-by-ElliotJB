#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "j1Module.h"
#include "j1Scene.h"

enum TypeMoviment 
{
	FOLLOW,				 /* This the point follow the "Object" */
	FIRE_VERTICAL,		 /*  */
	FIRE_LATERAL,	   	 /*  */
	EXPLISION,			 /*  */
	EXPLISION_UP,		 /*  */
	EXPLISION_DOWN,		 /*  */
	EXPLISION_RIGHT,	 /*  */
	EXPLISION_LEFT,		 /*  */
	FIREWORK_RANDOM,	 /*  */
	FIREWORK
};


class Particle
{
public:
	//Initialize position and animation
	Particle(int x, int y, int size, TypeMoviment type, fPoint speed, bool active);

	//Reactive this only when the particle is created
	bool Modify(int x, int y, int size, TypeMoviment type);

	//Checks if particle is dead
	bool isDead();

	//render particle
	void render(SDL_Texture* texture);

	//Move particles
	void Move(fPoint speed, TypeMoviment type);
	//GetPosition
	fPoint GetPosition();
	
private: //private??
	//Offsets
	fPoint position;

	//Current frame of animation
	int timelife;

	//Texture
	SDL_Rect rect;

	//velocity
	fPoint speed;

	//int
	iPoint degrade;
};

class ParticleGroup
{
public:
	//Contructor valors predefinition Num_particules = 20 // active = false
	ParticleGroup(TypeMoviment type, SDL_Texture* texture, fPoint pos, fPoint speed, int size, int num_particles = 20, bool active_ = false);
	~ParticleGroup();

	void render(fPoint pos, fPoint speed);
	void MoveParticles();

public:
	TypeMoviment type;
	SDL_Texture* texture;
	std::vector<Particle*> particle;
	
	//Num of particles
	int number_particles;

	//position
	fPoint pos;
	int size_rect;

	//velocity
	fPoint speed;
	float gravity;
	bool active;

	bool godelete;

	int cont_active_firework;
};


class ParticleManager : public j1Module
{
public:

	ParticleManager();

	// Destructor
	~ParticleManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool DeleteGroup(ParticleGroup* group);

public:
	std::list<ParticleGroup*> Group;
private:

	std::vector<SDL_Texture*> texture;



};

#endif // __PARTICLESYSTEM_H__