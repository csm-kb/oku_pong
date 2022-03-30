#ifndef GameObject_H
#define GameObject_H

#include <memory>

class Renderer;

class GameObject;
typedef std::shared_ptr<GameObject> GameObject_Ptr;

class GameObject
{
public:
	/// <summary>
	/// Whether the object is enabled or not.
	/// </summary>
	bool enabled = true;

	/* --- Static Methods --- */

	/// <summary>
	/// Instantiates a new GameObject given an original copy.
	/// </summary>
	/// <returns>The new GameObject.</returns>
	static GameObject_Ptr Instantiate(GameObject &original);

	/* --- Instance Methods --- */

	/// <summary>
	/// Called when the object is enabled. It will begin to process frame updates.
	/// </summary>
	virtual void OnEnable() {};

	/// <summary>
	/// Called when the object is disabled. It will no longer process frame updates.
	/// </summary>
	virtual void OnDisable() {};

	/// <summary>
	/// Called when the object is first instantianted and ready to go.
	/// </summary>
	virtual void Start() {};

	/// <summary>
	/// Called every frame.
	/// </summary>
	virtual void Update(double delta) {};

	/// <summary>
	/// Called every render cycle.
	/// </summary>
	virtual void Draw(Renderer& renderer) {};
};

#endif//GameObject_H