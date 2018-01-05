#include "jetstory.h"

void ImportMap() {
//	Index<Image> blocks;
//	for(int i = 0; i < BlocksImg::GetCount(); i++) {
//		Image m = BlocksImg::Get(i);
//		for(int j = 0; j < 4; j++)
//			blocks.Add(Crop(m, 0, j * 8, 32, 8));
//	}
	

	Image map = StreamRaster::LoadFileAny("c:/u/jetstory/map.png");
	for(int y = 0; y < MAPY; y++) {
		String ln;
		for(int x = 0; x < MAPX; x++) {
			Image m = Crop(map, x * 32, y * 32, 32, 32);
			int qq = 0;
			int maxx = 0;
			for(int i = 0; i < BlocksImg::GetCount(); i++) {
				int nn = 0;
			#if 1
				Image mm = BlocksImg::Get(i);
				const RGBA *a = ~m;
				const RGBA *b = ~mm;
				for(int i = 0; i < 32 * 32; i++)
					if(a[i] == b[i])
						nn++;
			#else
				for(int j = 0; j < 4; j++) {
					if(blocks[4 * i + j] == Crop(m, 0, j * 8, 32, 8))
						nn++;
				}
			#endif
				if(nn > maxx) {
					qq = i;
					maxx = nn;
				}
			}
			jetstory[y][x] = qq;
			if(x)
				ln << ", ";
			ln << qq;
		}
		RLOG("{ " << ln << " },");
	}
/*
	String blocks = "c:/u/jetstory/blocks";
	DeleteFolderDeep(blocks);
	
	RealizeDirectory(blocks);
	Image null = CreateImage(Size(8, 8), Null);
	for(int i = 0; i < img.GetCount(); i++)
		PNGEncoder().SaveFile(AppendFileName(blocks, Format("B%04d.png", i)), img.GetKey(i));
	PromptOK("Done");
*/
}

void BlockMap()
{
//	DDUMP(RGBAZero());
	RGBA black = Black();
//	DDUMP(black);
	for(int i = 0; i < BlocksImg::GetCount(); i++) {
		Image mm = BlocksImg::Get(i);
		for(int x = 0; x < 32; x++)
			for(int y = 0; y < 32; y++) {
				if(mm[y][x] != black && mm[y][x].a)
					blockmap[i][y / 8][x / 8] = true;
			}
	}
}