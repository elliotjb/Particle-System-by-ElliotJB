#include "ParticleManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Timer.h"
#include "P_Follow.h"
#include "P_Fire.h"

/*Particle::Particle(int x, int y, int size, TypeMoviment type, fPoint speed_particle, bool isActive)
{
	if (type == FOLLOW)
	{
		//with random change position
		position.x = x - (rand() % 12) + (rand() % 10);
		position.y = y - (rand() % 2) + (rand() % 2);

		//Inicialitzed with random the timelife of the particle
		timelife = rand() % 12;

		//Set SDL_Rect
		switch (rand() % 4)
		{
		case 0: rect = { 0,0,size,size }; break;
		case 1: rect = { size,0,size,size }; break;
		case 2: rect = { size * 2,0,size,size }; break;
		case 3: rect = { size * 3,0,size,size }; break;
		}
		if (isActive)
		{
			degrade.y = 255;
		}
		else
		{
			degrade.y = 0;
		}

		degrade.x = (rand() % 15 + 5);
	}
	else if (type == FIREWORK_RANDOM)
	{
		//with random change position
		position.x = x - (rand() % 5) + (rand() % 5);
		position.y = y;

		degrade.y = 255;
		degrade.x = 1;

		speed = speed_particle;
		speed.y -= (((float)rand() / (float)(RAND_MAX)) * 1);
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 2) - (((float)rand() / (float)(RAND_MAX)) * 2);

		//Set SDL_Rect
		rect = { 0,0,size,size };
	}
	else if (type == FIREWORK)
	{
		//with random change position
		position.x = x;
		position.y = y;

		degrade.y = 255;
		degrade.x = 3;

		speed = speed_particle;
		speed.y -= (((float)rand() / (float)(RAND_MAX)) * 1);
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 2) - (((float)rand() / (float)(RAND_MAX)) * 2);

		//Set SDL_Rect
		rect = { 0,0,size,size };
	}
	else
	{
		//with random change position
		position.x = x - (rand() % 5) + (rand() % 5);
		position.y = y - (rand() % 2) + (rand() % 2);

		//Inicialitzed with random the timelife of the particle
		timelife = rand() % 25;

		if (isActive)
		{
			degrade.y = 255;
		}
		else
		{
			degrade.y = 0;
		}
		degrade.x = (rand() % 15 + 5);

		speed = speed_particle;

		//Set SDL_Rect
		switch (rand() % 4)
		{
		case 0: rect = { 0,0,size,size }; break;
		case 1: rect = { size,0,size,size }; break;
		case 2: rect = { size * 2,0,size,size }; break;
		case 3: rect = { size * 3,0,size,size }; break;
		}
	}
}

bool Particle::Modify(int x, int y, int size, TypeMoviment type)
{
	if (type == FOLLOW)
	{
		//with random change position
		position.x = x - (rand() % 12) + (rand() % 10);
		position.y = y - (rand() % 2) + (rand() % 2);

		//Inicialitzed with random the timelife of the particle
		timelife = rand() % 12;

		//Set SDL_Rect
		switch (rand() % 4)
		{
		case 0: rect = { 0,0,size,size }; break;
		case 1: rect = { size,0,size,size }; break;
		case 2: rect = { size * 2,0,size,size }; break;
		case 3: rect = { size * 3,0,size,size }; break;
		}
		degrade.y = 255;
		degrade.x = (rand() % 15 + 5);
	}
	else if (type == FIREWORK_RANDOM)
	{
		//with random change position
		position.x = x;
		position.y = y;

		//Inicialitzed with random the timelife of the particle
		timelife = rand() % 25;
		degrade.y = 255;
		degrade.x = 3;

		speed.y = (((float)rand() / (float)(RAND_MAX)) * -2);
		if (speed.x >= 0)
		{
			speed.x = (((float)rand() / (float)(RAND_MAX)) * -2);
		}
		if (speed.x < 0)
		{
			speed.x = (((float)rand() / (float)(RAND_MAX)) * 2);
		}

		switch (rand() % 3)
		{
		case 0: rect = { size * 3,0,size,size }; break;
		case 1: rect = { size,0,size,size }; break;
		case 2: rect = { size * 2,0,size,size }; break;
		}
	}
	else
	{
		//with random change position
		position.x = x - (rand() % 5) + (rand() % 5);
		position.y = y - (rand() % 2) + (rand() % 2);

		//Inicialitzed with random the timelife of the particle
		timelife = rand() % 25;

		degrade.y = 255;
		degrade.x = (rand() % 15 + 5);

		//Set SDL_Rect
		switch (rand() % 4)
		{
		case 0: rect = { 0,0,size,size }; break;
		case 1: rect = { size,0,size,size }; break;
		case 2: rect = { size * 2,0,size,size }; break;
		case 3: rect = { size * 3,0,size,size }; break;
		}
	}
	return true;
}

bool Particle::isDead()
{
	//return timelife > 25;
	return degrade.y == 0;
}

void Particle::render(SDL_Texture* texture)
{
	App->render->Blit(texture, position.x, position.y, &rect);
	degrade.y -= MIN(degrade.y, degrade.x);
	if (degrade.y <= 0)
	{
		degrade.y = 0;
	}

	SDL_SetTextureAlphaMod(texture, degrade.y);

	timelife++;
}

void Particle::Move(fPoint speed_set, TypeMoviment type)
{
	if (type == FOLLOW || type == FIRE_VERTICAL)
	{
		position.x += speed_set.x;
		position.y += speed_set.y;
	}
	else if (type == FIREWORK_RANDOM)
	{
		speed.y += -speed_set.y;
		position.y += speed.y;
		position.x += speed.x;
	}
	else
	{
		if (degrade.y < 60)
		{
			position.y += speed_set.y;
		}
		position.x += speed_set.x;
	}

}

fPoint Particle::GetPosition()
{
	return position;
}*/

