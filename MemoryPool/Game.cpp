#include "Game.h"

namespace lab9
{
	Game::Game(unsigned int seed, unsigned int poolSize)
	{
		srand(seed);
		mPool = new ObjectPool<IceCube>(static_cast<size_t>(poolSize));
	}

	Game::~Game()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end(); ++it)
		{
			delete (*it);
		}

		mActiveGameObjects.clear();
		delete mPool;
	}

	void Game::Spawn()
	{
		IceCube* iceCube = mPool->Get();
		iceCube->Initialize(rand() % MAX_FRAME_COUNT_TO_LIVE + 1);
		mActiveGameObjects.push_back(iceCube);
	}

	void Game::Update()
	{
		for (auto it = mActiveGameObjects.begin(); it != mActiveGameObjects.end();)
		{
			IceCube* iceCube = *it;
			iceCube->Animate();

			if (!iceCube->IsActive())
			{
				mPool->Return(*it);
				it = mActiveGameObjects.erase(it);
				continue;
			}

			++it;
		}
	}

	const std::vector<IceCube*>& Game::GetActiveGameObjects() const
	{
		return mActiveGameObjects;
	}
	ObjectPool<IceCube>& Game::GetObjectPool()
	{
		// TODO: insert return statement here
		return *mPool;
	}
}