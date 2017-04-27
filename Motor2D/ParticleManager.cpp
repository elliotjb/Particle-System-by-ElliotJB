#include "ParticleManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Timer.h"
#include "P_Follow.h"
#include "P_Fire.h"
#include "P_Explosion.h"
#include "P_Firework.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

bool ParticleManager::Awake()
{
	return true;
}

bool ParticleManager::Start()
{
	test_age = App->tex->Load("Particles/test_age_1.png");

	//texture
	atlas_particle = App->tex->Load("Particles/pixel_fire_1.png"); //1


	Group_Follow.push_back(new P_Follow(App->scene->player, nullptr));
	//Group_Fire.push_back(new P_Fire(iPoint(327, 246), texture[1], iPoint(5,2), iPoint(15,5), fPoint(0, -60), P_NON, 65, 4, true));
	//mouse
	//Group_Fire.push_back(new P_Fire(&App->input->mouse_pos, texture[1], iPoint(20, 10), iPoint(10, 3), fPoint(60, -60), P_RANDOM, 5000, 4, true));

	//Group_Fire.push_back(new P_Fire(iPoint(250, 250), texture[1], iPoint(5, 2), iPoint(20, 5), fPoint(45, -60), P_NON, 65, 4, true, W_LEFT));
	//mouse v2
	//Group_Follow.push_back(new P_Follow(&App->input->mouse_pos, texture[1], iPoint(2,2), iPoint(15,5), 2, 4, 40, true));


	return true;
}

bool ParticleManager::PreUpdate()
{
	return true;
}

bool ParticleManager::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, iPoint(250, 200), SDL_Rect{ 0,0,8,4 }, CROSS, iPoint(20, 20), iPoint(10, 2), fPoint(60, 60), P_NON, 21));
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		Group_Firework.push_back(new P_Firework(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,0,8,4 }, iPoint(0, 2), fPoint(0, -400), P_NON, 20, 1, iPoint(1,1), iPoint(1, 4)));
	}


	if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
	{
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], CROSS, iPoint(20, 20), iPoint(10, 2), fPoint(60, 60), P_NON, 21));
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], RANDOM, iPoint(12, 12), iPoint(20, 10), fPoint(100, -60), P_LEFT, 21));
		Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,0,8,4 }, CIRCLE, iPoint(0, 0), iPoint(5, 2), fPoint(60, -60), P_RANDOM, 10));
	}
	if (App->input->GetMouseButtonDown(2) == KEY_DOWN)
	{
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], RANDOM, iPoint(20, 20), iPoint(20, 8), fPoint(60, -60), P_RANDOM_X, 21));
		Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,0,8,4 }, CIRCLE, iPoint(0, 0), iPoint(5, 2), fPoint(60, -60), P_RANDOM, 20));
	}
	if (App->input->GetMouseButtonDown(3) == KEY_DOWN)
	{
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], RANDOM, iPoint(20, 20), iPoint(20, 8), fPoint(200, -60), P_RANDOM_X, 21));
		Group_Explosion.push_back(new P_Explosion(nullptr, nullptr, App->input->GetMousePosition(), SDL_Rect{ 0,0,8,4 }, CIRCLE, iPoint(0, 0), iPoint(5, 2), fPoint(60, -60), P_RANDOM, 30));
	}

	std::list<P_Follow*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->Update(dt);
		item++;
	}

	std::list<P_Fire*>::iterator item_2 = Group_Fire.begin();
	while (item_2 != Group_Fire.end())
	{
		item_2._Ptr->_Myval->Update(dt);
		item_2++;
	}
	std::list<P_Explosion*>::iterator item_3 = Group_Explosion.begin();
	while (item_3 != Group_Explosion.end())
	{
		if (item_3._Ptr->_Myval->godelete)
		{
			item_3._Ptr->_Myval->particle.clear();
			Group_Explosion.erase(item_3);
		}
		else
		{
			item_3._Ptr->_Myval->Update(dt);
		}
		item_3++;
	}

	std::list<P_Firework*>::iterator item_4 = Group_Firework.begin();
	while (item_4 != Group_Firework.end())
	{
		if (item_4._Ptr->_Myval->godelete)
		{
			item_4._Ptr->_Myval->particle.clear();
			Group_Firework.erase(item_4);
		}
		else
		{
			item_4._Ptr->_Myval->Update(dt);
		}
		item_4++;
	}


	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(305, 162), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(314, 174), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(374, 136), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(361, 226), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(266, 276), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(386, 319), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
		Group_Fire.push_back(new P_Fire(nullptr, nullptr, iPoint(468, 207), SDL_Rect{ 0,0,8,4 }, iPoint(10, 2), iPoint(20, 5), fPoint(0, -60), P_NON, 65, 4, true, W_NON));
	}

	


	return true;
}

