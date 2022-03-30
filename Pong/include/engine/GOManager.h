#ifndef GOManager_H
#define GOManager_H

#include <renderer/Renderer.h>

#include <vector>
typedef std::vector<GameObject_Ptr> GameObjectList;

class GOManager
{
public:
	GOManager(Renderer& renderer) : renderer(renderer) {}

	/**
	 * \brief Initializes the GO manager.
	 */
	bool Init();

	/**
	 * \brief Performs an update on every registered GameObject.
	 * \param delta The time since the last frame. Standard update delta.
	 */
	void UpdateLoop(double delta);

	/**
	 * \brief Registers a GameObject to the manager.
	 * \param go The GameObject reference to add.
	 */
	void AddGameObject(GameObject_Ptr go);

	/**
	 * \brief Unregisters a GameObject from the manager.
	 * \param go The GameObject reference to remove.
	 */
	void RemoveGameObject(GameObject_Ptr go);

	/**
	 * \brief Retrieves a list of all game objects.
	 */
	GameObjectList GetAll();

	/**
	 * \brief Tells the manager to clean up upon destroy.
	 */
	void Destroy();

private:
	Renderer& renderer;

	size_t goListSize;
	size_t goListMax;
	GameObject_Ptr* goList;

	/// <summary>
	/// Doubles the size of the tracker.
	/// </summary>
	void _IncreaseListSize();

	/// <summary>
	/// Halves the size of the tracker. Is always valid because the size of the array should always a power of two.
	///	If the list cannot be halved because (size > max/2), then this does nothing.
	/// </summary>
	void _DecreaseListSize();
};

#endif//GOManager_H