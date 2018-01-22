#ifndef _JetStory_jetstory_h_
#define _JetStory_jetstory_h_

#include <CtrlLib/CtrlLib.h>

#define IMAGECLASS JetStoryImg
#define IMAGEFILE <JetStory/JetStory.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS BlocksImg
#define IMAGEFILE <JetStory/Blocks.iml>
#include <Draw/iml_header.h>

#include <Synth/Synth.h>

using namespace Upp;

void ImportMap();

void BlockMap();

enum { MAPX = 128, MAPY = 40, BLOCKSIZE = 64 };

extern int jetstory[MAPY][MAPX];

extern bool blockmap[64][4][4];

void InitSound();

struct Object {
	Pointf pos;
	Pointf speed = Pointf(0, 0);
	Pointf map_collision;
	
	bool Move(Size sz, Pointf bounce, Pointf friction, double gravity = 0.01);
	bool Move(Size sz, double bounce, double friction = 0.997, double gravity = 0.01);
};

struct Ship : Object {
	bool left;
};

struct Missile : Object {
	int    kind = 0;
	double accelx = 0;
	int    damage = 1;
	bool   left;
	int    sound_id = 0;
	
	~Missile() { StopSound(sound_id); }
};

#endif
