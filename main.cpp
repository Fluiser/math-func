#include "scr/window.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <math.h>
#define MATH_DEFINES
#define DEFAULT_HEIGHT 1000
#define DEFAULT_WEIGHT 1000

static bool debug = false;
const unsigned cm = 50;
constexpr const unsigned sleep_for = 1000/30;

template<typename T>
T transX(T n, T s)
{
    auto E = (float)s/2;
    if (n < 0) return (E-abs(n));
    else return (n+E);
}

template<typename T>
T transY(T n, T s)
{
    auto E = (float)s/2;
    if(n >= 0) return (E-n);
    else return (E+abs(n));
}


double mathFunction(double x)
{
    double y = sin(x)*180;
    return y;
}

auto toNumber(const std::string& str)
{
    size_t num = 0;
    try {
        std::stringstream stream(str);
        stream >> num;
    } catch(std::exception err) {
        if(debug) std::cout << err.what() << "\n";
        num = 0;
    }
    return num;
}

void renderMathFunction(sf::RenderWindow& window, Window* _)
{
    _->window.clear();
    auto size = _->window.getSize();
    //@Y
    _->line(
            math::vector<float>(size.x/2, 0),
            math::vector<float>(size.x/2, size.y),
            sf::Color::Yellow
        );
    //@X
    _->line(
            math::vector<float>(0, size.y/2),
            math::vector<float>(size.x, size.y/2),
            sf::Color::Yellow
        );


    for(unsigned i = 0; i <= size.y; i += cm)
    {
        _->line(
                math::vector<float>((size.x/2)-5, i),
                math::vector<float>((size.x/2)+5, i),
                sf::Color::Yellow
        );
    }

    for(unsigned i = 0; i <= size.x; i += cm)
    {
        _->line(
                math::vector<float>(i, (size.y/2)-5),
                math::vector<float>(i, (size.y/2)+5),
                sf::Color::Yellow
        );
    }
    
    for(float x = -(float)size.x/2; x <= ((float)size.x/2); x += cm)
    {
        auto start = math::vector<double>(transX<double>(x, size.x), transY<double>(mathFunction(x), size.y));
        auto end = math::vector<double>(transX<double>(x+cm, size.x), transY<double>(mathFunction(x+cm), size.y));
        if(debug) {
            std::cout << x << " - " << mathFunction(x) << "\n";
            std::cout << "start: " << start.toString() << "\n";
            std::cout << "end: " << end.toString() << "\n";
        }
        _->line(
                start,
                end,
                sf::Color::Red
        );
    }

    _->window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
}

int main(int argc, char** argv)
{
    int h = -1, w = -1;
    if (argc >= 3) {
        std::cout << toNumber(argv[1]) << "\n";
        h = toNumber(argv[1]);
        w = toNumber(argv[2]);
    }

    if(h < 1) h = DEFAULT_HEIGHT;
    if(w < 1) w = DEFAULT_WEIGHT;

    if(argc >= 2) {
        for(int i = 1; i < argc; ++i)
            if(std::string(argv[i]) == "debug") debug = true;
    }
    std::cout << h << "x" << w << "\n";
    Window window(h, w, "MAIN WINDOW");
    //window.window.setFramerateLimit(10);
    window.render(renderMathFunction, [](auto&, auto*){});

    return 0;
}
