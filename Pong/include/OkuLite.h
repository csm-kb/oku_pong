#ifndef OkuLite_H
#define OkuLite_H

#include <SDL.h>

#include <renderer/Renderer.h>
#include <engine/GOManager.h>
#include <engine/Input.h>
#include <util/Log.h>

class OkuLite
{
public:
	/**
	 * \brief Initializes the engine and underlying components for interactive use.
	 */
	static bool Init(const char* const windowName);

	/**
	 * \brief The core engine loop entry point. Returns a POSIX-style exit code.
	 */
	static int Loop();

	/**
	 * \brief Tells the engine to stop everything and shut down.
	 */
	static void Quit();
	
	static std::unique_ptr<Renderer> renderer;
	static std::unique_ptr<GOManager> goManager;
};

#endif//OkuLite_H