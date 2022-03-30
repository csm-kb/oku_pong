#include <util/SDLPrimitives.h>

void SDLPrimitive::FillCircle(SDL_Surface* surface, int x, int y, int radius, Uint32 color)
{
	SDL_LockSurface(surface);
	{
		const int pitch = surface->pitch;

		// draw diagonal line
		for (int i = 0; i < DEFAULT_SCREEN_HEIGHT; i++)
		{
			const int y = i;
			for (int j = 0; j < 8; j++)
			{
				const int x = (x + i + j) % DEFAULT_SCREEN_WIDTH;

				const auto row = reinterpret_cast<Uint32*>(static_cast<char*>(surface->pixels) + static_cast<ptrdiff_t>(pitch) * y);
				row[x] = color; //0xRGBA
			}
		}
	}
	SDL_UnlockSurface(surface);
}