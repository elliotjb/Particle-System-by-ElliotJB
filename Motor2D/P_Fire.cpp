#include "P_Fire.h"
#include "Particle.h"
#include "j1Window.h"

P_Fire::P_Fire(SceneElement* element, SDL_Texture* texture_, iPoint area_, iPoint timelife_, fPoint speed_particle, bool speed_static, int num_particles, int size_particle, int num_textures, bool active_, Wind dir)
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
		speed.y = speed_particle.y;
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 60) - (((float)rand() / (float)(RAND_MAX)) * 60);
	}
	if (dir != W_NON)
		wind_speed = true;
	else
		wind_speed = false;

	object_follow = nullptr;
	element_to_follow = element;
	//
	area = area_;
	timelife = timelife_;
	dir_wind = dir;
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos, area, timelife, speed, speed_static, size_particle, num_textures, true);
		particle.push_back(temp);
	}
}

P_Fire::P_Fire(iPoint* element, SDL_Texture* texture_, iPoint area_, iPoint timelife_, fPoint speed_particle, bool speed_static, int num_particles, int size_particle, int num_textures, bool active_, Wind dir)
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
		speed.y = speed_particle.y;
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 60) - (((float)rand() / (float)(RAND_MAX)) * 60);
	}
	if (dir != W_NON)
		wind_speed = true;
	else
		wind_speed = false;
	object_follow = element;
	element_to_follow = nullptr;
	//
	area = area_;
	timelife = timelife_;
	dir_wind = dir;
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, area, timelife, speed, speed_static, size_particle, num_textures, true);
		particle.push_back(temp);
	}
}

P_Fire::P_Fire(iPoint position, SDL_Texture* texture_, iPoint area_, iPoint timelife_, fPoint speed_particle, bool speed_static, int num_particles, int size_particle, int num_textures, bool active_, Wind dir)
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
		speed.y = speed_particle.y;
		speed.x = (((float)rand() / (float)(RAND_MAX)) * 60) - (((float)rand() / (float)(RAND_MAX)) * 60);
	}
	if (dir != W_NON)
		wind_speed = true;
	else
		wind_speed = false;
	object_follow = nullptr;
	element_to_follow = nullptr;
	//
	area = area_;
	timelife = timelife_;
	dir_wind = dir;
	number_particles = num_particles;
	cont_active_firework = 0;
	godelete = false;
	active = active_;
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, area, timelife, speed, speed_static, size_particle, num_textures, true);
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
				particle[i]->Modify(pos, area, timelife);
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
	pos.x = element->x - App->render->camera.x / App->win->GetScale();
	int scale = App->win->GetScale();
	int temp = App->render->camera.y / scale;
	pos.y = element->y - temp;
}
