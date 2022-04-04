#ifndef SDLPrimitives_H
#define SDLPrimitives_H

#include <renderer/Renderer.h>

class SDLPrimitive
{
public:
	/// <summary>
	/// Draws a hollow colored circle at the specified location and radius.
	/// </summary>
	static void DrawCircle(Renderer& renderer, int x, int y, int radius, Uint32 color);

	/// <summary>
	/// Draws a filled colored circle at the specified location and radius.
	/// </summary>
	static void FillCircle(Renderer& renderer, int x, int y, int radius, Uint32 color);
};

#endif//SDLPrimitives_H