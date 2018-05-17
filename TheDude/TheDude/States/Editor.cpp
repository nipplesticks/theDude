#include "Editor.hpp"

Editor::Editor()
	: level(s_window)
{
	level.LoadLevel("Resourses/Levels/test34");
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
	level.EditorRender();
	s_window->draw(level);

}