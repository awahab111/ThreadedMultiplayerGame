#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <random>
using namespace sf;
using namespace std;
int random_num();
RectangleShape initialize_grid(int area);
void draw_grid(int width, int area, RenderWindow &w ,RectangleShape &rect);
Sprite create_player(string filename, int gridlen, float scale=0.34);
void PlayerInput_1(Sprite& player, Event &e ,int size);


int main()
{
    int random = (random_num());
    // set up the grid parameters
    int gridWidth = random;
    int gridHeight = random;
    int rectSize = 65 ;

    RectangleShape rect = initialize_grid(rectSize);

    RenderWindow window(VideoMode((gridHeight*rectSize), gridWidth*rectSize), "SFML Grid");

    Sprite ch_1 = create_player("Goujo.png", gridWidth);
    Sprite ch_2 = create_player("itadori.png",gridWidth);
    Sprite ch_3 = create_player("meg.png",gridWidth);
    Sprite item = create_player("finger.png",gridWidth,0.1);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {window.close();}

            // Player Input
            if (event.type == Event::KeyPressed) {
                PlayerInput_1(ch_1, event, rectSize);
        }
        }
        window.clear(Color::Black);

        draw_grid(gridWidth, rectSize, window, rect);
        window.draw(ch_1);
        window.draw(ch_2);
        window.draw(ch_3);
        window.draw(item);


        window.display();
    }
    
    return 0;
}

int random_num(int upper, int lower){
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<int> dist(1, 14);
    return dist(engine);
}

RectangleShape initialize_grid(int area){
    RectangleShape rect(Vector2f(area, area));
    rect.setFillColor(Color::Green);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(Color::White);
    return rect;
}


void draw_grid(int width, int area, RenderWindow &w , RectangleShape &rect){
    // draw the grid
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < width; x++) {
            rect.setPosition(Vector2f(x * area, y * area));
            w.draw(rect);
        }
    }
    
}

void PlayerInput_1(Sprite& player, Event &e , int size){
    if (e.key.code == Keyboard::Left && player.getPosition().x > 65) {
        // Move player left
        player.move(-65.f, 0.f);
    } else if (e.key.code == Keyboard::Right && player.getPosition().x < 900 ) {
        // Move player right
        player.move(65.f, 0.f);
    } else if (e.key.code == Keyboard::Up  && player.getPosition().y > 65) {
        // Move player left
        player.move(0.f, -65.f);
    } else if (e.key.code == Keyboard::Numpad2  && player.getPosition().y <900) {
        // Move player right
        player.move(0.f, +65.f);
    }
}

Sprite create_player(string filename, int gridlen, float scale){

    // generate a random number between 1-14
    int random_width = random_num(14,1);
    int random_height = random_num(14,1);

    // Taking texture for the player 
    Texture * playerTexture = new Texture;
    if (!playerTexture->loadFromFile(filename)) {
        cout << "Error Loading "<< filename << endl;
    }
    playerTexture->setSmooth(true);

    // Applying texture
    Sprite playerSprite;
    playerSprite.setTexture(*playerTexture);
    playerSprite.setPosition(20.f, 1.f);
    playerSprite.move(random_width * 65, random_height * 65);
    playerSprite.scale(scale, scale);
    return playerSprite;

}
