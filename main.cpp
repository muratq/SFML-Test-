#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstdlib>

enum class YON {

	SOL,
	SAG,
	YUKARI,
	ASAGI,
	DUR
};

sf::Vector2f YemPosition(void);

void hareket(sf::Vector2f& konum, YON yon)
{
	switch (yon)
	{
	case YON::SAG:
		konum.x += 5;
		break;
	case YON::SOL:
		konum.x -= 5;
		break;
	case YON::YUKARI:
		konum.y -= 5;
		break;
	case YON::ASAGI:
		konum.y += 5;
		break;
	case YON::DUR:
		break;
	}

}



int main() {

	sf::Clock saat;
	sf::RenderWindow pencere(sf::VideoMode(600, 600), "merhaba");
	

	
	sf::CircleShape daire(10, 10);
	daire.setFillColor(sf::Color::Blue);
	daire.setOutlineThickness(2.1f);
	daire.setOutlineColor(sf::Color::Yellow);
	daire.setPosition(sf::Vector2f(0, 0));

	sf::CircleShape yem(10, 10);
	yem.setFillColor(sf::Color::Red);
	yem.setOutlineThickness(2.1f);
	yem.setOutlineColor(sf::Color::Yellow);

	sf::RectangleShape ekran(sf::Vector2f(600, 600));
	ekran.setFillColor(sf::Color::White);

	sf::Text yazi;

	yazi.setString("selam");
	yazi.setFillColor(sf::Color::Red);
	yazi.setPosition(300, 300);
	yazi.setCharacterSize(24);

	yem.setPosition(YemPosition());


	

	sf::Vector2f konum(100, 100);
	YON sekilYonu = YON::SAG;

	float cerceveSuresi = 1/60.0f;
	while (pencere.isOpen())
	{
		sf::Event olay;
		while (pencere.pollEvent(olay))
		{
			sf::Vector2f pos;
			pos = daire.getPosition();
			if (olay.type == sf::Event::Closed)
			{
				pencere.close();
			}
			if (olay.type == sf::Event::KeyPressed)
			{
				if (olay.key.code == sf::Keyboard::Left)
				{
					sekilYonu = YON::SOL;

					
				}
				else if (olay.key.code == sf::Keyboard::Right)
				{
					sekilYonu = YON::SAG;
					
				}
				else if (olay.key.code == sf::Keyboard::Up)
				{
					sekilYonu = YON::YUKARI;
				

				}
				else if (olay.key.code == sf::Keyboard::Down)
				{
					sekilYonu = YON::ASAGI;
					
				}
			}
			if (olay.type == sf::Event::KeyReleased)
			{
				if (olay.key.code == sf::Keyboard::Left ||
					olay.key.code == sf::Keyboard::Right||
					olay.key.code == sf::Keyboard::Up   ||
					olay.key.code == sf::Keyboard::Down 
					)
				{
					//sekilYonu = YON::DUR;
				}
			}
			if(olay.type == sf::Event::MouseMoved)
			{ 
				//std::cout<<olay.mouseMove.x << std::endl;
			}
		}


		float gecenSure = saat.getElapsedTime().asSeconds();
		if (gecenSure > cerceveSuresi)
		{
			pencere.clear();
			hareket(konum, sekilYonu);
			daire.setPosition(konum);
			pencere.draw(ekran);
			pencere.draw(daire);
			pencere.draw(yem);
			pencere.draw(yazi);
			pencere.display();

			sf::Vector2f dairePos;
			sf::Vector2f yemPos;
			dairePos = daire.getPosition();
			yemPos = yem.getPosition();

			if (olay.type == sf::Event::MouseButtonPressed)
			{
				if (olay.mouseButton.button == sf::Mouse::Left)
				{
					std::cout<<olay.mouseButton.x << ","<< olay.mouseButton.y << std::endl;
				}

			}


			if (dairePos.x > 600)
			{
				konum.x = 0;
				
			}
			if (dairePos.x < 0)
			{
				konum.x = 600;

			}
			if (dairePos.y < 0)
			{
				konum.y = 600;
				
			}

			if (dairePos.y > 600)
			{
				konum.y = 0;

			}
			if ((yemPos.x > dairePos.x-15 && yemPos.x < dairePos.x+15) && (yemPos.y > dairePos.y - 15 && yemPos.y < dairePos.y + 15))
			{
				std::cout << "scoree!!!" << std::endl;
				yem.setPosition(YemPosition());
				
			}


			int fps = 1.0f / gecenSure;
			saat.restart();
		}
		else
		{
			sf::sleep(sf::seconds(cerceveSuresi - gecenSure));
		}
	}
}


sf::Vector2f YemPosition(void)
{
	int x, y;
	x = rand() % 580;
	y = rand() % 580;
	return sf::Vector2f(x, y);
}
