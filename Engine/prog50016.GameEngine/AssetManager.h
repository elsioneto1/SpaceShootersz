#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_
#pragma once

#include "ISystem.h"

class Asset;

class AssetManager : public ISystem
{
private:
	std::map<STRCODE, std::shared_ptr<Asset>> assets;

public:
	inline static AssetManager& Instance()
	{
		static AssetManager instance;
		return instance;
	}

	void initialize();

	std::shared_ptr<Asset> getAsset(STRCODE AssetUID, STRCODE Type = NoName);
	std::shared_ptr<Asset> getAsset(std::string AssetUID, STRCODE Type = NoName);

protected:
	void load(XMLElement* element, STRCODE fileID);
	void unload(STRCODE filecode);

private:
	AssetManager() = default;
	~AssetManager() = default;
	AssetManager(AssetManager const&) = delete;

	friend class GameEngine;
	friend class FileSystem;
};

#endif

