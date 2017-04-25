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



	for (int i = 0; i < num_particles; i++)//
	{
		//Modify position 
		if (type == CIRCLE)
		{

		}
		else if (type == CROSS)
		{

		}
		else
		{

		}


		Particle* temp = new Particle(pos, iPoint(0,0), timelife, speed, true, size_particle, num_textures, true);
		particle.push_back(temp);
	}
}

P_Explosion::P_Explosion(iPoint* element, SDL_Texture* texture_, Explosion_Type type, iPoint perimeter, iPoint timelife_particle, fPoint speed, int num_particles, int size_particle, int num_textures)
{
}

P_Explosion::P_Explosion(iPoint pos, SDL_Texture* texture_, Explosion_Type type, iPoint perimeter, iPoint timelife_particle, fPoint speed, int num_particles, int size_particle, int num_textures)
{
}

P_Explosion::~P_Explosion()
{
}

bool P_Explosion::Update(float dt)
{
	return false;
}

bool P_Explosion::PostUpdate()
{
	return false;
}

void P_Explosion::render(fPoint pos)
{
}

void P_Explosion::Update_position(iPoint * pos)
{
}

void P_Explosion::MoveParticles()
{
}
