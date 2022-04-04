#ifndef Renderer_H
#define Renderer_H

#include <array>
#include <SDL.h>

#include <engine/GameObject.h>

class GameObject;

/// <summary>
/// Renderer for the game engine.
///
///	Currently uses a basic unordered drawing system for rendering game objects.
/// </summary>
class Renderer
{
public:
	SDL_Window* window;
	//SDL_Surface* surface;
	//SDL_Surface* pixels;
	SDL_Renderer* renderer;

	/// <summary>
	/// Whether the renderer is running at the moment.
	/// </summary>
	bool running;
	/// <summary>
	/// The total number of milliseconds that have passed since the game started (from <see cref="SDL_GetTicks64"/>).
	/// </summary>
	Uint64 ticks;

	/// <summary>
	/// Returns the current screen width in pixels.
	/// </summary>
	int ScreenWidth();

	/// <summary>
	/// Returns the current screen height in pixels.
	/// </summary>
	int ScreenHeight();

	/**
 * \brief Initializes a renderer object.
 */

	/// <summary>
	/// Initializes the renderer object.
	/// </summary>
	/// <returns>Whether it was successful.</returns>
	bool Init(const char* const windowName,
		int screenWidth = 1280,
		int screenHeight = 720,
		int screenDepth = 32);
	/**
	 * \brief Tells the renderer to render this frame.
	 */

	/// <summary>
	/// Tells the renderer to render this frame with the given variable time delta.
	/// </summary>
	/// <param name="delta">The amount of time passed since last frame.</param>
	/// <returns>Whether it was successful.</returns>
	bool Render(double delta);

	/// <summary>
	/// Adds the specified GameObject to the render queue.
	/// </summary>
	void AddToRenderList(GameObject_Ptr go);

	/// <summary>
	/// Removes the specified GameObject from the render queue.
	/// </summary>
	void RemoveFromRenderList(GameObject_Ptr go);

	/// <summary>
	/// Tells the renderer to quit and clean up.
	/// </summary>
	void Quit();

private:
	int currentScreenWidth, currentScreenHeight;
	size_t goRenderSize;
	size_t goRenderMax;
	GameObject_Ptr* goRenderList;

	/// <summary>
	/// Doubles the size of goRenderList.
	/// </summary>
	void _IncreaseRenderListSize();

	/// <summary>
	/// Halves the size of goRenderList. Is always valid because the size of the array should always a power of two.
	///	If the list cannot be halved because (size > max/2), then this does nothing.
	/// </summary>
	void _DecreaseRenderListSize();
};



#endif//Renderer_H