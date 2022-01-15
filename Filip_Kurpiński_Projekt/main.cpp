#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "gra.cpp"
#include <time.h>
#include <Windows.h>
#include<SFML/System.hpp>
using namespace std;



#define MAX_LICZBA_POZIOMOW 5

class Ludek 
{
private:
	sf::Vector2f pozycja;
	sf::Sprite Sprite;
	sf::Texture Texture;
	sf::Text ludek;
	float ms;
	void texture();
	

public:
	void sprite();
	Ludek();
	virtual ~Ludek();
	void ruch(const float x, const float y);
	void update();
	void render(sf::RenderTarget& window);
	float pozycjax();
	float pozycjay();
};

void Ludek::ruch(const float x, const float y){
	Sprite.move(ms*x,ms*y);
}

void Ludek::texture() {
	Texture.loadFromFile("tekstury/tekstura1.png");
}

void Ludek::sprite() {
	Sprite.setTexture(Texture);
	Sprite.scale(0.1f, 0.1f);
}

float Ludek::pozycjax() {
	return Sprite.getPosition().x;
}
float Ludek::pozycjay() {
	return Sprite.getPosition().y;
}

Ludek::Ludek() {
	texture();
	sprite();
	ms = 10.f;
}

Ludek::~Ludek() {

}

void Ludek::render(sf::RenderTarget& window) {
	window.draw(Sprite);
}

void Ludek::update() {

}

class Platforma {
private:
	sf::Sprite Sprite;
	sf::Texture Texture;
	void texture();
	int w;
	
public:
	Platforma();
	virtual ~Platforma();
	void update();
	void render(sf::RenderTarget& window);
	void sprite(int pos_x, int pos_y, const float x, const float y);
	float pozycjax();
	float pozycjay();
};

float Platforma::pozycjax() {
	return Sprite.getPosition().x;
}
float Platforma::pozycjay() {
	return Sprite.getPosition().y;
}
void Platforma::texture() {
	Texture.loadFromFile("tekstury/ziemia.jpg");
}

void Platforma::sprite(int pos_x, int pos_y, const float x, const float y) {
	Sprite.setTexture(Texture);
	Sprite.setPosition(pos_x, pos_y);
	Sprite.scale(x, y);
}


Platforma::Platforma() {
	texture();
}

Platforma::~Platforma() {

}

void Platforma::render(sf::RenderTarget& window) {
	
	window.draw(Sprite);
}

void Platforma::update() {

}

int pies() {

	sf::Texture kot;
	kot.loadFromFile("tekstury/chmura2.png");
	sf::Sprite chmura1;
	chmura1.setTexture(kot);
	chmura1.scale(0.3f, 0.3f);
	float predkosc=1;

	sf::RenderWindow window(sf::VideoMode(800, 600), "gra");
	Ludek ludek;
	Platforma cokolwiek;
	cokolwiek.sprite(0, 540, 1, 0.1);

	while (window.isOpen())
	{
		if (ludek.pozycjay() < cokolwiek.pozycjay() && predkosc >= 1)
		{
			ludek.ruch(0.f, 0.01f*predkosc);
			predkosc += 0.01;
		}
		else {
			predkosc = 0;
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
		
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			{
				ludek.ruch(-2.f,0.f);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
			{
				ludek.ruch(2.f, 0.f);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && predkosc==0)
			{
				predkosc = 1;
				
				while (predkosc < 2) 
				{
					ludek.ruch(0.f, -0.2f*predkosc);
					predkosc+=0.02;
				}
				predkosc = 1;
			}
			
		}
		window.clear(sf::Color(173,216,230));
		window.draw(chmura1);
		cokolwiek.render(window);
		chmura1.move(0.17f,0.f);
		ludek.render(window);
		window.display();
	}
	return 0;
}

class Menu
{

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW+5];//maksymalna liczba poziomow
	int selectedItem = 0;

public:

	Menu(float width, float height);
	~Menu() {};
	void przesunG();//przesun do gory
	void przesunD();//przesun w dol
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow &window);
	void draw1(sf::RenderWindow &window);//rysuj menu w oknie
};


