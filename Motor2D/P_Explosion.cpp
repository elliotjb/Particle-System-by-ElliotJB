#include "P_Explosion.h"
#include "Particle.h"

P_Explosion::P_Explosion(SceneElement* element, SDL_Texture* texture_, Explosion_Type type, iPoint perimeter_object, iPoint timelife_particle, fPoint speed_particle, int num_particles, int size_particle, int num_textures)
{
	texture = texture_;
	pos.x = element->position.x;
	pos.y = element->position.y;
	speed = speed_particle;

	object_follow = nullptr;
	element_to_follow = element;
	//
	timelife = timelife_particle;
	number_particles = num_particles;
	godelete = false;


	int num_line = num_particles / 2;
	int space_x = (perimeter_object.x * 2) / num_line;
	int temp_x = -perimeter_object.x;
	int space_y = (perimeter_object.y * 2) / num_line;
	int temp_y = -perimeter_object.y;

	for (int i = 0; i < num_particles; i++)//
	{
		//Modify position 
		if (type == CIRCLE)
		{

		}
		else if (type == CROSS)
		{
			if (i < num_line)
			{
				pos.x += temp_x;
				Particle* temp = new Particle(pos, iPoint(0, 0), timelife, speed, true, size_particle, num_textures, true);
				particle.push_back(temp);
				temp_x += space_x;
			}
			else
			{
				pos.y += temp_y;
				Particle* temp = new Particle(pos, iPoint(0, 0), timelife, speed, true, size_particle, num_textures, true);
				particle.push_back(temp);
				temp_y += space_y;
			}

		}
		else
		{

		}
	}
}

P_Explosion::P_Explosion(iPoint* element, SDL_Texture* texture_, Explosion_Type type, iPoint perimeter_object, iPoint timelife_particle, fPoint speed_particle, int num_particles, int size_particle, int num_textures)
{
}

P_Explosion::P_Explosion(iPoint pos_object, SDL_Texture* texture_, Explosion_Type type, iPoint perimeter_object, iPoint timelife_particle, fPoint speed_particle, int num_particles, int size_particle, int num_textures)
{
	texture = texture_;
	pos.x = pos_object.x;
	pos.y = pos_object.y;
	speed = speed_particle;

	object_follow = nullptr;
	element_to_follow = nullptr;
	//
	timelife = timelife_particle;
	number_particles = num_particles;
	godelete = false;


	int num_line = num_particles / 2;
	int space_x = (perimeter_object.x * 2) / num_line * 2;
	int temp_x = -perimeter_object.x;
	int space_y = (perimeter_object.y * 2) / num_line;
	int temp_y = -perimeter_object.y;
	int mid_pos = pos.x;
	pos.x += temp_x;
	pos.y += temp_y;
	for (int i = 0; i < num_particles; i++)//
	{
		//Modify position 
		if (type == CIRCLE)
		{

		}
		else if (type == CROSS)
		{
			if (i < num_line)
			{
				Particle* temp = new Particle(pos, iPoint(0, 0), timelife, speed, true, size_particle, num_textures, true);
				particle.push_back(temp);
				pos.x += space_x;
			}
			else
			{
				pos.x = mid_pos;
				Particle* temp = new Particle(pos, iPoint(0, 0), timelife, speed, true, size_particle, num_textures, true);
				particle.push_back(temp);
				pos.y += space_y;
			}

		}
		else
		{

		}
	}
}

P_Explosion::~P_Explosion()
{
}

bool P_Explosion::Update(float dt)
{
	MoveParticles();

	return true;
}

bool P_Explosion::PostUpdate()
{
	render(pos);
	return true;
}

void P_Explosion::render(fPoint pos)
{
	//Check if the particle dead
	for (int i = 0; i < number_particles; i++)
	{
		if (particle[i]->isDead())
		{
			//delete
		}
	}

	//Draw particles
	for (int i = 0; i < number_particles; i++)
	{
		particle[i]->render(texture);
	}
}

void P_Explosion::MoveParticles()
{
	for (int i = 0; i < number_particles; i++)
	{
		float temp = App->GetDT();
		particle[i]->Move(fPoint(speed.x * temp, speed.y * temp));
	}
}
