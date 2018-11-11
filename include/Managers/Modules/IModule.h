#pragma once
#include <string>

class IModule {
public:
	virtual ~IModule() = default;

public:
	virtual const std::string& GetModuleName() = 0;
	virtual const bool IsActive() = 0;

};
