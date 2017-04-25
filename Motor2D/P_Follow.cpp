#include "P_Follow.h"
#include "Particle.h"
#include "j1Player.h"

P_Follow::P_Follow(SceneElement* element, iPoint area, iPoint timelife, SDL_Texture* texture_, int size_particle, int num_textures, int num_particles, bool active_)
{
	texture = texture_;
	pos.x = element->position.x;
	pos.y = element->position.y;
	//speed = speed_;

	object_follow = nullptr;
	element_to_follow = element;
	//
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos, area, timelife, fPoint(0,0), false, size_particle, num_textures, active_);
		particle.push_back(temp);
	}
}

P_Follow::P_Follow(iPoint* element, iPoint area, iPoint timelife, SDL_Texture* texture_, int size_particle, int num_textures, int num_particles, bool active_)
{
	texture = texture_;
	pos.x = element->x;
	pos.y = element->y;
	//speed = speed_;
	object_follow = element;
	element_to_follow = nullptr;
	//
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, area, timelife, fPoint(0, 0), false, size_particle, num_textures, active_);
		particle.push_back(temp);
	}
}

P_Follow::~P_Follow()
{
}

bool P_Follow::Update(float dt)
{
	if (element_to_follow != nullptr)
	{
		pos.x = element_to_follow->position.x;
		pos.y = element_to_follow->position.y;
	}
	else
	{
		Update_position(object_follow);
	}


	return true;
}

bool P_Follow::PostUpdate()
{
	render(pos);
	return true;
}

void P_Follow::render(fPoint pos)
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

void P_Follow::MoveParticles()
{
}

void P_Follow::Update_position(iPoint* element)
{
	pos.x = element->x;
	pos.y = element->y;
}
