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
		// draw diagonal line
		for (int i = 0; i < OkuLite::renderer->ScreenHeight(); i++)
		{
			const int y = i;
			for (int j = 0; j < 8; j++)
			{
				const int x = (static_cast<int>(pos) + i+j) % OkuLite::renderer->ScreenWidth();

				const Uint8 _r = static_cast<Uint8>((color & 0xff000000) >> 24);
				const Uint8 _g = static_cast<Uint8>((color & 0x00ff0000) >> 16);
				const Uint8 _b = static_cast<Uint8>((color & 0x0000ff00) >> 8);
				const Uint8 _a = static_cast<Uint8>(color & 0x000000ff);
				SDL_SetRenderDrawColor(renderer.renderer, _r, _g, _b, _a);
				SDL_RenderDrawPoint(renderer.renderer, x, y);
			}
		}
	}

	void Update(double delta) override
	{
		// move speed, in px/s
		pos += delta * spd;
		pos = std::fmod(pos, OkuLite::renderer->ScreenWidth());

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
		rect.h = OkuLite::renderer->ScreenHeight() / 3;
	}

	void Update(double delta) override
	{
		if (Input::GetKeyDown(up_key))
			Move((int)(speed * delta));
		else if (Input::GetKeyDown(down_key))
			Move((int)(-speed * delta));
	}

	void Draw(Renderer& renderer) override
	{
		// add the position as an offset to the base transform (->local)
		SDL_Rect rect_transform = rect;
		rect_transform.x += x;
		rect_transform.y += y;
		SDL_SetRenderDrawColor(renderer.renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRect(renderer.renderer, &rect_transform);
	}
private:
	int x, y;
	double speed = 400;
	SDL_Rect rect;
	InputKey up_key, down_key;

	void Move(int vy)
	{
		auto dy = y - vy;
		if (dy < 0 || dy > OkuLite::renderer->ScreenHeight() - rect.h)
			return;
		y = dy;
	}
};

class Ball : public GameObject
{
public:
	Ball(int sx, int sy, int rad = 20, Uint32 col = 0xFFFFFFFF)
		: x(sx), y(sy), size(rad), color(col)
	{}

	void Update(double delta) override
	{

	}

	void Draw(Renderer& renderer) override
	{
		SDLPrimitive::FillCircle(renderer, x, y, size, color);
	}
private:
	int x, y;
	int size;
	double speed = 100;
	Uint32 color;
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

	auto paddle = std::make_shared<Paddle>(40, 120, K_W, K_S);
	OkuLite::goManager->AddGameObject(paddle);
	auto paddle2 = std::make_shared<Paddle>(OkuLite::renderer->ScreenWidth() - 80, 120, K_I, K_K);
	OkuLite::goManager->AddGameObject(paddle2);

	auto ball = std::make_shared<Ball>(OkuLite::renderer->ScreenWidth() / 2, OkuLite::renderer->ScreenHeight() / 2);
	OkuLite::goManager->AddGameObject(ball);

	OLog::Info("Active!");

	// Pass off to engine loop
	const auto ret = OkuLite::Loop();

	return ret;
}