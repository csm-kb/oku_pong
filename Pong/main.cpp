#include <memory>
#include <cmath>
#include <string>
#include <array>

#include <sstream>
#include <filesystem>

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
	int x, y;
	double speed = 8;
	SDL_Rect rect;

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
			Move((int)(speed * 100 * delta));
		else if (Input::GetKeyDown(down_key))
			Move((int)(-speed * 100 * delta));
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
	InputKey up_key, down_key;

	void Move(int vy)
	{
		auto dy = y - vy;
		if (dy < 0 || dy > OkuLite::renderer->ScreenHeight() - rect.h)
			return;
		y = dy;
	}
};

class ScoreKeeper : public GameObject
{
public:
	ScoreKeeper()
	{
		font = TTF_OpenFont(fontName, 144);
		if (!font) {
			OLog::Error((std::string("Could not create font: ") + std::string(TTF_GetError())).c_str(), "[ScoreKeeper]");
			exit(1);
		}

		color = { 255, 255, 255 };

		int width = 140;
		rect.x = (OkuLite::renderer->ScreenWidth()/2)-(width/2);  //controls the rect's x coordinate 
		rect.y = 40; // controls the rect's y coordinte
		rect.w = width; // controls the width of the rect
		rect.h = 80; // controls the height of the rect

		int winW = 800, winH = 150;
		winRect.x = (OkuLite::renderer->ScreenWidth() / 2) - (winW / 2);
		winRect.y = (OkuLite::renderer->ScreenHeight() / 2) - (winH / 2);
		winRect.w = winW;
		winRect.h = winH;
	}

	void Update(double delta) override
	{}

	void Draw(Renderer& renderer) override
	{
		// must generate SDL_Surface first
		SDL_Surface* surfaceMessage =
			TTF_RenderText_Solid(
				font,
				(std::to_string(scores[0]) + std::string(" : ") + std::to_string(scores[1])).c_str(),
				color);

		// then we can convert it to an SDL_Texture for rendering
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer.renderer, surfaceMessage);
		// ... then render it ...
		SDL_RenderCopy(renderer.renderer, message, NULL, &rect);
		// ... then free intermediate resources
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);

		if (showPlayerWin) {
			surfaceMessage =
				TTF_RenderText_Solid(
					font,
					(std::string("Player ") + std::to_string(whoWon+1) + std::string(" wins!")).c_str(),
					color);

			message = SDL_CreateTextureFromSurface(renderer.renderer, surfaceMessage);
			SDL_RenderCopy(renderer.renderer, message, NULL, &winRect);
			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(message);
		}
	}

	/// <summary>
	/// Increases the score of player 0 or 1.
	/// </summary>
	void IncrementScore(int whom)
	{
		if (whom != 0 && whom != 1) return;
		scores[whom]++;
	}

	/// <summary>
	/// Resets the scores of both players to 0.
	/// </summary>
	void ResetScores()
	{
		scores[0] = 0; scores[1] = 0;
	}

	/// <summary>
	/// Sets the winning player and shows who won.
	/// </summary>
	void ShowPlayerWin(int winPlayer) {
		whoWon = winPlayer;
		showPlayerWin = true;
	}
	/// <summary>
	/// Hides the winning player dialog.
	/// </summary>
	void HidePlayerWin() {
		whoWon = -1;
		showPlayerWin = false;
		ResetScores();
	}

	/// <summary>
	/// Returns the current scores of both players.
	/// </summary>
	std::array<int,2> GetScores() {
		return std::array<int, 2>{scores[0], scores[1]};
	}
private:
	int scores[2] = { 0,0 };
	SDL_Rect rect;
	SDL_Color color;
	TTF_Font* font;
	const char* const fontName = "fonts/Lato-Light.ttf";

	bool showPlayerWin = false;
	int whoWon = -1;
	SDL_Rect winRect;
};

class Ball : public GameObject
{
public:
	double x, y;
	int radius;
	double speed = 1;
	double angle = 0;
	Uint32 color;
	std::shared_ptr<Paddle> paddleA, paddleB;
	double respawnTimer = -1;
	bool toRespawn = false;

	Ball(ScoreKeeper& sk, int sx, int sy, int rad = 20, Uint32 col = 0xFFFFFFFF)
		: scoreKeeper(sk), x(sx), y(sy), radius(rad), color(col)
	{}

