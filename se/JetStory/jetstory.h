#ifndef _JetStory_jetstory_h_
#define _JetStory_jetstory_h_

#include <CtrlLib/CtrlLib.h>

#define IMAGECLASS JetStoryImg
#define IMAGEFILE <JetStory/JetStory.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS BlocksImg
#define IMAGEFILE <JetStory/Blocks.iml>
#include <Draw/iml_header.h>

using namespace Upp;

void ImportMap();

void BlockMap();

enum { MAPX = 128, MAPY = 40, BLOCKSIZE = 32 };

extern int jetstory[MAPY][MAPX];

extern bool blockmap[64][4][4];

void InitSound();

#endif
