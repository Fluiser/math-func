#include <SFML/Graphics.hpp>
#include <vector>

#ifndef ___WINDOW_HPP
#define ___WINDOW_HPP

class Window {
public:
	sf::RenderWindow window;

	Window(int x, int y, const char* title)
	{
            window.create(sf::VideoMode(x, y), title, sf::Style::Default);
	}

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
    void line(const sf::Vector2<T>& start, const sf::Vector2<T>& end, sf::Color color = sf::Color::Red)
    {
        sf::VertexArray lines(sf::Lines, 2);
        lines[0].position = start;
        lines[1].position = end;
        lines[0].color = color;
        lines[1].color = color;
        this->window.draw(lines);
    }
};

#endif
