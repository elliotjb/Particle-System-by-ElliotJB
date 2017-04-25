#include "P_Fire.h"
#include "Particle.h"

P_Fire::P_Fire(SceneElement* element, SDL_Texture* texture_, iPoint area, iPoint timelife, fPoint speed_particle,bool speed_static, Wind dir, int size_particle, int num_textures, int num_particles, bool active_)
{
	texture = texture_;
	pos.x = element->position.x;
	pos.y = element->position.y;
	if (speed_static)
	{
		speed = speed_particle;
	}
	else
	{
		//speed.y -= (((float)rand() / (float)(RAND_MAX)) * 10);
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 20) - (((float)rand() / (float)(RAND_MAX)) * 20);
	}
	wind_speed = speed_static;

	object_follow = nullptr;
	element_to_follow = element;
	//
	dir_wind = dir;
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos, iPoint(12, 2), iPoint(15, 5), speed, speed_static, 2, 4, true);
		particle.push_back(temp);
	}
}

P_Fire::P_Fire(iPoint* element, SDL_Texture* texture_, iPoint area, iPoint timelife, fPoint speed_particle, bool speed_static, Wind dir, int size_particle, int num_textures, int num_particles, bool active_)
{
	texture = texture_;
	pos.x = element->x;
	pos.y = element->y;
	if (speed_static)
	{
		speed = speed_particle;
	}
	else
	{
		//speed.y -= (((float)rand() / (float)(RAND_MAX)) * 10);
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 20) - (((float)rand() / (float)(RAND_MAX)) * 20);
	}
	wind_speed = speed_static;
	object_follow = element;
	element_to_follow = nullptr;
	//
	dir_wind = dir;
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, iPoint(12, 2), iPoint(15, 5), speed, speed_static, 2, 4, true);
		particle.push_back(temp);
	}
}

P_Fire::P_Fire(iPoint position, SDL_Texture* texture_, iPoint area, iPoint timelife, fPoint speed_particle, bool speed_static, Wind dir, int size_particle, int num_textures, int num_particles, bool active_)
{
	texture = texture_;
	pos.x = position.x;
	pos.y = position.y;
	if (speed_static)
	{
		speed = speed_particle;
	}
	else
	{
		//speed.y -= (((float)rand() / (float)(RAND_MAX)) * 10);
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 20) - (((float)rand() / (float)(RAND_MAX)) * 20);
	}
	wind_speed = speed_static;
	object_follow = nullptr;
	element_to_follow = nullptr;
	//
	dir_wind = dir;
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, iPoint(12, 2), iPoint(15, 5), speed, speed_static, 2, 4, true);
		particle.push_back(temp);
	}
}

P_Fire::~P_Fire()
{
}

bool P_Fire::Update(float dt)
{
	if (element_to_follow != nullptr && object_follow == nullptr)
	{
		pos.x = element_to_follow->position.x;
		pos.y = element_to_follow->position.y;
	}
	else if (element_to_follow == nullptr && object_follow != nullptr)
	{
		Update_position(object_follow);
	}
	else
	{
		//Nothing
	}

	MoveParticles();


	return true;
}

bool P_Fire::PostUpdate()
{
	render(pos);
	return true;
}

void P_Fire::render(fPoint pos)
{
	if (active)
	{
		//Check if the particle dead
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, iPoint(12, 2));
			}
		}
	}

	//Draw particles
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render(texture);
	}
}

void P_Fire::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		float temp = App->GetDT();
		particle[i]->Move(fPoint(speed.x * temp, speed.y * temp), dir_wind, wind_speed);
	}
}

void P_Fire::Update_position(iPoint* element)
{
	pos.x = element->x;
	pos.y = element->y;
}
