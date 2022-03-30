#include <engine/GOManager.h>

bool GOManager::Init()
{
	goListSize = 0;
	goListMax = 8;
	goList = new GameObject_Ptr[goListMax];

	return true;
}

void GOManager::UpdateLoop(double delta)
{
	for (auto i = 0; i < goListSize; i++)
		goList[i]->Update(delta);
}


void GOManager::AddGameObject(GameObject_Ptr go)
{
	if (goListSize == goListMax)
		_IncreaseListSize();

	goList[goListSize++] = go;
	// then, add it to renderer
	renderer.AddToRenderList(go);
}

void GOManager::RemoveGameObject(GameObject_Ptr go)
{
	auto loc = 0;
	// locate the object pointer
	for (auto i = 0; i < goListSize; i++)
		if (goList[i] == go)
		{
			loc = i;
			break;
		}

	// shuffle everything above it down
	for (auto i = loc; i < goListSize - 1; i++)
		goList[i] = goList[i + 1];
	goList[goListSize - 1] = nullptr;
	goListSize--;
	// then, make sure renderer stops drawing it
	renderer.RemoveFromRenderList(go);
	// lastly, if we can half the size of the render array to save space, then we do
	if (goListSize <= goListMax / 2)
		_DecreaseListSize();
}

GameObjectList GOManager::GetAll()
{
	auto gol = GameObjectList();
	for (auto i = 0; i < goListSize; i++)
	{
		gol.emplace_back(goList[i]);
	}
	return gol;
}


void GOManager::Destroy()
{
	delete[] goList;
}


void GOManager::_IncreaseListSize()
{
	goListMax *= 2;
	auto newList = new GameObject_Ptr[goListMax];
	for (auto i = 0; i < goListSize; i++)
		newList[i] = goList[i];

	auto oldList = goList;
	goList = newList;
	delete[] oldList;
}

void GOManager::_DecreaseListSize()
{
	// do nothing if we cannot cut the list in half
	if (goListMax / 2 < goListSize)
		return;

	goListMax /= 2;
	auto newList = new GameObject_Ptr[goListMax];
	for (auto i = 0; i < goListSize; i++)
		newList[i] = goList[i];

	auto oldList = goList;
	goList = newList;
	delete[] oldList;
}