/*ParticleGroup::ParticleGroup(TypeMoviment type_, SDL_Texture* texture_, fPoint pos_, fPoint speed_, int size, int num_particles, bool active_)
{
	//
	texture = texture_;
	type = type_;
	//
	pos = pos_;
	speed = speed_;
	//
	size_rect = size;
	//
	number_particles = num_particles;
	cont_active_firework = 0;
	gravity = -9.8;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos.x, pos.y, size, type_, speed, active);
		particle.push_back(temp);
	}


	//int temp = 0;
}

ParticleGroup::~ParticleGroup()
{
}

void ParticleGroup::render(fPoint pos, fPoint speed)
{
	if (type == FOLLOW)
	{
		if (active)
		{
			//Check if the particle dead
			for (int i = 0; i < number_particles; i++)
			{
				if (particle[i]->isDead())
				{
					particle[i]->Modify(pos.x, pos.y, App->tex->GetHeight(texture), type);
				}
			}
		}

		//Draw particles
		for (int i = 0; i < number_particles; i++)
		{
			particle[i]->render(texture);
		}
	}
	if (type == FIREWORK_RANDOM)
	{
		if (active)
		{
			//Check if the particle dead
			for (int i = 0; i < number_particles; i++)
			{
				if (cont_active_firework >= number_particles)
				{
					if(particle[i]->isDead())
					{
						godelete = true;
					}
				}
				else if (particle[i]->isDead() && cont_active_firework < number_particles)
				{
					cont_active_firework++;
					particle[i]->Modify(particle[i]->GetPosition().x, particle[i]->GetPosition().y, size_rect, type);
				}

			}
		}
		//Draw particles
		for (int i = 0; i < number_particles; i++)
		{
			particle[i]->render(texture);
		}
	}
	if (type == FIRE_VERTICAL || type == FIRE_LATERAL)
	{
		if (active)
		{
			//Check if the particle dead
			for (int i = 0; i < number_particles; i++)
			{
				if (particle[i]->isDead())
				{
					particle[i]->Modify(pos.x, pos.y, size_rect, type);
				}
			}
		}
		//Draw particles
		for (int i = 0; i < number_particles; i++)
		{
			particle[i]->render(texture);
		}
	}
}

void ParticleGroup::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		float temp = App->GetDT();
		particle[i]->Move(fPoint(speed.x * temp, speed.y * temp), type);
	}
}*/

/**bool ParticleManager::DeleteGroup(ParticleGroup* group)
{
	std::list<ParticleGroup*>::iterator item = Group.begin();
	while (item != Group.end())
	{
		if (item._Ptr->_Myval == group)
		{
			Group.erase(item);
		}
		item++;
	}


	return true;
}*/

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

	Group_Follow.push_back(new P_Follow(App->scene->player, texture[0]));
	Group_Fire.push_back(new P_Fire(iPoint(327, 246), texture[1], iPoint(5,2), iPoint(15,5), fPoint(0, -60), true, 65, 2, 4, true));
	//mouse
	Group_Fire.push_back(new P_Fire(&App->input->mouse_pos, texture[1], iPoint(5, 2), iPoint(15, 5), fPoint(0, -60), true, 65, 2, 4, true));

	Group_Fire.push_back(new P_Fire(iPoint(250, 250), texture[1], iPoint(5, 2), iPoint(20, 5), fPoint(0, -60), false, 65, 2, 4, true, W_LEFT));
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

	return true;
}

bool ParticleManager::PostUpdate()
{
	j1PerfTimer time;
	time.Start();

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




	LOG("TIMER %.5f", time.ReadMs());

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


