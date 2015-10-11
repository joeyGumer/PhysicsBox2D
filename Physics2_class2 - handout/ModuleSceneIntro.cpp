#include "Globals.h"
#include "p2Defs.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("game/pinball/wheel.png"); 
	box = App->textures->Load("game/pinball/crate.png");
	rick = App->textures->Load("game/pinball/rick_head.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	p2List_item<PhysBody*>* c = circles.getFirst();
	while (c != NULL)
	{
		RELEASE(c->data)
			c = c->next;
	}
	circles.clear();
	
	c = boxes.getFirst();
	while (c != NULL)
	{
		RELEASE(c->data)
			c = c->next;
	}
	boxes.clear();

	c = ricks.getFirst();
	while (c != NULL)
	{
		RELEASE(c->data)
			c = c->next;
	}
	ricks.clear();

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseX(), 25, 2));	
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseX(), 50, 25, 2));
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		ricks.add(App->physics->CreateRick(App->input->GetMouseX(), App->input->GetMouseX(), 2));
	}
	// TODO 7: Draw all the circles using "circle" texture

	p2List_item<PhysBody*>* c = circles.getFirst();
	while (c != NULL)
	{
		int x, y;
		double angle = c->data->GetRotation();
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, angle);

		c = c->next;
	}

	c = boxes.getFirst();
	while (c != NULL)
	{
		int x, y;
		double angle = c->data->GetRotation();
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, angle);

		c = c->next;
	}

	c = ricks.getFirst();
	while (c != NULL)
	{
		int x, y;
		double angle = c->data->GetRotation();
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, angle);

		c = c->next;
	}


	return UPDATE_CONTINUE;
}
