#include "Editor.hpp"

Editor::Editor()
	: level(s_window)
{
	level.LoadLevel("");
}

Editor::~Editor()
{

}

void Editor::Update()
{
	level.Update();
	if (!level.isClose())
		State::Pop();
}

void Editor::Draw()
{
	
	s_window->draw(level);
	level.EditorRender();

}