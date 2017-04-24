#include "ParticleManager.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Player.h"
#include "j1Audio.h"
#include "j1Timer.h"

Particle::Particle(int x, int y, int size, TypeMoviment type, fPoint speed_particle, bool isActive)
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
	else if (type == FIREWORK)
	{
		//with random change position
		position.x = x - (rand() % 12) + (rand() % 10);
		position.y = y;

		//Inicialitzed with random the timelife of the particle
		timelife = rand() % 12;
		speed.y = -10;
		//Set SDL_Rect
		switch (rand() % 4)
		{
		case 0: rect = { 0,0,size,size }; break;
		case 1: rect = { size,0,size,size }; break;
		case 2: rect = { size * 2,0,size,size }; break;
		case 3: rect = { size * 3,0,size,size }; break;
		}
		degrade.y = 255;
		degrade.x = 2;
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
	else if (type == FIREWORK)
	{
		speed.y += -speed_set.y;
		position.y += speed.y;
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

ParticleGroup::ParticleGroup(TypeMoviment type_, SDL_Texture* texture_, fPoint pos_, fPoint speed_, int size, int num_particles, bool active_)
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

	gravity = -9.8;

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
					/*delete particle[i];
					particle[i] = new Particle(pos.x, pos.y, size_rect, type);*/
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
	if (type == FIRE_VERTICAL || type == FIRE_LATERAL || type == FIREWORK)
	{
		if (active)
		{
			//Check if the particle dead
			for (int i = 0; i < number_particles; i++)
			{
				if (particle[i]->isDead())
				{
					/*delete particle[i];
					particle[i] = new Particle(pos.x, pos.y, size_rect, type);*/
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
		particle[i]->Move(fPoint(speed.x * App->GetDT(), speed.y * App->GetDT()), type);
	}
}

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
	texture.push_back(App->tex->Load("Particles/pixel_test_1.png"));

	//Add a metod particleGroup with type == Follow
	Group.push_back(ParticleGroup(FOLLOW, texture[0], fPoint(App->scene->player->position.x, App->scene->player->position.y), fPoint(0,0), App->tex->GetHeight(texture[0]), 90));
	//lamp
	Group.push_back(ParticleGroup(FIRE_VERTICAL, texture[1], fPoint(327, 246), fPoint(0, -60), App->tex->GetHeight(texture[1]), 80));

	Group.push_back(ParticleGroup(FIRE_VERTICAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y), fPoint(0, -100), App->tex->GetHeight(texture[1]), 80));
	Group.push_back(ParticleGroup(FIRE_LATERAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y - 8), fPoint(100, -30), App->tex->GetHeight(texture[1]), 65));
	Group.push_back(ParticleGroup(FIRE_VERTICAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y), fPoint(0, 100), App->tex->GetHeight(texture[1]), 80));
	Group.push_back(ParticleGroup(FIRE_LATERAL, texture[1], fPoint(App->scene->player->position.x, App->scene->player->position.y - 8), fPoint(-100, -30), App->tex->GetHeight(texture[1]), 65));

	Group.push_back(ParticleGroup(FIREWORK, texture[1], fPoint(250, 200), fPoint(0, -2), App->tex->GetHeight(texture[1]), 20));

	Group[1].active = true;
	return true;
}

bool ParticleManager::PreUpdate()
{
	return true;
}

bool ParticleManager::Update(float dt)
{
	for (int i = 0; i < Group.size(); i++)
	{
		switch (Group[i].type)
		{
		case FOLLOW:
		{
			//Update------
			break;
		}
		case FIRE_VERTICAL:
		{
			Group[i].MoveParticles();
			break;
		}
		case FIRE_LATERAL:
		{
			Group[i].MoveParticles();
			break;
		}
		case EXPLISION:
		{
			//Update------
			break;
		}
		case FIREWORK:
		{
			Group[i].MoveParticles();
			break;
		}
		}
	}

	return true;
}

bool ParticleManager::PostUpdate()
{
	/*for (int i = 0; i < Group.size(); i++)
	{
		Group[i].render(App->scene->player->position, Group[i].speed);
	}
	if (Group[0].active == true)
	{
		Group[0].render(App->scene->player->position, Group[0].speed);
	}
	if (Group[1].active == true)
	{
		Group[1].render(Group[1].pos, Group[1].speed);
	}*/

	Group[0].render(fPoint(App->scene->player->position.x, App->scene->player->position.y), Group[0].speed);
	Group[2].render(fPoint(App->scene->player->position.x, App->scene->player->position.y - 14), Group[2].speed);
	Group[3].render(fPoint(App->scene->player->position.x + 8, App->scene->player->position.y - 8), Group[3].speed);
	Group[4].render(fPoint(App->scene->player->position.x, App->scene->player->position.y - 8), Group[4].speed);
	Group[5].render(fPoint(App->scene->player->position.x - 8, App->scene->player->position.y - 8), Group[5].speed);
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
	{
		App->audio->PlayFx(1);
		Group[2].active = false;
		Group[3].active = false;
		Group[4].active = false;
		Group[5].active = false;
		if (App->scene->player->direction == UP)
		{
			Group[2].active = true;
		}
		else if (App->scene->player->direction == RIGHT)
		{
			Group[3].active = true;
		}
		else if (App->scene->player->direction == DOWN)
		{
			Group[4].active = true;
		}
		else if (App->scene->player->direction == LEFT)
		{
			Group[5].active = true;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_UP)
	{
		App->audio->StopFx(1);
		Group[2].active = false;
		Group[3].active = false;
		Group[4].active = false;
		Group[5].active = false;

	}
	Group[6].active = true;
	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
	{
		Group[6].active = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_G) == KEY_UP)
	{
		Group[6].active = false;
	}

	//FireWork
	Group[6].render(fPoint(250, 200), Group[6].speed);


	Group[1].render(Group[1].pos, Group[1].speed);

	return true;
}

bool ParticleManager::CleanUp()
{
	return true;
}


