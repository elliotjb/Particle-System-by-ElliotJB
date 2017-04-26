#pragma once
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include "j1Module.h"
#include "j1Scene.h"

#define MAX_TIMELIFE 255
#define NORMAL_SPEED_Y 180

enum Wind { W_NON = 0, W_UP, W_DOWN, W_LEFT, W_RIGHT };
enum P_Direction { P_NON, P_UP, P_DOWN, P_LEFT, P_RIGHT, P_RANDOM_X, P_RANDOM_Y, P_RANDOM, P_RANDOM_FIREWORK };


class P_Follow;
class P_Fire;
class P_Explosion;
class P_Firework;

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
	std::list<P_Explosion*> Group_Explosion;
	std::list<P_Firework*> Group_Firework;
	std::vector<SDL_Texture*> texture;
private:





};

#endif // __PARTICLESYSTEM_H__