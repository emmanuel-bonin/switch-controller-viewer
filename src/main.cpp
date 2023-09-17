#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>

const unsigned int WINDOW_W = 500;
const unsigned int WINDOW_H = 500;
const unsigned int SWITCH_CONTROLLER_MAX_BUTTON = 14;

class JoystickProjection
{
private:
  sf::CircleShape *_circle;
  sf::RectangleShape *_xAxis;
  sf::RectangleShape *_yAxis;
  sf::CircleShape *_positionDot;
  sf::Font *_font;
  sf::Text *_text;
  float _projDotRadius;

public:
  JoystickProjection();
  ~JoystickProjection();

  void update(float, float);
  void draw(sf::RenderWindow&);
};

JoystickProjection::JoystickProjection()
{
  this->_circle = new sf::CircleShape(250.0f);
  this->_circle->setFillColor(sf::Color(125.0f, 125.0f, 125.0f));
  this->_circle->setPosition(0.0f, 0.0f);

  this->_xAxis = new sf::RectangleShape(sf::Vector2f(500.0f, 2.0f));
  this->_xAxis->setPosition(0.0f, 250.0f);
  this->_xAxis->setFillColor(sf::Color(250.0f, 0.0f, 0.0f));

  this->_yAxis = new sf::RectangleShape(sf::Vector2f(2.0f, 500.0f));
  this->_yAxis->setPosition(250.0f, 0.0f);
  this->_yAxis->setFillColor(sf::Color(0.0f, 250.0f, 0.0f));

  this->_projDotRadius = 10.0f;
  this->_positionDot = new sf::CircleShape(this->_projDotRadius);
  this->_positionDot->setFillColor(sf::Color(200.0f, 200.0f, 0.0f));

  this->_font = new sf::Font();
  if (!this->_font->loadFromFile("assets/font.ttf"))
    {
      std::cerr << "cannot open font file" << std::endl;
    }

  this->_text = new sf::Text();
  this->_text->setFillColor(sf::Color(250.0f, 250.0f, 250.0f));
  this->_text->setFont(*this->_font);
}

JoystickProjection::~JoystickProjection()
{
  delete this->_circle;
  delete this->_xAxis;
  delete this->_yAxis;
  delete this->_positionDot;
  delete this->_font;
  delete this->_text;
}

void JoystickProjection::update(float x, float y)
{
  const float origX = WINDOW_W / 2 - this->_projDotRadius;
  const float origY = WINDOW_H / 2 - this->_projDotRadius;
  std::stringstream ss;

  float angle = std::abs(std::atan(y / x) * 180 / 3.1415);

  ss << "x: " << x << std::endl << "y: " << y << std::endl << "a: " << angle;

  this->_positionDot->setPosition(origX + (x * WINDOW_W / 2 / 100), origY + (y * WINDOW_H / 2 / 100));
  this->_text->setString(ss.str());

  //this->_text->setFillColor(sf::Color(0.0f, 250.0f, 0.0f));
  // if (angle < 15.0f || angle > 45.0f)
  //     this->_text->setFillColor(sf::Color(250.0f, 0.0f, 0.0f));
  // else if (angle < 25.0f || angle > 35.0f)
  //     this->_text->setFillColor(sf::Color(250.0f, 250.0f, 0.0f));
}

void JoystickProjection::draw(sf::RenderWindow& window)
{
  window.draw(*this->_circle);
  window.draw(*this->_xAxis);
  window.draw(*this->_yAxis);
  window.draw(*this->_positionDot);
  window.draw(*this->_text);
}

int main ()
{
  sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Switch controller");
  JoystickProjection proj;
  std::map<int, std::string> buttonMap;

  buttonMap[0] = "B";
  buttonMap[1] = "A";
  buttonMap[2] = "X";
  buttonMap[3] = "Y";
  buttonMap[4] = "RECORD";
  buttonMap[5] = "L";
  buttonMap[6] = "R";
  buttonMap[7] = "ZL";
  buttonMap[8] = "ZR";
  buttonMap[9] = "-";
  buttonMap[10] = "+";
  buttonMap[11] = "HOME";
  buttonMap[12] = "SL";
  buttonMap[13] = "SR";

  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}
      float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
      float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

      std::cout << "x = " << x << std::endl << "y = " << y << std::endl << std::endl;

      // for (int i = 0; i < SWITCH_CONTROLLER_MAX_BUTTON; i++)
      // 	{
      // 	  if (sf::Joystick::isButtonPressed(0, i))
      // 	    {
      // 	      std::cout << "Button " << buttonMap[i] << std::endl;
      // 	    }
      // 	}

      proj.update(x, y);
      window.clear();
      proj.draw(window);
      window.display();
    }

  return EXIT_SUCCESS;
}
