#include <cstdio>

#include <renderer/Renderer.h>

int Renderer::ScreenWidth() { return currentScreenWidth; }
int Renderer::ScreenHeight() { return currentScreenHeight; }

bool Renderer::Init(const char* const windowName, int screenWidth, int screenHeight, int screenDepth)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(windowName,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight, 0);
	if (!window)
	{
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return false;
	}
	currentScreenWidth = screenWidth;
	currentScreenHeight = screenHeight;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
		return false;
	}

	ticks = SDL_GetTicks64();

	goRenderSize = 0;
	goRenderMax = 8;
	goRenderList = new GameObject_Ptr[goRenderMax];

	return true;
}

bool Renderer::Render(double delta)
{
	if (!running)
		return running;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// call each GameObject draw (yes this is extremely simple, no depth-ordering)
	for (auto i = 0; i < goRenderSize; i++)
		goRenderList[i]->Draw(*this);

	// flip window, functions as the frame buffer
	SDL_RenderPresent(renderer);

	return running;
}

void Renderer::AddToRenderList(GameObject_Ptr go)
{
	if (goRenderSize == goRenderMax)
		_IncreaseRenderListSize();

	goRenderList[goRenderSize++] = go;
}

void Renderer::RemoveFromRenderList(GameObject_Ptr go)
{
	auto loc = 0;
	// locate the object pointer
	for (auto i = 0; i < goRenderSize; i++)
		if (goRenderList[i] == go)
		{
			loc = i;
			break;
		}

	// shuffle everything above it down
	for (auto i = loc; i < goRenderSize-1; i++)
		goRenderList[i] = goRenderList[i + 1];
	goRenderList[goRenderSize - 1] = nullptr;
	goRenderSize--;
	// lastly, if we can half the size of the render array to save space, then we do
	if (goRenderSize <= goRenderMax / 2)
		_DecreaseRenderListSize();
}

void Renderer::Quit()
{
	delete[] goRenderList;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::_IncreaseRenderListSize()
{
	goRenderMax *= 2;
	auto newList = new GameObject_Ptr[goRenderMax];
	for (auto i = 0; i < goRenderSize; i++)
		newList[i] = goRenderList[i];

	auto oldList = goRenderList;
	goRenderList = newList;
	delete[] oldList;
}

void Renderer::_DecreaseRenderListSize()
{
	// do nothing if we cannot cut the list in half
	if (goRenderMax / 2 < goRenderSize)
		return;

	goRenderMax /= 2;
	auto newList = new GameObject_Ptr[goRenderMax];
	for (auto i = 0; i < goRenderSize; i++)
		newList[i] = goRenderList[i];

	auto oldList = goRenderList;
	goRenderList = newList;
	delete[] oldList;
}