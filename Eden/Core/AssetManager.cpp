#include "Precompiled.h"
#include "AssetManager.h"

namespace edn
{
	//
	// Assets
	//
	void Asset::Load(String filename)
	{
		m_name = filename;
    	String cache_file = os::MakePath(AssetManager::CachePath(), m_subDir, m_name);
		if (os::IsFile(cache_file))
			loadFromCashe(cache_file);
		else
		{
			String file = os::MakePath(AssetManager::AssetPath(), m_subDir, m_name);
			loadFromFile(file);
			writeCacheFile(cache_file);
		}
	}
}