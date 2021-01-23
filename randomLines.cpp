#include "scr/window.h"
#define _USE_MATH_DEFINES
#include <string>
#include <chrono>
#include <thread>
#include <sstream>
#include <list>
#include <vector>
#include <cmath>

#define DEFAULT_HEIGHT 1920
#define DEFAULT_width 1080
#define MAX_COUNT_VECTORS 500

constexpr const unsigned sleep_for = 1000/50;

typedef sf::Vector2f v;
std::vector<v> points;
sf::Clock timer;
bool debug = false;

float v_(const v& a,const v& b)
{
    return (a.x*b.y-b.x*a.y);
}

bool wtf(const float& a, const float&b = 0.0)
{
    return ((a*b)<1e-3);
}

bool crossing(const v& aStart, const v& aEnd,
              const v& bStart, const v& bEnd)
{
    float v1 = v_(bEnd-bStart, {aStart.x-bStart.x, aStart.y-bStart.y});
    float v2 = v_(bEnd-bStart, aEnd-bStart);
    float v3 = v_(aEnd-aStart, bStart-aStart);
    float v4 = v_(aEnd-aStart, bEnd-aStart);
    if(wtf(v1*v2) && wtf(v3*v4)) return true;
    else return false;
}

auto toNumber(const std::string& str)
{
    size_t num = 0;
        std::stringstream stream(str);
        stream >> num;
    return num;
}

inline float random(const int& n)
{
    return (rand()%n);
}

inline float random(const int& min, const int& max)
{
    return (random(max-min)+min);
}

int includes(const std::vector<int>& v, const int& value)
{
	for(int i = 0; i < v.size(); ++i)
    {
	    if(v[i] == value) return i;
    }
	return -1;
}

sf::Vector2f r(std::vector<int>& alloved, int& __)
{
    int v = rand()%alloved.size();
    v = alloved[v];
    __ = v;
    switch(v)
    {
        case 0:
            return {-random(20,10), 0.0};
            break;
        case 1:
            return {random(20,10), 0.0};
            break;
        case 2:
            return {0.0, random(20,10)};
            break;
        case 3:
            return {0.0, -random(20, 10)};
            break;
    }
}

template<typename VALUE>
const VALUE& random(const std::vector<VALUE>& values)
{
	return values[rand()%values.size()];
}

bool allCross(const v& a, const v& b)
{
    if(points.size() <= 2) return false;
    for(size_t i = 1; i < (points.size()-2); ++i) {
        if (crossing(points[i-1], points[i], a, b)) return true;
    }
    return false;
}

void tick(const sf::Vector2f& p)
{
    std::vector<int> alloved = {0,1,2,3};
    int code;
    auto v = r(alloved, code);
    v += p;
    while(allCross(p, v) || (v.x < 0 || v.x > 990 || v.y > 990 || v.y < 0))
    {
        if (debug) {
            std::cout << "CROSSING\n";
            std::cout << "ALLOW WAYS: " << alloved.size() << "\n";
        }
        if(alloved.size()) {
            int __$ = includes(alloved, code);
            if (debug) {
                std::cout << "CODE: " << code << "\n";
                std::cout << "OFFSET: " << __$ << "\n";
            }
            if(__$ != -1) alloved.erase(alloved.begin()+__$);
            if (alloved.size()) {
                v = r(alloved, code);
                v += p;
            }
            else continue;
        } else {
            if(debug) std::cout << "CANNOT FIND WAY\n";
            alloved = {0,1,2,3};
            while((v.x < 0 || v.x > 990 || v.y > 990 || v.y < 0)) {
                v = r(alloved, code);
                v += p;
            }
            break;
        }
        if(debug)std::cout << "\n------------------------------------------\n";
    }
    points.push_back(v);
}

void renderMathFunction(sf::RenderWindow& window, Window* _)
{
    _->window.clear();

    for (size_t i = 0; points.size() >= 2 && i < points.size(); ++i)
    {
        if ((i + 1) < points.size()) _->line<float>(points[i], points[i + 1]);
    }
    _->window.display();
    if (timer.getElapsedTime().asMicroseconds() >= 50) {
        tick(points.back());
        timer.restart();
    }
    if (points.size() >= MAX_COUNT_VECTORS) points.erase(points.begin());
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
}

void event(sf::Event& event, Window* w)
{
	// std::cout << points.size() << "\n";
	// if(event.type == sf::Event::MouseButtonPressed) {
	// 	auto pos = sf::Mouse::getPosition();
	// 	std::cout << allCross(points.back(), {
	// 		(float)0.0+pos.x,
	// 		(float)0.0+pos.y
	// 	}) << "\n";
	// 	points.push_back({
	// 		(float)0.0+pos.x,
	// 		(float)0.0+pos.y
	// 	});
	// }
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    int h = -1, w = -1;
    if (argc >= 3) {
        std::cout << toNumber(argv[1]) << "\n";
        h = toNumber(argv[1]);
        w = toNumber(argv[2]);
    }

    for (size_t i = 0; i < argc; ++i)
        if (argv[i] == "debug") debug = true;

    if (h < 1) h = DEFAULT_HEIGHT;
    if (w < 1) w = DEFAULT_width;
    points.push_back({ 500.0, 500.0 });

    std::cout << h << "x" << w << "\n";
    Window window(h, w, "MAIN WINDOW");
    //window.window.setFramerateLimit(10);
    window.render(renderMathFunction, event);

    return 0;
}