Menu::Menu(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("C:/Users/filip/Desktop/arial.ttf"))
	{
		return;
	}
	//rysowanie elementow menu
	menu[0].setFont(font);	
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wczytaj gre");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Ostatnie wyniki");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Pomoc");
	menu[3].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 4));
	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("Koniec gry");
	menu[4].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 5));

	menu[5].setFont(font);
	menu[5].setFillColor(sf::Color::Cyan);
	menu[5].setString("Poziom 1");
	menu[5].setPosition(sf::Vector2f(800 / 3, 600 / 6 * 1));
	menu[6].setFont(font);
	menu[6].setFillColor(sf::Color::White);
	menu[6].setString("Poziom 2");
	menu[6].setPosition(sf::Vector2f(800 / 3, 600 / 6 * 2));
	menu[7].setFont(font);
	menu[7].setFillColor(sf::Color::White);
	menu[7].setString("Poziom 3");
	menu[7].setPosition(sf::Vector2f(800 / 3, 600 / 6 * 3));
	menu[8].setFont(font);
	menu[8].setFillColor(sf::Color::White);
	menu[8].setString("Poziom 4");
	menu[8].setPosition(sf::Vector2f(800 / 3, 600 / 6 * 4));
	menu[9].setFont(font);
	menu[9].setFillColor(sf::Color::White);
	menu[9].setString("Powrot");
	menu[9].setPosition(sf::Vector2f(800 / 3, 600 / 6 * 5));
}


//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
	if (selectedItem > 5)
		selectedItem = 0;
}

void Menu::draw1(sf::RenderWindow &window)
{
	for (int i = 5; i < 10; i++)
	{
		window.draw(menu[i]);
	}
	if (selectedItem < 5)
		selectedItem = 5;
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	if (selectedItem >= 5 && selectedItem < MAX_LICZBA_POZIOMOW+5)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 5)
			selectedItem = MAX_LICZBA_POZIOMOW +4;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
	
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	if (selectedItem >= 5 && selectedItem < MAX_LICZBA_POZIOMOW+5)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW+5)
			selectedItem = 5;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
	
}

//funklcja opozniajaca
void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
			
	}	
}


int main()
{
	int menu_selected_flag = 0;
	FILE* plik;
	int zmienna;
	plik = fopen("plik.txt", "r");
	zmienna = fgetc(plik);
	std::cout << zmienna;
	fclose(plik);
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML demo");// utworz okno
	Menu menu(window.getSize().x, window.getSize().y);
	// petla wieczna - dopoki okno jest otwarte
	while (window.isOpen())
	{
		// w kazdej iteracji petli sprawdzaj zdarzenia
		sf::Event event;
		while (window.pollEvent(event))
		{
			// jezeli odebrano zdarzenie "Closed" zamknij okno
			if (event.type == sf::Event::Closed)
				window.close();
			//jezeli nacisnieto jakikolwiek przycisk
			if (event.type == sf::Event::KeyPressed)
			{//obsluga menu z poziomu klawiszy (strzalki)
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(50);
					menu.przesunG();
				}
					
				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(50);
					menu.przesunD();
				}
				if (menu_selected_flag == 0)
				{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Uruchamiam gre..." << std::endl;
						menu_selected_flag = 1;
						
					}
					if (zmienna > 48) {
						if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
						{
							std::cout << "Wczytaj gre..." << std::endl;
							menu_selected_flag = 2;
						}
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						std::cout << "Najlepsze wyniki..." << std::endl;
						menu_selected_flag = 3;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
					{
						std::cout << "Pomoc" << std::endl;
						menu_selected_flag = 4;
					}
						
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 4)
					{
						std::cout << "Koniec gry..." << std::endl;
						menu_selected_flag = 5;
					}
						
				}
				
					
			}			
		}
		


		// wyczysc obszar rysowania
		window.clear();
		

		// tutaj umiesc procedury rysujace...
		// window.draw(...);
		if (menu_selected_flag == 0)
			menu.draw(window);

		if (menu_selected_flag == 1) {
		
			window.clear();
			menu.draw1(window);
			fstream plik;
			plik.open("plik.txt", ios::out);
			plik << 0;
			plik.close();
			if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 9)
			{
				std::cout << "Witamy w koiloknisu" << std::endl;
				menu_selected_flag = 0;
			}
			
			if (event.key.code == sf::Keyboard::Space && menu.getSelectedItem() == 5)
			{
				std::cout << "Witamy w koiloknisu" << std::endl;
				menu_selected_flag = 6;
			}
		}
		if (menu_selected_flag == 2) {
			
			menu.draw(window);

		}
		if (menu_selected_flag == 3) {
			menu.draw(window);

		}
		if (menu_selected_flag == 4) {
			menu.draw(window);

		}

		if (menu_selected_flag == 5) {
				window.close();
		}

		if (menu_selected_flag == 6) {
			window.close();
			pies();
		}
		
		window.display();
	}

	return 0;
}