#ifndef _JetStory_jetstory_h_
#define _JetStory_jetstory_h_

#include <CtrlLib/CtrlLib.h>

#define IMAGECLASS MapImg
#define IMAGEFILE <JetStory/map.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS JetStoryImg
#define IMAGEFILE <JetStory/jetstory.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS BlocksImg
#define IMAGEFILE <JetStory/Blocks.iml>
#include <Draw/iml_header.h>

using namespace Upp;

void ImportMap();

enum { MAPX = 128, MAPY = 40, BLOCKSIZE = 32 };

extern int jetstory[MAPY][MAPX];



#endif
