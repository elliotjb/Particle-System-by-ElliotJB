#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "j1Module.h"
#include "j1Scene.h"

enum Wind { W_NON = 0, W_UP, W_DOWN, W_LEFT, W_RIGHT };

class P_Follow;
class P_Fire;

/*class Particle
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
};*/



/*class ParticleGroup
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
};*/


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
	virtual bool Update(float dt);

	// Called before all Updates
	virtual bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//create Group
	//void CreateFIRE(TypeMoviment type, SceneElement* element_to_follow);
	//void CreateFIREWORK(TypeMoviment type, SceneElement* element_to_follow);
	bool CreateFollowParticle(SceneElement* element_to_follow, SDL_Texture* texture, iPoint* pos_object = nullptr, int num_particles = 20, bool active_ = false);
	//bool DeleteGroup(ParticleGroup* group);

public:
	//std::list<ParticleGroup*> Group;
	std::list<P_Follow*> Group_Follow;
	std::list<P_Fire*> Group_Fire;
	std::vector<SDL_Texture*> texture;
private:





};

#endif // __PARTICLESYSTEM_H__