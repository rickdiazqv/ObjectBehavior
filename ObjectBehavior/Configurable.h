#pragma once

template <typename T>
class Configurable {
public:
	virtual void configure(T config) = 0;
};