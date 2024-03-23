#pragma once

#include "state.h"

class Component {
public:
	State *state;

	virtual void render(){};
};
