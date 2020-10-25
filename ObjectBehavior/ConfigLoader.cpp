#include "ConfigLoader.h"
#include "SpriteManager.h"

ConfigLoader::ConfigLoader() {
	setConfigure();
}

ConfigLoader::~ConfigLoader() {

}

void ConfigLoader::configure(const char* const fpath) {
	json config = json::parse(DxFileRead(fpath));
	json& pathList = config[j_config];

	for (json& path : pathList) {
		callConfigure(path);
	}
}

void ConfigLoader::callConfigure(json& path) {
	json config = json::parse(DxFileRead(j2s(path[j_path]).c_str()));
	_confMap[path[j_class]]->configure(config);
}

void ConfigLoader::setConfigure() {
	_confMap["SpriteManager"] = SpriteManager::getInstance();
}