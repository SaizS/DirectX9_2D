#pragma once

class Cursor : public World{
private:
	vector<Texture*> textures;
public:
	Cursor();
	~Cursor();
	void Update();
	void Render();

};