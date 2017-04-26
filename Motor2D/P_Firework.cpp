#include "P_Firework.h"
#include "Particle.h"

P_Firework::P_Firework(SceneElement* element, SDL_Texture* texture_, iPoint area_, iPoint timelife_, fPoint speed_particle, P_Direction p_direction, int num_particles, int num_textures, bool active_, Wind dir)
{
	texture = texture_;
	pos.x = element->position.x;
	pos.y = element->position.y;
	speed = speed_particle;

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
	n_textures = num_textures;
	size_rect = App->tex->GetHeight(texture_);
	for (int i = 0; i < num_particles; i++)//
	{
		Particle* temp = new Particle(pos, area, timelife, speed, p_direction, size_rect, n_textures, true);
		particle.push_back(temp);
	}


}

P_Firework::P_Firework(iPoint* element, SDL_Texture* texture_, iPoint area_, iPoint timelife_, fPoint speed_particle, P_Direction p_direction, int num_particles, int num_textures, bool active_, Wind dir)
{

	texture = texture_;
	pos.x = element->x;
	pos.y = element->y;

	speed = speed_particle;

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
	n_textures = num_textures;
	size_rect = App->tex->GetHeight(texture_);
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, area, timelife, speed, p_direction, size_rect, n_textures, true);
		particle.push_back(temp);
	}

}

P_Firework::P_Firework(iPoint position, SDL_Texture* texture_, iPoint area_, iPoint timelife_, fPoint speed_particle, P_Direction p_direction, int num_particles, int num_textures, bool active_, Wind dir)
{
	texture = texture_;
	pos.x = position.x;
	pos.y = position.y;
	speed = speed_particle;

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
	n_textures = num_textures;
	size_rect = App->tex->GetHeight(texture_);
	for (int i = 0; i < num_particles; i++)
	{
		Particle* temp = new Particle(pos, area, timelife, speed, p_direction, size_rect, n_textures, true);
		particle.push_back(temp);
	}


}

P_Firework::~P_Firework()
{



}

bool P_Firework::Update(float dt)
{

	MoveParticles();


	return true;
}

bool P_Firework::PostUpdate()
{
	render(pos);
	return true;
}

void P_Firework::render(fPoint pos)
{
	if (active)
	{
		//Check if the particle dead
		for (int i = 0; i < number_particles; i++)
		{
			if (particle[i]->isDead())
			{
				particle[i]->Modify(pos, area, timelife, iPoint(0, n_textures));
			}
		}
	}

	//Draw particles
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render(texture);
	}
}

void P_Firework::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		float temp = App->GetDT();
		particle[i]->Move(fPoint(particle[i]->GetSpeed().x * temp, particle[i]->GetSpeed().y * temp), dir_wind, wind_speed);
	}
}
