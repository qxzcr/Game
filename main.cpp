#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits//stdc++.h>
#include <sstream>
using namespace sf;


void menu(RenderWindow & window) {
	Texture Texture1, Texture2, Texture3, aboutTexture, menuBackground;
	Texture1.loadFromFile("images/newgame.png");  //Przesylamy zdjecia z tekstem
	Texture2.loadFromFile("images/about.png");
	Texture3.loadFromFile("images/exit.png");
	aboutTexture.loadFromFile("images/aboutt.png");
	menuBackground.loadFromFile("images/backgg.jpg");  //Przesylay Tlo 
	Sprite menu1(Texture1), menu2(Texture2), menu3(Texture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(70, 30); //Pozycja teksta
	menu2.setPosition(50, 90);
	menu3.setPosition(125, 150);
	menuBg.setPosition(345, 0);
 
	while (isMenu)
	{ 
	Event event;
  		while (window.pollEvent(event)) 
		  {
		   if (event.type == Event::Closed)
		    window.close();
		
		menu1.setColor(Color::White);  //Przywrucimy oryginalny kolor do obrazu 
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(sf::Color(245, 245, 220));  //Zamalujemy nad oknem menu  
 
		if(IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { //Jesli najedziemy kursorem na element, zostanie on podswietlony 
				menu1.setColor(Color::Black); menuNum = 1; 
				}
		if(IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { 
				menu2.setColor(Color::Black); menuNum = 2; 
				}
		
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { 
				menu3.setColor(Color::Black); menuNum = 3;
		 		} 
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false; //
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		
		window.display();
	}
}
}
View view;

void PlayerCordinate(float x, float y) { 
	float tempX = x; 
	float tempY = y;
	if (x < 320) {
		tempX = 320;
	}
	if (y < 240){
		tempY = 240;	
	} 
	if (y > 554){
		tempY = 554;
	} 
	if (x > 954) {
		tempX = 954;
	}
	view.setCenter(tempX, tempY);  //Ustawiamy centrum widoku na wspó³rzêdne tempX i tempY
}

 

int getCurrentMission(int x){ //Funkcja numeru misji, ktora zmienia numer misji, w zaleznosci od wspolrzednych gracza X
	int mission = 0; 
	if ((x>0) && (x<100)){ //Wprowadzamy gracza do gry 
		mission = 0; } 
 
	return mission; //Funkcja zwraca numer misji 
} 
std::string getTextMission(int currentMission) {
 
	std::string missionText = ""; //Tekst misji i jej inicjalizacja 
	switch (currentMission)  //Pobierany jest numer misji i, w zaleznosci od niego, zmiennej missionText przypisany jest inny tekst 
	{
	case 0: missionText = "\nGame Manual.\n The task is to\ntake 10 keys\nw within 60s.\n  You can press\nthe arrows or the\nletters W, A, S, D \nto walk\n  Tips: flowers are \npoisonous,\nhearts bring you\nback to life.\nGood luck!"; 
	break;
	}
	
	return missionText;//Funkcja zwraca tekst
}; 

const int HieghtMap = 25;  //Wysokosc mapy
const int WidthMap = 40;  //Szerokosc mapy 
 
 
sf::String MainMap[HieghtMap] = { //Pole dostepne dla gracza
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};


class Player {             //Klasa gracza
	private: float x, y;
	public:
	float w, h, speed,dx,dy;
	int dir, Score, health; //Nowa zmienna, która przechowuje ¿ycie gracza
	bool life; //zmienna zywotnosc, logiczna
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H){
		dx = 0;   //zainicjowa³ zmienna zycia w konstruktorze
		dy = 0; 
		dir = 0; 
		speed = 0; 
		Score = 0; 
		health = 100; 
		life = true; //zainicjowa³ zmienna zycia logicznego
		File = F;
		w = W; 
		h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));  // Tworzenie maski koloru
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; 
		y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h)); 
	}
	void update(float time) 
	{
		switch (dir)
		{
			case 0: 
				dx = speed; // Ustalanie kierunku ruchu w prawo 
				dy = 0;  // Brak ruchu w osi Y 
				break;
			case 1: 
				dx = -speed; 
				dy = 0; 
				break;
			case 2: 
				dx = 0; 
				dy = speed; 
				break;
			case 3: 
				dx = 0; 
				dy = -speed; 
				break;
		}
		x += dx * time;  // Aktualizacja pozycji X z uwzglednieniem predkosci i czasu 
		y += dy * time;  // Aktualizacja pozycji X z uwzglednieniem predkosci i czasu
		speed = 0;  // Resetowanie prêdkosci do zera
		sprite.setPosition(x, y);   // Ustawienie pozycji sprajtu na nowych wartosciach X i Y
		MapInter();  // Wywolanie funkcji odpowiedzialnej za interakcje z map
		if (health <= 0){ //Jesli zycia sa mniejsze lub rowne 0, to gracz umiera  
			life = false; 
		}
	}
	float getplayercoordinateX(){	
		return x;
	}
	float getplayercoordinateY(){
		return y;
	}
	void MapInter()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (MainMap[i][j] == '0' || MainMap[i][j] == 'r'){
					if (dy > 0){
					y = i * 32 - h;  // Ustala nowa pozycje y
					}
					if (dy<0){
					y = i * 32 + 32;
					}
					if (dx>0){
					x = j * 32 - w;
					}
					if (dx < 0){
					x = j * 32 + 32;
					}
				}
			if (MainMap[i][j] == 'k') { //Jesli wzieli klucz, zmienna Score=Score+1 
				Score++;
				MainMap[i][j] = ' '; //Usuniêeto klucza
			}
			if (MainMap[i][j] == 'f') { //Jesli wzieli kwiat, zmienna health zmiensza sie na 20 
				health -= 20;
				MainMap[i][j] = ' '; //Usuniêeto kwiat
			}
			if (MainMap[i][j] == 'h') { //Jesli wzieli serce, zmienna health zwieksza sie na 20 
				health += 20;
				MainMap[i][j] = ' '; //Usuniêeto serce
			}
		}
	}
};
int main()
{ 

	RenderWindow window(VideoMode(1100, 740), "Adventure");
	menu(window); 
	view.reset(FloatRect(0, 0, 640, 480));
	Font font;
	font.loadFromFile("JdCarnivalBlack.ttf");  //Przekaz plik czcionki do naszej czcionki 
	Text textFinish("", font, 40);  //Utwórzymy obiekt tekstowy, wrzucimy linie, czcionke, rozmiar czcionki (w pikselach) do obiektu tekstowego
	textFinish.setColor(Color::Yellow);  //Pomalowal tekst na zolty
	textFinish.setStyle(Text::Bold);  //Pogrubiony tekst 
	
	Text text("", font, 20);
	text.setColor(Color::Yellow);
	text.setStyle(Text::Bold);
	
	Text missionText("", font, 20);
	missionText.setColor(Color::Black);
	missionText.setStyle(Text::Bold);
	
	Text textBegining("", font, 50);
	textBegining.setColor(Color::Black);
	textBegining.setStyle(Text::Bold);
	
	sf::SoundBuffer buf; 
	buf.loadFromFile("sounds/keys.ogg");// ??? ????????? ? ????? ??? ??
	sf::Sound keys;
	keys.setBuffer(buf);
	
	sf::SoundBuffer buffer; 
	buffer.loadFromFile("sounds/win.ogg");// ??? ????????? ? ????? ??? ??
	sf::Sound win;
	win.setBuffer(buffer);//??????? ???? ? ????????? ? ???? ???? ?? ??????
	 
	sf::SoundBuffer buffers; 
	buffers.loadFromFile("sounds/quest.ogg");// ??? ????????? ? ????? ??? ??
	sf::Sound quest;
	quest.setBuffer(buffers);
	
	sf::SoundBuffer buff; 
	buff.loadFromFile("sounds/gameover.ogg");
	sf::Sound over;
	over.setBuffer(buff);
	
	Music music;
	music.openFromFile("sounds/music.ogg");
	music.play();
	music.setVolume(40);
	music.setLoop(true); 
	
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	
	Image questImage;
	questImage.loadFromFile("images/mission.png");
	questImage.createMaskFromColor(Color(0, 0, 0));
	Texture questTexture;
	questTexture.loadFromImage(questImage);
	Sprite sQuest;
	sQuest.setTexture(questTexture);
	sQuest.setTextureRect(IntRect(0, 0, 340, 510)); // Konwersja typow 
	sQuest.setScale(0.6f, 0.6f);  //Nieznacznie zmniejszono obraz, z tego wynika rozmiar stal sie mniejszy 
	
	Player p("hero.png", 80, 80, 75.0, 75.0);
	
	bool showMissionText = true; //Zmienna logiczna odpowiedzialna za pojawienie siê tekstu misji na ekranie 
	
	float currentFrame = 0;
	Clock clock;
	Clock gameTimeClock;  //Czas gry zmienny, bedziemy przechowywac czas gry tutaj
	int gameTime = 0; //Og³oszono czas gry, zainicjowano.
	srand(time(0));
	for(int k = 0; k < 10; k++){
		int i = rand() % 18 + 6;
		int j = rand() % 33 + 6;
		MainMap[i][j] = 'r';
	} 
	for(int k = 0; k < 10; k++){
		int i = rand() % 23 + 1;
		int j = rand() % 38 + 1;
		MainMap[i][j] = 'f';
	}
	for(int k = 0; k < 10; k++){
		int i = rand() % 23 + 1;
		int j = rand() % 38 + 1;
		MainMap[i][j] = 'h';
	}
	for(int k = 0; k < 11; k++){
		int i = rand() % 23 + 1;
		int j = rand() % 38 + 1;
		MainMap[i][j] = 'k';
	}
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life){ 											//Czas gry w sekundach idzie do przodu, dopóki gracz zyje
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
		} else { 
		view.move(0.8, 0); }
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
    			window.close();
			if (event.type == Event::KeyPressed)  //Zdarzenie nacisniecia 
			if ((event.key.code == Keyboard::Tab)) { //jesli TAB 
				
				switch (showMissionText) {  //Przelacznik, ktory reaguje na zmienna logiczna showMissionText 
 
				case true: {
				quest.play();
				std::ostringstream task;  //Ciag tekstowy misji
				task << getTextMission(getCurrentMission(p.getplayercoordinateX())); //wywolywana jest funkcja getTextMission (zwraca tekst misji), ktora przyjmuje funkcje getCurrentMission jako argument (ktora zwraca numer misji), a ta funkcja przyjmuje funkcje p.getplayercoordinateX() jako argument (ta funkcja zwraca wspó³rzêdna X odtwarzacza) 
				missionText.setString("\n" + task.str());
				missionText.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
				sQuest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
				showMissionText = false; //Ta linia pozwala usunac wszystko, co wyswietlilismy na ekranie 
				break;  //wyjdzejy, aby nie spe³niac "falszywego" warunku (ktory znajduje siê ponizej) 
				}
				case false: {
					text.setString("");  //Jesli Tab nie zostanie nacisniety, caly ten tekst jest pusty 
					showMissionText = true;  // Ta linia pozwala ponownie nacisnac Tab i uzyskac dane wyjsciowe na ekranie 
					break;
					}
				}
			}
		}
		if (p.life){    //Sterowanie postacia z animacji
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
				p.dir = 1; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;{
					p.sprite.setTextureRect(IntRect(75 * int(currentFrame), 75, 75, 75));
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
				p.dir = 0; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;{
					p.sprite.setTextureRect(IntRect(75 * int(currentFrame), 150, 75, 75));
				}				
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
				p.dir = 3; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;{
					p.sprite.setTextureRect(IntRect(75 * int(currentFrame), 220, 75, 75));
				}				
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
				p.dir = 2; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;{
					p.sprite.setTextureRect(IntRect(75 * int(currentFrame), 0, 75, 75));
				}				
			}
			PlayerCordinate(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		p.update(time);
		window.setView(view);
		window.clear();
		for (int i = 0; i < HieghtMap; i++){    //Rysujemy mape
			for (int j = 0; j < WidthMap; j++){
				if (MainMap[i][j] == ' ')  {
					s_map.setTextureRect(IntRect(0, 0, 32, 32));
				}
				if (MainMap[i][j] == 'k')  {
					s_map.setTextureRect(IntRect(32, 0, 32, 32));
				}
				if ((MainMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));  //Krawedz mapy 
				if ((MainMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));  //Kwiat
				if ((MainMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32)); //Serce
				if ((MainMap[i][j] == 'r')) s_map.setTextureRect(IntRect(165, 0, 32, 32)); //Kamien
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}
		std::ostringstream playerHealthString, gameTimeString, playerScoreString; //Zadeklarowana zmienna zdrowia i czasu   
		playerHealthString << p.health; //Tworzenie ciagu znaków
		gameTimeString << gameTime;	
		playerScoreString << p.Score;
		text.setString("Health: " + playerHealthString.str() + "\nGame time: " + gameTimeString.str() + "\nKeys: " + playerScoreString.str()); //Ustawiamy ciag znakow na tekst i wywolamy powyzszy ciag za pomoca metody .str()
		text.setPosition(view.getCenter().x - 280, view.getCenter().y - 215); //Ustawiamy po;ozenie tekstu, cofajac sie od srodka kamery
		window.draw(text); //Rysujemy ten tekst
		if(p.Score == 10){
			win.play();
			textFinish.setString("You WIN!");
			textFinish.setPosition(view.getCenter().x, view.getCenter().y); 
			window.draw(textFinish);
			window.display();
			sf::sleep(sf::milliseconds(2900));
			window.close();
		}
		if(gameTime == 60 || p.health <= 0){
			over.play();
			textFinish.setString("You Loose!");
			textFinish.setPosition(view.getCenter().x, view.getCenter().y); 
			window.draw(textFinish); //Rysujemy tekst zwyciestwa 
			window.display();
			sf::sleep(sf::milliseconds(2750)); //Spimy przez kilka milisekund 
			window.close();
		}
		if(gameTime == 0){
			textBegining.setString("Nacisij TAB!");
			textBegining.setPosition(view.getCenter().x, view.getCenter().y); 
			window.draw(textBegining); //Rysujemy poczatkowy tekst
			window.display();
			sf::sleep(sf::milliseconds(1000)); //Spimy przez kilka milisekund  
		}
		if (!showMissionText) {
			missionText.setPosition(view.getCenter().x + 125, view.getCenter().y - 160);  //Pozycja ca³ego bloku tekstu
			sQuest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);	//Pozycja tla bloku		
			window.draw(sQuest);   //Narysujemy sprite'a scrolla (tlo tekstu misji), a potem tekst, wszystko to jest powiazane ze zmienna logiczna, ktora zmienia swoj stan poprzez nacisniecie TAB 
			window.draw(missionText); //Rysujemy tekst misji
		}
		window.draw(p.sprite);
		
		window.display();
	}
	return 0;
}
