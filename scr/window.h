#include <SFML/Graphics.hpp>
#include "math_vector.h"
#include <vector>

#ifndef ___WINDOW_H
#define ___WINDOW_H

constexpr size_t ___reserve_size = 8*8*8*8;

class Window {
public:
	sf::RenderWindow window;

	Window(int x, int y, const char* title)
	{
            window.create(sf::VideoMode(x, y), title);
	}
	//Fucking github syntax.
	void render(void(*windowRender)(sf::RenderWindow&, Window*), void(*eventListener)(sf::Event&, Window*))
	{
		sf::Event event;
		while(window.isOpen())
		{	
			while(window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed) window.close();
				eventListener(event, this);
			}
			windowRender(window, this);
		}
	}

    	template<typename T>
	void line(math::vector<T> start, math::vector<T> end, sf::Color color = sf::Color::Black)
	{
		sf::VertexArray lines(sf::Lines, 2);
		lines[0].position = sf::Vector2f(start[0], start[1]);
		lines[1].position = sf::Vector2f(end[0], end[1]);
		lines[0].color = color;
		lines[1].color = color;
		this->window.draw(lines);
	}
};

#endif
