#include "ParticleManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Timer.h"
#include "P_Follow.h"
#include "P_Fire.h"
#include "P_Explosion.h"

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


	//texture
	texture.push_back(App->tex->Load("Particles/pixel_grass_2.png"));
	texture.push_back(App->tex->Load("Particles/pixel_fire_1.png"));
	texture.push_back(App->tex->Load("Particles/pixel_firework_1.png"));
	texture.push_back(App->tex->Load("Particles/pixel_star.png"));

	Group_Follow.push_back(new P_Follow(App->scene->player, texture[0]));
	Group_Fire.push_back(new P_Fire(iPoint(327, 246), texture[1], iPoint(5,2), iPoint(15,5), fPoint(0, -60), P_NON, 65, 4, true));
	//mouse
	//Group_Fire.push_back(new P_Fire(&App->input->mouse_pos, texture[1], iPoint(20, 10), iPoint(10, 3), fPoint(0, -60), P_NON, 5000, 2, 4, true));

	Group_Fire.push_back(new P_Fire(iPoint(250, 250), texture[1], iPoint(5, 2), iPoint(20, 5), fPoint(45, -60), P_NON, 65, 4, true, W_LEFT));
	//mouse v2
	//Group_Follow.push_back(new P_Follow(&App->input->mouse_pos, texture[1], iPoint(2,2), iPoint(15,5), 2, 4, 40, true));

	


	//Add a metod particleGroup with type == Follow
	/*Group.push_back(new ParticleGroup(FOLLOW, texture[0], fPoint(App->scene->player->position.x, App->scene->player->position.y), fPoint(0,0), App->tex->GetHeight(texture[0]), 90));

	//lamp
	Group.push_back(new ParticleGroup(FIRE_VERTICAL, texture[1], fPoint(327, 246), fPoint(0, -60), App->tex->GetHeight(texture[1]), 80));

	Group.push_back(new ParticleGroup(FIRE_VERTICAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y), fPoint(0, -100), App->tex->GetHeight(texture[1]), 80));
	Group.push_back(new ParticleGroup(FIRE_LATERAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y - 8), fPoint(100, -30), App->tex->GetHeight(texture[1]), 65));
	Group.push_back(new ParticleGroup(FIRE_VERTICAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y), fPoint(0, 100), App->tex->GetHeight(texture[1]), 80));
	Group.push_back(new ParticleGroup(FIRE_LATERAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y - 8), fPoint(-100, -30), App->tex->GetHeight(texture[1]), 65));
	*/
	//Group.push_back(new ParticleGroup(FIREWORK_RANDOM, texture[2], fPoint(250, 250), fPoint(1, -3), App->tex->GetHeight(texture[2]), 20));

	//Group.push_back(ParticleGroup(FIREWORK, texture[2], fPoint(180, 200), fPoint(-1, -3), App->tex->GetHeight(texture[2]), 1));

	
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
		Group_Explosion.push_back(new P_Explosion(iPoint(250, 200), texture[1], CROSS, iPoint(20, 20), iPoint(10, 2), fPoint(60, 60), P_NON, 21));
	}

	if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
	{
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], CROSS, iPoint(20, 20), iPoint(10, 2), fPoint(60, 60), P_NON, 21));
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], RANDOM, iPoint(12, 12), iPoint(20, 10), fPoint(100, -60), P_LEFT, 21));
		Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], CIRCLE, iPoint(0, 0), iPoint(5, 2), fPoint(60, -60), P_RANDOM, 10));
	}
	if (App->input->GetMouseButtonDown(2) == KEY_DOWN)
	{
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], RANDOM, iPoint(20, 20), iPoint(20, 8), fPoint(60, -60), P_RANDOM_X, 21));
		Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], CIRCLE, iPoint(0, 0), iPoint(5, 2), fPoint(60, -60), P_RANDOM, 20));
	}
	if (App->input->GetMouseButtonDown(3) == KEY_DOWN)
	{
		//Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], RANDOM, iPoint(20, 20), iPoint(20, 8), fPoint(200, -60), P_RANDOM_X, 21));
		Group_Explosion.push_back(new P_Explosion(App->input->GetMousePosition(), texture[1], CIRCLE, iPoint(0, 0), iPoint(5, 2), fPoint(60, -60), P_RANDOM, 30));
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
			LOG("DELETE EXPLOSION!------------------");
		}
		else
		{
			item_3._Ptr->_Myval->Update(dt);
		}
		item_3++;
	}


	return true;
}

bool ParticleManager::PostUpdate()
{
	//j1PerfTimer time;
	//time.Start();

	//Iterate all list
	std::list<P_Follow*>::iterator item = Group_Follow.begin();
	while (item != Group_Follow.end())
	{
		item._Ptr->_Myval->PostUpdate();
		item++;
	}

	std::list<P_Fire*>::iterator item_2 = Group_Fire.begin();
	while (item_2 != Group_Fire.end())
	{
		item_2._Ptr->_Myval->PostUpdate();
		item_2++;
	}

	std::list<P_Explosion*>::iterator item_3 = Group_Explosion.begin();
	while (item_3 != Group_Explosion.end())
	{
		item_3._Ptr->_Myval->PostUpdate();
		item_3++;
	}




	//LOG("TIMER %.5f", time.ReadMs());

	return true;
}

bool ParticleManager::CleanUp()
{
	return true;
}

bool ParticleManager::CreateFollowParticle(SceneElement* element_to_follow, SDL_Texture* texture, iPoint* object, int num_particles, bool active_)
{
	/*if (element_to_follow != nullptr)
	{
		Group_Follow.push_back(new P_Follow(element_to_follow, texture,  num_particles, active_));
	}
	else
	{
		Group_Follow.push_back(new P_Follow(object, texture, num_particles, active_));
	}*/

	return true;
}


