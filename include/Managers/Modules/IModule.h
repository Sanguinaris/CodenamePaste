#pragma once
#include <string>

class IModule {
public:
	virtual ~IModule() = default;

public:
	virtual void Toggle() = 0;
	virtual void SetActive(bool state) = 0;

public:
	virtual const std::string& GetModuleName() const = 0;
	virtual const bool IsActive() const = 0;
};
