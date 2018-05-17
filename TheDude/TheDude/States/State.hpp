#pragma once
#include <stack>
#include <SFML\Graphics.hpp>

class State 
{
private:
	static std::stack<State*>* s_states;

protected:
	static sf::RenderWindow* s_window;

public:
	State();
	virtual ~State() {};
	virtual void Pop();
	virtual void Push(State * state);
	virtual void Update() = 0;
	virtual void Draw() = 0;


	static void InitState(sf::RenderWindow* window, std::stack<State*>* states);
};