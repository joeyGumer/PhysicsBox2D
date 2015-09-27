#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

// TODO 1: Include Box 2 header and library
#include "Box2D/Box2D/Box2D.h"
#pragma comment (lib,"Box2D/libx86/Debug/Box2D.lib")

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);

	world = new b2World(gravity);

	// TODO 4: Create a a big static circle as "ground"
	//body definition
	//don't understand why we need the PIXELS_TO_METERS, transformation because Box2D will have it's own proportions pixels/meters
	//int x = 100;//10 meters
	//int y = 100;//10 meters
	//int radius = 60;//2 meters
	
	CreateStaticCircle(100, 100, 60);
	CreateDynamicCircle(600, 100, 60);
	//definition of the body
	/*b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(PIXELS_TO_METERS(x), PIXELS_TO_METERS(x));
			b2Body* groundCircleBody = world->CreateBody(&groundBodyDef);		b2CircleShape shape;	shape.m_radius = PIXELS_TO_METERS(radius);	b2FixtureDef fixture;
	fixture.shape = &shape;
	groundCircleBody->CreateFixture(&fixture);*/

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	// TODO 3: Update the simulation ("step" the world)
	world->Step(timeStep, velocityIterations, positionIterations);
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		int radius = 30;
		int x = App->input->GetMouseX();
		int y = App->input->GetMouseY();
		
		CreateDynamicCircle(x, y, radius);
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}
/*
   Creating functions------------------------------------
*/
//Circles
bool ModulePhysics::CreateStaticCircle(int x, int y, int radius)
{
	
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(PIXELS_TO_METERS(x), PIXELS_TO_METERS(y));
		b2Body* groundCircleBody = world->CreateBody(&groundBodyDef);		b2CircleShape shape;	shape.m_radius = PIXELS_TO_METERS(radius);		b2FixtureDef fixture;
	fixture.shape = &shape;
	groundCircleBody->CreateFixture(&fixture);

	return true;
}

bool ModulePhysics::CreateDynamicCircle(int x, int y, int radius)
{
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_dynamicBody;
	groundBodyDef.position.Set(PIXELS_TO_METERS(x), PIXELS_TO_METERS(y));
	b2Body* groundCircleBody = world->CreateBody(&groundBodyDef);	b2CircleShape shape;	shape.m_radius = PIXELS_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1;
	groundCircleBody->CreateFixture(&fixture);

	return true;
}