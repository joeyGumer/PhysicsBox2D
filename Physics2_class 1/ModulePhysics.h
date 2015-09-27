#pragma once
#include "Module.h"
#include "Globals.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y 10.0f

#define PROPORTION 30
#define METERS_TO_PIXELS(m) ((int) m*30)
#define PIXELS_TO_METERS(p) ((float) p/30)

class b2World;

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	//tools to create objects
	bool CreateStaticCircle(int x, int y, int radius);
	bool CreateDynamicCircle(int x, int y, int radius);

private:

	bool debug;
	b2World* world;

};

