#pragma once

class GWManager : public World{
private:
	vector<GetItemWindow*> windows;
public:
	GWManager();
	~GWManager();
	void Update();
	void Render();
	void AddWindow(int key, float duration);
};