#include <engine/GameObject.h>

GameObject_Ptr GameObject::Instantiate(GameObject &original)
{
	auto go = std::make_shared<GameObject>();
	go->enabled = original.enabled;
	if (original.enabled)
	{
		go->OnEnable();
	}
	go->Start();
	return go;
}