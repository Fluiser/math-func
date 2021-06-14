#include "scr/window.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#define DEFAULT_HEIGHT 1000
#define DEFAULT_WIDTH 1000

inline float radiant(const float& n)
{
    if(n == 0) return 0;
    return (n)*M_PI/180;
}

static bool debug = false;
constexpr float cm = 50;
// It's for you if want you draw line with random y.
constexpr const unsigned sleep_for = 1000/30;

float h = -1, w = -1;

inline sf::Vector2f normalize(const sf::Vector2f& null, const sf::Vector2f& point)
{
	return sf::Vector2f{ null.x+point.x, null.y-point.y };
}

float mathFunction(float x)
{
    float y = sin(radiant(x));
    return y;
}

auto toNumber(const std::string& str)
{
    size_t num = 0;
    std::stringstream stream(str);
    stream >> num;
    return num;
}

void renderMathFunction(sf::RenderWindow& window, Window* _)
{
    _->window.clear();
    auto size = _->window.getSize();
    //@Y
    _->line(
            sf::Vector2f(size.x/2, 0),
            sf::Vector2f(size.x/2, size.y),
            sf::Color::Yellow
        );
    //@X
    _->line(
            sf::Vector2f(0, size.y/2),
            sf::Vector2f(size.x, size.y/2),
            sf::Color::Yellow
        );


    for(unsigned i = 0; i <= size.y; i += cm)
    {
        _->line(
                sf::Vector2f((size.x/2)-5, i),
                sf::Vector2f((size.x/2)+5, i),
                sf::Color::Yellow
        );
    }

    for(unsigned i = 0; i <= size.x; i += cm)
    {
        _->line(
                sf::Vector2f(i, (size.y/2)-5),
                sf::Vector2f(i, (size.y/2)+5),
                sf::Color::Yellow
        );
    }
    
    for(float x = -(float)size.x/2; x <= ((float)size.x/2); x += cm/10)
    {
        sf::Vector2f start{ x, mathFunction(x)*cm };
        sf::Vector2f end{ x+cm/10, mathFunction(x+cm/10)*cm };

        _->line(
                normalize(sf::Vector2f{h/2, w/2}, start),
                normalize(sf::Vector2f{h/2, w/2}, end),
                sf::Color::Red
        );
    }

    _->window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
}

int main(int argc, char** argv)
{
    if (argc >= 3) {
        std::cout << toNumber(argv[1]) << "\n";
        h = toNumber(argv[1]);
        w = toNumber(argv[2]);
    }

    if(h < 1) h = DEFAULT_HEIGHT;
    if(w < 1) w = DEFAULT_WIDTH;

    if(argc >= 2) {
        for(int i = 1; i < argc; ++i)
            if(argv[i] == "debug") debug = true;
    }
    std::cout << h << "x" << w << "\n";
    Window window(h, w, "MAIN WINDOW");
    //window.window.setFramerateLimit(10);
    window.render(renderMathFunction, [](auto&, auto*){});

    return 0;
}
