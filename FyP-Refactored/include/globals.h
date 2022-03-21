#ifndef GLOBALS_INCLUDE
#define GLOBALS_INCLUDE

#include <SFML/Graphics.hpp>
#include <box2d/b2_world.h>

#define WINDOW_WIDTH sf::VideoMode::getDesktopMode().width / 4 * 3 //unsigned int (3/4 the size of the screens width)
#define WINDOW_HEIGHT sf::VideoMode::getDesktopMode().height / 4 * 3 // unsigned int (3/4 the size of the screens height)

#define PixelsPerMetre 32.0f //conversion to pixels on screen to metres in box2d

#define PI 3.14159263f

#define Deg2Rad PI / 180.f
#define Rad2Deg 180.f / PI

#endif