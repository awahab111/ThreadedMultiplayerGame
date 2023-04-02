#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <queue>
#include <functional>
using namespace std;
using namespace sf;

int random_num(int upper, int lower);
RectangleShape initialize_grid(int area);
void draw_grid(int width, int area, RenderWindow &w ,RectangleShape &rect);

queue<function<void()>> functionQueue[3];
queue<function<void()>> ItemsQueue[3];



class Player {
private:
    Texture playerTexture;
    float positionX;
    float positionY;
    int points;
public:
    FloatRect boundingbox;
    Sprite playerSprite;
    
    Player(std::string filename, int gridlen, int area);
    void PlayerInput_1(Event &e , int size);
    void PlayerInput_2(Event &e , int size);
    void PlayerInput_3(Event &e , int size);
    void move(float a, float b);
    void increment_points();
    int getpoints();
    void update_position();

};

Player::Player(std::string filename, int gridlen, int area) {
    int random_width = random_num(gridlen - 1, 1);
    int random_height = random_num(gridlen -1, 1);

    // Taking texture for the player
    if (!playerTexture.loadFromFile(filename)) {
        std::cout << "Error Loading " << filename << std::endl;
    }
    playerTexture.setSmooth(true);

    // Applying texture
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(20.f, 1.f);
    playerSprite.move(random_width * area, random_height * area);
    playerSprite.scale(0.32f, 0.32f);

    //Getting player position
    positionX = playerSprite.getPosition().x;
    positionX = playerSprite.getPosition().y;

    //Creating a bounding box
    boundingbox = playerSprite.getGlobalBounds();

    points = 0;
}

void Player::PlayerInput_1(Event &e , int size) {

    if (e.key.code == Keyboard::Numpad4 && playerSprite.getPosition().x > size) {
        // Move playerSprite left
        functionQueue[0].push(bind(&Player::move,ref(*this),(-1*size), 0.f));
        
    
    } 
    else if (e.key.code == Keyboard::Numpad6 && playerSprite.getPosition().x < size * 14 ) {
        // Move playerSprite right
        functionQueue[0].push(bind(&Player::move,ref(*this),(size), 0.f));
        
    } 
    else if (e.key.code == Keyboard::Numpad8  && playerSprite.getPosition().y > size) {
        // Move playerSprite up
        functionQueue[0].push(bind(&Player::move,ref(*this),0,(-1*size)));
        
    } 
    else if (e.key.code == Keyboard::Numpad2  && playerSprite.getPosition().y <size * 14) {
        // Move playerSprite down
        functionQueue[0].push(bind(&Player::move,ref(*this),0,(size)));
    }
    
}

void Player::PlayerInput_2(Event &e , int size) {
   if (e.key.code == Keyboard::A && playerSprite.getPosition().x > size) {
        // Move playerSprite left
        functionQueue[1].push(bind(&Player::move,ref(*this),(-1*size), 0.f));
    
    } 
    else if (e.key.code == Keyboard::D && playerSprite.getPosition().x < size * 14 ) {
        // Move playerSprite right
        functionQueue[1].push(bind(&Player::move,ref(*this),(size), 0.f));
        
    } 
    else if (e.key.code == Keyboard::W  && playerSprite.getPosition().y > size) {
        // Move playerSprite up
        functionQueue[1].push(bind(&Player::move,ref(*this),0,(-1*size)));
        
    } 
    else if (e.key.code == Keyboard::S  && playerSprite.getPosition().y <size * 14) {
        // Move playerSprite down
        functionQueue[1].push(bind(&Player::move,ref(*this),0,(size)));
    }
}

void Player::PlayerInput_3(Event &e , int size) {
   if (e.key.code == Keyboard::H && playerSprite.getPosition().x > size) {
        // Move playerSprite left
        functionQueue[2].push(bind(&Player::move,ref(*this),(-1*size), 0.f));
    
    } 
    else if (e.key.code == Keyboard::K && playerSprite.getPosition().x < size * 14 ) {
        // Move playerSprite right
        functionQueue[2].push(bind(&Player::move,ref(*this),(size), 0.f));
        
    } 
    else if (e.key.code == Keyboard::U  && playerSprite.getPosition().y > size) {
        // Move playerSprite up
        functionQueue[2].push(bind(&Player::move,ref(*this),0,(-1*size)));
        
    } 
    else if (e.key.code == Keyboard::J  && playerSprite.getPosition().y <size * 14) {
        // Move playerSprite down
        functionQueue[2].push(bind(&Player::move,ref(*this),0,(size)));
    }
}

void Player::increment_points(){
    points++;
}

void Player::move(float a, float b){
    playerSprite.move(a, b);
}

int Player::getpoints(){
    return points;
}

void Player::update_position() {
    positionX = playerSprite.getPosition().x;
    positionX = playerSprite.getPosition().y;
}


void* PlayerInput_1_wrapper(void* args) {
  auto [me, e, area] = *static_cast<tuple<Player*, Event*, int>*>(args);
  me->PlayerInput_1(*e, area);
  return NULL;
}
void* PlayerInput_2_wrapper(void* args) {
  auto [me, e, area] = *static_cast<tuple<Player*, Event*, int>*>(args);
  me->PlayerInput_2(*e, area);
  return NULL;
}
void* PlayerInput_3_wrapper(void* args) {
  auto [me, e, area] = *static_cast<tuple<Player*, Event*, int>*>(args);
  me->PlayerInput_3(*e, area);
  return NULL;
}


class Item { 
private:
    Texture itemtexture;
    FloatRect boundingBox;
    bool isActive;

public:
    Sprite itemSprite;
    Item(){}
    Item(std::string filename,int gridlen, int area) {
        //Load Texture
        if (!itemtexture.loadFromFile(filename)) {
            std::cout << "Error Loading " << filename << endl;
        }

        int random_width = random_num(gridlen - 1, 1);
        int random_height = random_num(gridlen -1, 1);


        itemSprite.setTexture(itemtexture);
        itemSprite.setPosition(05.f, -2.f);
        itemSprite.move(random_width * area, random_height * area);
        itemSprite.scale(0.08f, 0.08f);
        isActive = true;
        boundingBox = itemSprite.getGlobalBounds();
    }

    bool isColliding(Sprite otherBox) {
        return boundingBox.contains(otherBox.getPosition());
    }

    void setActive(bool active) {
        isActive = active;
    }

    bool getActive() {
        return isActive;
    }

    void setPosition(float x, float y) {
        itemSprite.setPosition(x, y);
    }

    FloatRect getBoundingBox() {
        return boundingBox;
    }
};




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

 
void item_collect(Item *finger, Player *characters){
    finger->setPosition(999,999);
    finger->setActive(false);
    characters->increment_points();
}

void check_collision(Player *characters, Item **finger, int player_no){
    bool gamefinish = true;
    for (int i = 0; i < 20; i++){
        if (finger[i]->isColliding(characters->playerSprite) && finger[i]->getActive()){
            functionQueue[player_no].push(bind(&item_collect, finger[i], characters)); 
        }
        if (finger[i]->getActive() == true){gamefinish = false;}
    }

}


void * check_collision_wrapper(void * args){
    auto [me, fingers, player_no] = *static_cast<tuple<Player*,Item**, int>*>(args);
    check_collision(me, fingers, player_no);
    cout << "Thread : "<< me->getpoints() << endl;
    pthread_exit(NULL);
}