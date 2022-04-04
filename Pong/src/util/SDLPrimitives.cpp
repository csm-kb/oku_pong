#include <util/SDLPrimitives.h>

/// <summary>
/// Draws eight points per draw. v1 -- for v2, build list of SDL_Points and make one draw call
/// </summary>
void _BresenhamDraw(Renderer& renderer, int x, int y, int xc, int yc, Uint32 color)
{
	const int xs[] = { x + xc,x + xc,x - xc,x - xc,x + yc,x + yc,x - yc,x - yc };
	const int ys[] = { y + yc,y - yc,y + yc,y - yc,y + xc,y - xc,y + xc,y - xc };

	int sw, sh;
	sw = renderer.ScreenWidth();
	sh = renderer.ScreenHeight();

	int p_size = 0;
	SDL_Point points[8];
	for (auto i = 0; i < 8; i++) {
		if (xs[i] >= sw || xs[i] < 0 || ys[i] >= sh || ys[i] < 0)
			continue;
		points[p_size++] = { xs[i], ys[i] };
	}
	const Uint8 _r = (color & 0xff000000) >> 24;
	const Uint8 _g = (color & 0x00ff0000) >> 16;
	const Uint8 _b = (color & 0x0000ff00) >> 8;
	const Uint8 _a = (color & 0x000000ff);
	SDL_SetRenderDrawColor(renderer.renderer, _r, _g, _b, _a);
	SDL_RenderDrawPoints(renderer.renderer, points, p_size);
}

void SDLPrimitive::DrawCircle(Renderer& renderer, int x, int y, int radius, Uint32 color)
{
	int locX = 0, locY = radius;

	int d = 3 - 2 * radius;
	_BresenhamDraw(renderer, x, y, locX, locY, color);
	while (locY >= locX)
	{
		locX++;
		if (d > 0)
		{
			locY--;
			d = d + 4 * (locX - locY) + 10;
		}
		else
			d = d + 4 * locX + 6;
		_BresenhamDraw(renderer, x, y, locX, locY, color);
	}
}

void SDLPrimitive::FillCircle(Renderer& renderer, int x, int y, int radius, Uint32 color)
{
	int offsetx, offsety, d;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx) {

		SDL_RenderDrawLine(renderer.renderer, x - offsety, y + offsetx,
			x + offsety, y + offsetx);
		SDL_RenderDrawLine(renderer.renderer, x - offsetx, y + offsety,
			x + offsetx, y + offsety);
		SDL_RenderDrawLine(renderer.renderer, x - offsetx, y - offsety,
			x + offsetx, y - offsety);
		SDL_RenderDrawLine(renderer.renderer, x - offsety, y - offsetx,
			x + offsety, y - offsetx);

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}