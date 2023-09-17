#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main ()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Switch controller");

  sf::Texture texture;
  if (!texture.loadFromFile("assets/image.jpg"))
    return EXIT_FAILURE;

  sf::Sprite sprite(texture);

  sf::Font font;
  if (!font.loadFromFile("assets/font.ttf"))
    return EXIT_FAILURE;

  sf::Text text("Hello switch controller", font, 50);

  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	}

      window.clear();
      window.draw(sprite);
      window.draw(text);
      window.display();
    }

  return EXIT_SUCCESS;
}
