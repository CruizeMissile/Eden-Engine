#ifndef H_CORE_ASSET_MANAGER_H
#define H_CORE_ASSET_MANAGER_H

#include "Precompiled.h"
#include "AssetPool.h"

namespace edn
{
	class AssetManager;

	class Asset
	{
		friend class AssetManager;
	public:
		void Load(String filename);

		//protected:
		virtual void loadFromFile(String filename) = 0;
		virtual void loadFromCashe(String filename) = 0;
		virtual void writeCacheFile(String filename) = 0;

		String m_name;
		String m_subDir;
	};

	class AssetManager : public Singleton<AssetManager>
	{
		typedef std::unique_ptr<AssetPoolInterface> AssetPoolPtr;
		typedef std::unordered_map<std::type_index, AssetPoolPtr> AssetPoolList;
		typedef AssetPoolList::value_type AssetPoolPair;

	public:
		template<typename Type>
		static void Register();

		template<typename Type>
		static Type * Load(String file);

		//Texture * texture = AssetManager::Load<Texture>(filename);

		static String & AssetPath() { return AssetManager::Instance().m_rootAssetPath; }
		static String & CachePath() { return AssetManager::Instance().m_rootCachePath; }

		static void SetAssetPath(String path) { AssetManager::Instance().m_rootAssetPath = path; }
		static void SetCachePath(String path) { AssetManager::Instance().m_rootCachePath = path; }

	private:
		template<typename Type>
		Type * create(String file);
		template<typename Type>
		Type * lookup(String file);

		template<typename Type>
		AssetPool<Type> * getAssetPool();

		AssetPoolList m_assets;
		String m_rootAssetPath;
		String m_rootCachePath;
	};

	//
	// Asset
	//


	//
	// AssetManager
	//
	template<typename Type>
	void AssetManager::Register()
	{
		AssetManager & mgr = AssetManager::Instance();

		// Validate Asset type
		static_assert(std::is_base_of<Asset, Type>::value, "Not a asset type");

		// Check if Asset type is registered
		auto it = mgr.m_assets.find(typeid(Type));

		if (it != mgr.m_assets.end())
			return;

		std::type_index index = typeid(Type);

		auto poolPtr = std::make_unique<AssetPool<Type>>();

		auto pair = std::make_pair(index, std::move(poolPtr));
		auto result = mgr.m_assets.insert(std::move(pair));
	}

	template<typename Type>
	Type * AssetManager::Load(String file)
	{
		AssetManager & mgr = AssetManager::Instance();
		// Validate component type
		static_assert(std::is_base_of<Asset, Type>::value, "Not a Asset type");

		// Getting the Type asset list
		Type * value = mgr.lookup<Type>(file);

		// could not find the 
		if (value == nullptr)
		{
			value = mgr.create<Type>(file);
			value->Load(file);
			return value;
		}
		return value;
	}

	template<typename Type>
	Type * AssetManager::create(String file)
	{
		AssetPool<Type> * pool = getAssetPool<Type>();

		if (pool == nullptr)
			return nullptr;

		return pool->Create(file);
	}

	template<typename Type>
	Type * AssetManager::lookup(String file)
	{
		AssetPool<Type> * pool = getAssetPool<Type>();

		if (pool == nullptr)
			return nullptr;

		return pool->Lookup(file);
	}

	template<typename Type>
	AssetPool<Type> * AssetManager::getAssetPool()
	{
		auto it = m_assets.find(typeid(Type));
		if (it == m_assets.end())
			return nullptr;

		AssetPool<Type> * pool = reinterpret_cast<AssetPool<Type>*>(it->second.get());
		return pool;
	}

}


#endif