bool ParticleManager::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_REPEAT)
	{
		App->render->Blit(test_age, 100, 50);

	}

	//Iterate all list
	//Group FOLLOW -------------------------------------------------
	std::list<P_Follow*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->PostUpdate();
		item++;
	}
	//Group FRIE -------------------------------------------------
	std::list<P_Fire*>::iterator item_2 = Group_Fire.begin();
	while (item_2 != Group_Fire.end())
	{
		item_2._Ptr->_Myval->PostUpdate();
		item_2++;
	}
	//Group EXPLOSION -------------------------------------------------
	std::list<P_Explosion*>::iterator item_3 = Group_Explosion.begin();
	while (item_3 != Group_Explosion.end())
	{
		item_3._Ptr->_Myval->PostUpdate();
		item_3++;
	}
	//Group FIREWORK -------------------------------------------------
	std::list<P_Firework*>::iterator item_4 = Group_Firework.begin();
	while (item_4 != Group_Firework.end())
	{
		item_4._Ptr->_Myval->PostUpdate();
		item_4++;
	}


	return true;
}

bool ParticleManager::CleanUp()
{
	return true;
}

//CREATE GROUPS -------------------------------------------------------------------------------------------------------------------------------------

void ParticleManager::CreateFollow_P(SceneElement* element_to_follow, iPoint* object_follow, SDL_Rect initial_rect, iPoint area, iPoint timelife, int num_textures, int num_particles, bool active, bool isMouse)
{
	Group_Follow.push_back(new P_Follow(element_to_follow, object_follow, initial_rect, area, timelife, num_textures, num_particles, active, isMouse));
}

void ParticleManager::CreateFire_Particle(SceneElement* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint area, iPoint timelife, fPoint speed, P_Direction p_direction, int num_particles, int num_textures, bool active, Wind w_dir)
{
	Group_Fire.push_back(new P_Fire(element_to_follow, object_follow, position_static, initial_rect, area, timelife, speed, p_direction, num_particles, num_textures, active, w_dir));
}

void ParticleManager::CreateExplosion_Particle(SceneElement* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, Explosion_Type type, iPoint perimeter, iPoint timelife, fPoint speed, P_Direction p_direction, int num_particles, int num_textures)
{
	Group_Explosion.push_back(new P_Explosion(element_to_follow, object_follow, position_static, initial_rect, type, perimeter, timelife, speed, p_direction, num_particles, num_textures));
}

void ParticleManager::CreateFirework_Particle(SceneElement* element_to_follow, iPoint* object_follow, iPoint position_static, SDL_Rect initial_rect, iPoint timelife, fPoint speed, P_Direction p_direction, int num_particles, int num_textures, iPoint next_textures, iPoint last_textures)
{
	Group_Firework.push_back(new P_Firework(element_to_follow, object_follow, position_static, initial_rect, timelife, speed, p_direction, num_particles, num_textures, next_textures, last_textures));
}


//DELETE GROUPS -------------------------------------------------------------------------------------------------------------------------------------

bool ParticleManager::DeleteFollow_p(P_Follow* group)
{
	std::list<P_Follow*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		if (item._Ptr->_Myval == group)
		{
			Group_Follow.erase(item);
		}
		item++;
	}
	return true;
}

bool ParticleManager::DeleteFire_p(P_Fire* group)
{
	std::list<P_Fire*>::iterator item = Group_Fire.begin();
	while (item != Group_Fire.end())
	{
		if (item._Ptr->_Myval == group)
		{
			Group_Fire.erase(item);
		}
		item++;
	}
	return true;
}

bool ParticleManager::DeleteExplosion_p(P_Explosion* group)
{
	std::list<P_Explosion*>::iterator item = Group_Explosion.begin();
	while (item != Group_Explosion.end())
	{
		if (item._Ptr->_Myval == group)
		{
			Group_Explosion.erase(item);
		}
		item++;
	}
	return true;
}

bool ParticleManager::DeleteFirework_p(P_Firework* group)
{
	std::list<P_Firework*>::iterator item = Group_Firework.begin();
	while (item != Group_Firework.end())
	{
		if (item._Ptr->_Myval == group)
		{
			Group_Firework.erase(item);
		}
		item++;
	}
	return true;
}