#pragma once

class Info : public World
{

public:
	virtual void Update() = 0;
	virtual void Render() = 0;
};