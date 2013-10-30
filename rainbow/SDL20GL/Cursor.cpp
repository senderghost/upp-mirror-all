#include "Local.h"

#ifdef GUI_SDL20GL

NAMESPACE_UPP

#define LLOG(x)  LOG(x)
#define LDUMP(x) //DDUMP(x)

struct RectSDL {
	SDL_Rect sr;
	
	operator SDL_Rect *() { return &sr; }
	
	RectSDL(const Rect& r)
	{
		sr.x = r.left;
		sr.y = r.top;
		sr.w = r.GetWidth();
		sr.h = r.GetHeight();
	}
};

SDL_Texture *SDLTextureFromImage(SDL_Renderer *renderer, const Image& m)
{
	Size isz = m.GetSize();
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                                         SDL_TEXTUREACCESS_STATIC, isz.cx, isz.cy);
	if(texture) {
		SDL_UpdateTexture(texture, RectSDL(isz), ~m, isz.cx * sizeof(RGBA));
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}
	return texture;
}

SDL_Cursor  *sdl_cursor;
SDL_Surface *sdl_cursor_surface;
Buffer<RGBA> data;

void  Ctrl::SetMouseCursor(const Image& image)
{
	GuiLock __;
	if(image.GetSerialId() != fbCursorImage.GetSerialId()) {
		fbCursorImage = image;
		fbCursorPos = Null;
		SDL_ShowCursor(SystemCursor);
		if(SystemCursor) {
			if(sdl_cursor)
				SDL_FreeCursor(sdl_cursor);
			if(sdl_cursor_surface)
				SDL_FreeSurface(sdl_cursor_surface);
			
			int a = image.GetAuxData();
			if(a)
				sdl_cursor = SDL_CreateSystemCursor(SDL_SystemCursor(a - 1));
			else {
				sdl_cursor = NULL;
				data.Alloc(image.GetLength());
				Copy(data, image, image.GetLength());
				sdl_cursor_surface = SDL_CreateRGBSurfaceFrom(~data, image.GetWidth(), image.GetHeight(),
				                                              32, sizeof(RGBA) * image.GetWidth(),
				                                              0xff0000, 0xff00, 0xff, 0xff000000);
				Point h = image.GetHotSpot();
				if(sdl_cursor_surface)
					sdl_cursor = SDL_CreateColorCursor(sdl_cursor_surface, h.x, h.y);
			}
			if(sdl_cursor)
				SDL_SetCursor(sdl_cursor);
		}
	}
}

END_UPP_NAMESPACE

#endif