#include "j1EntityElementsScene.h"
#include "Soldier.h"
#include "j1Item.h"
#include "j1Player.h"
#include "j1DynamicObjects.h"
#include "j1Scene.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1FileSystem.h"
#include "j1Weapon.h"


j1EntityElementScene::j1EntityElementScene()
{
	name = "entityelement";
}

j1EntityElementScene::~j1EntityElementScene()
{
}

bool j1EntityElementScene::Awake(pugi::xml_node &config)
{
	/*std::list<SceneElement*>::iterator item = elementscene.begin();
	while (item != elementscene.end())
	{

		item++;
	}*/
	file_tex_dynobjects = config.child("textDynObjects").attribute("file").as_string("");
	file_tex_trainer = config.child("textBrendan").attribute("file").as_string("");
	return true;
}

bool j1EntityElementScene::Start()
{
	bool ret = true;
	std::list<SceneElement*>::iterator item = elementscene.begin();
	while (item != elementscene.end())
	{
		//item._Ptr->_Myval->Start();
		item++;
	}
	
	texture_dynobjects = App->tex->Load(file_tex_dynobjects.c_str());
	texture_trainer = App->tex->Load(file_tex_trainer.c_str());

	char* buf;
	int size = App->fs->Load("config.xml", &buf);
	XML.load_buffer(buf, size);
	return ret;
}

bool j1EntityElementScene::PreUpdate()
{
	BROFILER_CATEGORY("DoUpdate_Elements", Profiler::Color::Cyan)

	return true;
}

bool j1EntityElementScene::Update(float dt)
{
	bool ret = true;
	BROFILER_CATEGORY("DoUpdate_Elements", Profiler::Color::Cyan);
	if (App->scene->combat == false)
	{
		std::list<SceneElement*>::iterator item3 = elementscene.begin();
		while (item3 != elementscene.end())
		{
			item3._Ptr->_Myval->Update(dt);
			item3++;
		}
	}

	return ret;
}

bool j1EntityElementScene::PostUpdate()
{
	BROFILER_CATEGORY("Draw_Elements", Profiler::Color::Green)
	if (App->scene->combat == false)
	{
		std::list<SceneElement*>::iterator item = elementscene.end();
		item--;
		while (item != elementscene.begin())
		{
			item._Ptr->_Myval->Draw();
			item--;
		}
		if (elementscene.size() > 0)
		{
			item._Ptr->_Myval->Draw();
		}
	}
	return true;
}

bool j1EntityElementScene::CleanUp()
{
	bool ret = true;
	std::list<SceneElement*>::iterator item = elementscene.begin();
	while (item != elementscene.end())
	{
		item._Ptr->_Myval->CleanUp();
		item++;
	}
	return ret;
}

bool j1EntityElementScene::DelteWeapons()
{
	std::list<SceneElement*>::iterator item = elementscene.end();
	item--;
	{
		while (item != elementscene.begin())
		{
			if (item._Ptr->_Myval->type == WEAPON)
			{
				delete item._Ptr->_Myval;
				elementscene.erase(item);
			}
			item--;
		}
	}
	return true;
}

bool j1EntityElementScene::DelteElements()
{
	App->collision->waittodelete = true;
	std::list<SceneElement*>::iterator item = elementscene.end();
	item--;
	if (elementscene.begin()._Ptr->_Myval->name != "Link")
	{
		std::list<SceneElement*>::iterator temp = elementscene.begin();
		while (temp != elementscene.end())
		{
			if (temp._Ptr->_Myval->name == "Link")
			{
				std::swap(temp._Ptr->_Myval, elementscene.begin()._Ptr->_Myval);
			}
			temp++;
		}
	}
	if (elementscene.size() > 1)
	{
		while (item != elementscene.begin())
		{
			if (item._Ptr->_Myval->type != WEAPON)
			{
				delete item._Ptr->_Myval;
				elementscene.erase(item);
			}
			item--;
		}
	}
	return true;
}

Soldier* j1EntityElementScene::CreateSoldier(uint id, pugi::xml_node& config)
{

	Soldier* element = new Soldier();
	element->Awake(config, id);
	element->Start();
	elementscene.push_back(element);

	return element;
}

bool j1EntityElementScene::DeleteEnemy(Soldier* enemy)
{
	if (enemy != nullptr)
	{
		elementscene.remove(enemy);
		App->scene->enemy.remove(enemy);
		enemy->collision_feet->to_delete = true;
		enemy = nullptr;
		delete enemy;
	}

	return true;
}

bool j1EntityElementScene::DeleteDynObject(DynamicObjects* dynobject)
{
	elementscene.remove(dynobject);
	App->scene->dynobjects.remove(dynobject);
	dynobject->collision->to_delete = true;
	dynobject = nullptr;
	delete dynobject;
	return true;
}

bool j1EntityElementScene::DeleteItem(Item* item)
{
	elementscene.remove(item);
	App->scene->items.remove(item);
	item->collision->to_delete = true;
	item = nullptr;
	delete item;
	return true;
}


Item* j1EntityElementScene::CreateItem(uint id, iPoint position)
{
	Item* element = new Item();
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = LoadConfig(config_file);
	element->Awake(config.child(element->name.c_str()), id, position);
	element->Start();
	elementscene.push_front(element);
	return element;
}

Hookshot* j1EntityElementScene::CreateHookshot()
{
	Hookshot* hook = new Hookshot(true);
	hook->name = "hookshot";
	hook->Start();
	elementscene.push_back(hook);
	return hook;
}

BombContainer* j1EntityElementScene::CreateBombContainer()
{
	BombContainer* element = new BombContainer();
	element->name = "bomb";
	elementscene.push_back(element);
	return element;
}

DynamicObjects* j1EntityElementScene::CreateDynObject(iPoint pos, uint id, uint id_map)
{
	DynamicObjects* element = new DynamicObjects();
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = LoadConfig(config_file);
	bool stop_rearch = false;
	LOG("Create DynObjects");
	config = config.child("maps").child("map");
	for (; stop_rearch == false; config = config.next_sibling())
	{
		if (config.attribute("n").as_int(0) == id_map)
		{
			element->Awake(config, id, pos);
			element->Start();
			if (id == 1 || id == 6 || id == 7 || id == 8)
			{
				elementscene.push_front(element);
			}
			else
				elementscene.push_back(element);
			LOG("Created!!");
			stop_rearch = true;
		}
	}


	return element;
}

Player* j1EntityElementScene::CreatePlayer()
{
	Player* element = new Player();
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = LoadConfig(config_file);
	element->Awake(config.child(element->name.c_str()));
	elementscene.push_back(element);
	element->Start();

	return element;
}

// ---------------------------------------------
pugi::xml_node j1EntityElementScene::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	char* buf;
	int size = App->fs->Load("Levels.xml", &buf);
	pugi::xml_parse_result result = config_file.load_buffer(buf, size);
	RELEASE(buf);

	if (result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("levels");

	return ret;
}