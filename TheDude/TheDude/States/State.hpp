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
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void initStatics(std::stack<State*>* stack, sf::RenderWindow* window);

protected:
	virtual void Pop();
	virtual void Push(State * state);
};