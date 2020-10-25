#pragma once
#include "define.h"
#include "Configurable.h"

class ConfigLoader : public Configurable<const char* const> {
private:
	inline static ConfigLoader* _self = nullptr;

private:
	unordered_map<string, Configurable<json&>*> _confMap;

private:
	ConfigLoader();
	~ConfigLoader();

public:
	inline static ConfigLoader* getInstance() {
		if (!_self) { _self = new ConfigLoader(); }
		return _self;
	}
	inline static void finalize() {
		delete _self;
		_self = nullptr;
	}

public:
	void configure(const char* const fpath) override;

private:
	void setConfigure();
	inline void callConfigure(json& path);
};