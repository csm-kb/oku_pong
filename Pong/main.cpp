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

class Paddle : public GameObject
{
public:
	Paddle(int sx, int sy, InputKey upKey = K_UP, InputKey downKey = K_DOWN)
		: x(sx), y(sy), up_key(upKey), down_key(downKey)
	{
		rect.x = 0;
		rect.y = 0;
		rect.w = 40;
		rect.h = DEFAULT_SCREEN_HEIGHT / 3;
	}

	void Update(double delta) override
	{
		double vy = 0;
		if (Input::GetKeyDown(up_key)) vy = speed;
		if (Input::GetKeyDown(down_key)) vy = -speed;
		Move(vy * delta);
	}

	void Draw(Renderer& renderer) override
	{
		SDL_Rect rect_transform = rect;
		rect_transform.x += x;
		rect_transform.y += y;
		SDL_FillRect(renderer.pixels, &rect_transform, SDL_MapRGBA(renderer.pixels->format, 255, 255, 255, 255));

	}
private:
	int x, y;
	double speed = 400;
	SDL_Rect rect;
	InputKey up_key, down_key;

	void Move(double vy)
	{
		auto dy = y - vy;
		if (dy < 0 || dy > DEFAULT_SCREEN_HEIGHT - rect.h)
			return;
		y = dy;
	}
};

class Ball : public GameObject
{
public:
	void Update(double delta) override
	{

	}

	void Draw(Renderer& renderer) override
	{

	}
private:
	int x, y;
	double speed = 100;
	
};

class QuitObject : public GameObject
{
public:
	void Update(double delta) override
	{
		if (Input::GetKeyDown(K_LALT) && Input::GetKeyPressed(K_F4))
			OkuLite::Quit();
		else if (Input::GetKeyDown(K_Q))
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

	auto spiral1 = std::make_shared<Spirals>();
	spiral1->pos = 800;
	spiral1->spd = 100;
	spiral1->color = 0xff0000ff;
	OkuLite::goManager->AddGameObject(spiral1);

	auto spiral2 = std::make_shared<Spirals>();
	spiral2->pos = 600;
	spiral2->spd = 300;
	spiral2->color = 0x00ff00ff;
	OkuLite::goManager->AddGameObject(spiral2);

	auto spiral3 = std::make_shared<Spirals>();
	spiral3->pos = 400;
	spiral3->spd = 500;
	spiral3->color = 0x0000ffff;
	OkuLite::goManager->AddGameObject(spiral3);

	auto spiral4 = std::make_shared<Spirals>();
	spiral4->pos = 200;
	spiral4->spd = 700;
	spiral4->color = 0xce2954ff;
	OkuLite::goManager->AddGameObject(spiral4);

	auto quitObj = std::make_shared<QuitObject>();
	OkuLite::goManager->AddGameObject(quitObj);

	auto paddle = std::make_shared<Paddle>(40, 120);
	OkuLite::goManager->AddGameObject(paddle);
	auto paddle2 = std::make_shared<Paddle>(DEFAULT_SCREEN_WIDTH - 80, 120, K_I, K_K);
	OkuLite::goManager->AddGameObject(paddle2);

	OLog::Info("Active!");

	// Pass off to engine loop
	const auto ret = OkuLite::Loop();

	return ret;
}