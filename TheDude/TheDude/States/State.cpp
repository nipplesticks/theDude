#include "State.hpp"

std::stack<State*>* State::s_states = nullptr;
sf::RenderWindow* State::s_window = nullptr;

State::State()
{

}

void State::initStatics(std::stack<State*>* stack, sf::RenderWindow* window)
{
	s_states = stack;
	s_window = window;
}

void State::Pop()
{
	if (!s_states->empty())
		s_states->pop();
	delete this;
}

void State::Push(State * state)
{
	s_states->push(state);
}
