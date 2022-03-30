#ifndef SDLPrimitives_H
#define SDLPrimitives_H

#include <renderer/Renderer.h>

class SDLPrimitive
{
public:
	/// <summary>
	/// Draws a colored circle to the given SDL surface at the specified location and radius.
	/// </summary>
	static void FillCircle(SDL_Surface* surface, int x, int y, int radius, Uint32 color);
};

#endif//SDLPrimitives_H