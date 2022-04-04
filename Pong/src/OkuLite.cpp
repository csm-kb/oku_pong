#include <OkuLite.h>
#include <string>

std::unique_ptr<Renderer> OkuLite::renderer = nullptr;
std::unique_ptr<GOManager> OkuLite::goManager = nullptr;

bool OkuLite::Init(const char* const windowName)
{
	OLog::Info("Creating renderer", true);
	// initialize renderer
	renderer = std::make_unique<Renderer>();
	if (!renderer->Init(windowName))
		return false;

	OLog::Info("Creating GameObject manager", true);
	// initialize go manager
	goManager = std::make_unique<GOManager>(*renderer);
	if (!goManager->Init())
		return false;

	return true;
}

int OkuLite::Loop()
{
	SDL_Event event;
	double delta = 0;
	// -- BEHOLD, A GAME LOOP! -- //
	do
	{
		// -- input --
		while (SDL_PollEvent(&event))
		{
			renderer->running = event.type != SDL_QUIT;
			// update Input state
			if (event.type == SDL_KEYDOWN)
				Input::SetKeyDown(event.key.keysym.scancode);
			else if (event.type == SDL_KEYUP)
				Input::SetKeyUp(event.key.keysym.scancode);
		}
		const Uint64 tx = SDL_GetTicks64();
		delta = static_cast<double>(tx - renderer->ticks) / 1000.0;
		renderer->ticks = tx;

		// -- update --
		goManager->UpdateLoop(delta);

		// -- render --
		renderer->Render(delta);
		//OLog::Info((std::string("render FPS: ") + std::to_string(1.0/delta)).c_str(), true, "\r");

		// end loop
		Input::EndGameLoop();
	} while (renderer->running);
	// -- -- -- -- ---- -- -- -- -- //

	OLog::Info("Begin cleanup", true);

	// clean up GO manager
	goManager->Destroy();
	// clean up renderer
	renderer->Quit();

	OLog::Info("Exiting loop", true);
	return 0;
}

void OkuLite::Quit()
{
	// pretty basic for now, just tell the renderer to stop and the whole thing will collapse
	renderer->running = false;
}
