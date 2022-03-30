#include <memory>
#include <cmath>

#include <OkuLite.h>

/// <summary>
/// A spiral test object.
/// </summary>
class Spirals : public GameObject
{
public:
	/**
	 * \brief The spiral's color, represented in 0xRGBA notation.
	 */
	Uint32 color = 0xff0000ff; //0xRGBA

	double pos = 0;
	double spd = 140;

	void Draw(Renderer& renderer) override
	{
		// write pixels
		SDL_LockSurface(renderer.pixels);
		{
			const int pitch = renderer.pixels->pitch;

			// draw diagonal line
			for (int i = 0; i < DEFAULT_SCREEN_HEIGHT; i++)
			{
				const int y = i;
				for (int j = 0; j < 8; j++)
				{
					const int x = (static_cast<int>(pos) + i+j) % DEFAULT_SCREEN_WIDTH;

					const auto row = reinterpret_cast<Uint32*>(static_cast<char*>(renderer.pixels->pixels) + static_cast<ptrdiff_t>(pitch) * y);
					row[x] = color; //0xRGBA
				}
			}
		}
		SDL_UnlockSurface(renderer.pixels);
	}

	void Update(double delta) override
	{
		// move speed, in px/s
		pos += delta * spd;
		pos = std::fmod(pos, DEFAULT_SCREEN_WIDTH);

		if (Input::GetKeyPressed(K_RETURN))
			spd += 2000;
		else if (Input::GetKeyReleased(K_RETURN))
			spd -= 2000;
	}
};

class QuitObject : public GameObject
{
public:
	void Update(double delta) override
	{
		if (Input::GetKeyDown(K_LALT) && Input::GetKeyPressed(K_F4))
			OkuLite::Quit();
	}
};

/// <summary>
/// The primary entry point into the engine for Pong.
/// </summary>
/// <param name="argc">Size of provided argument list</param>
/// <param name="argv">List of arguments provided to the process during execution</param>
/// <returns>Process exit code</returns>
int main(int argc, char* argv[])
{
	if (!OkuLite::Init("Pong"))
		return 1;

	OLog::Info("Spawning spiral test GameObjects");

	auto spiral4 = std::make_shared<Spirals>();
	spiral4->pos = 200;
	spiral4->spd = 1200;
	spiral4->color = 0xce2954ff;
	OkuLite::goManager->AddGameObject(spiral4);

	auto quitObj = std::make_shared<QuitObject>();
	OkuLite::goManager->AddGameObject(quitObj);

	OLog::Info("Active!");

	// Pass off to engine loop
	const auto ret = OkuLite::Loop();

	return ret;
}