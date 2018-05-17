#include "State.hpp"

std::stack<State*>* State::s_states = nullptr;
sf::RenderWindow* State::s_window = nullptr;

State::State()
{

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

void State::InitState(sf::RenderWindow* window, std::stack<State*>* states)
{
	s_states = states;
	s_window = window;
}