	void Update(double delta) override
	{
		// first, check outside horizontal bounds
		if (x + radius < 0) {
			// left side
			if (!toRespawn) {
				// hide ball and begin respawn
				_StartRespawn();
				scoreKeeper.IncrementScore(1); // right side scored
				_CheckPlayerWin();
				return;
			}
			else {
				respawnTimer -= delta;
				if (respawnTimer < 0) {
					// respawn is complete, set for next round
					_EndRespawn();
					// serve goes to left
					angle = M_PI;
				}
				return;
			}
		}
		else if (x - radius > OkuLite::renderer->ScreenWidth()) {
			// right side
			if (!toRespawn) {
				// hide ball and begin respawn
				_StartRespawn();
				scoreKeeper.IncrementScore(0); // left side scored
				_CheckPlayerWin();
				return;
			}
			else {
				respawnTimer -= delta;
				if (respawnTimer < 0) {
					// respawn is complete, set for next round
					_EndRespawn();
					// serve goes to right
					angle = 0;
				}
				return;
			}
		}

		double vspeed = speed * 100 * delta;
		double vx = vspeed * cos(angle);
		double vy = vspeed * sin(angle);
		const auto paddles = { paddleA, paddleB };

		for (std::shared_ptr<Paddle> paddle : paddles) {
			if (paddle == nullptr) continue;
			if (_CheckCollision(*paddle, vx, vy)) {
				// calculate deflection angle
				if (vx > 0) {
					// right->left
					angle = -(M_PI + maxBounceAngle * ((y - paddle->y) / paddle->rect.h) - (maxBounceAngle / 2));
				}
				else {
					// left->right
					angle = maxBounceAngle * ((y - paddle->y) / paddle->rect.h) - (maxBounceAngle / 2);
				}
				vx = -vx; // keep it from being irrecoverable this frame
			}
		}

		// vertical bounce collision
		// = 2*(dot(normalVec,incidenceVec))*(normalVec-incidenceVec);
		// note that 0 degrees is right, 90 is down, 180 is left, and so on
		double dy = y + vy;
		if (dy - radius < 0) {
			// top bounce -- angle is positive [pi,2pi] (left,right)
			//if (vx > 0) // rightwards (angle [1.5pi,2pi])
			//	angle = halfPi - (angle-(3*M_PI/2));
			//else // leftwards (angle [pi,1.5pi])
				angle = halfPi - (angle-(3*M_PI/2)); //av should be in range [-pi/2,pi/2]
			angle = (angle - twoPi * floor(angle / twoPi)); // wrap to stay in [0,2pi]
			vy = -vy;
		}
		else if (dy + radius > OkuLite::renderer->ScreenHeight()) {
			// bottom bounce -- angle is positive [0,pi] (right,left)
			if (vx > 0) // rightwards
				angle = (3*M_PI/2) - (angle-halfPi); //(angle-M_PI) should be a small negative angle
			else // leftwards
				angle = twoPi - angle;
			angle = (angle - twoPi * floor(angle / twoPi)); // wrap to stay in [0,2pi]
			vy = -vy;
		}

		// move position
		x += vx;
		y += vy;
		// also, the ball always speeds up...
		speed += delta / 2;
	}

	void Draw(Renderer& renderer) override
	{
		SDLPrimitive::FillCircle(renderer, x, y, radius, color);
	}
private:
	const double halfPi = M_PI / 2.0;
	const double twoPi = M_PI * 2.0;

	ScoreKeeper& scoreKeeper;
	int scoreToWin = 7;

	double maxBounceAngle = 5 * M_PI / 12; // 75 deg

	bool _CheckCollision(Paddle& paddle, double vx, double vy) {
		double dx = x + vx;
		double dy = y + vy;
		// idea: circle overlapping bounding box check
		double circleDistX_L = abs(dx - paddle.x);
		double circleDistX_R = abs(dx - (paddle.x + paddle.rect.w));

		if (dx < paddle.x) {
			// outside left bound
			if (circleDistX_L >= radius) return false;
			// else, we're within radius of x (left side)
		}
		else if (dx > paddle.x + paddle.rect.w) {
			// outside right bound
			if (circleDistX_R >= radius) return false;
			// else, we're within radius of x (right side)
		}
		// within horizontal bounds, check if within vertical
		return (dy + radius > paddle.y) && (dy - radius < paddle.y + paddle.rect.h);
	}
	/// <summary>
	/// Called at the start of a respawn.
	/// </summary>
	void _StartRespawn() {
		toRespawn = true;
		x = -10 - radius;
		y = -10 - radius;
		respawnTimer = 2.0;
		speed = 1;
	}
	/// <summary>
	/// Called at the end of a respawn.
	/// </summary>
	void _EndRespawn() {
		toRespawn = false;
		x = (double)OkuLite::renderer->ScreenWidth() / 2;
		y = (double)OkuLite::renderer->ScreenHeight() / 2;
		scoreKeeper.HidePlayerWin();
	}

	void _CheckPlayerWin() {
		const auto scores = scoreKeeper.GetScores();
		if (scores[0] == scoreToWin)
			scoreKeeper.ShowPlayerWin(0);
		else if (scores[1] == scoreToWin)
			scoreKeeper.ShowPlayerWin(1);
	}

	double _dot(double x1, double y1, double x2, double y2) {
		return (x1 * y1) + (x2 * y2);
	}
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
	std::stringstream sstr;
	sstr << std::filesystem::current_path();
	OLog::Info(sstr.str().c_str());

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

	auto scoreKeeper = std::make_shared<ScoreKeeper>();
	OkuLite::goManager->AddGameObject(scoreKeeper);

	auto ball = std::make_shared<Ball>(*scoreKeeper, OkuLite::renderer->ScreenWidth() / 2, OkuLite::renderer->ScreenHeight() / 2);
	ball->paddleA = paddle;
	ball->paddleB = paddle2;
	OkuLite::goManager->AddGameObject(ball);

	OLog::Info("Active!");

	// Pass off to engine loop
	const auto ret = OkuLite::Loop();

	return ret;
}