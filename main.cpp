#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
using namespace sf;
using namespace std;


int main()
{
    // set up the grid parameters
    int random = ((random_num(99, 10) * 5)/675)%25;
    if (random < 10){random+=15;}
    int gridWidth = random;
    int gridHeight = random;
    int rectSize = 65 ;
    RectangleShape rect = initialize_grid(rectSize);

    //create window to display
    RenderWindow window(VideoMode((gridHeight*rectSize), gridWidth*rectSize), "SFML Grid");

    //Players
    Player characters[3] = { Player("resources/Goujo.png", gridWidth, rectSize),Player("resources/itadori.png",gridWidth, rectSize),Player("resources/meg.png",gridWidth, rectSize)};

    //Items
    Item * finger[20];
    for (int i = 0; i < 20; i++){
        finger[i] = new Item("resources/finger.png", gridWidth, rectSize);
    }
    

    //Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {window.close();}

            // Player Input
            if (event.type == Event::KeyPressed) {
                characters[0].PlayerInput_1(event, rectSize);
                characters[1].PlayerInput_2(event, rectSize);
                characters[2].PlayerInput_3(event, rectSize);
            }
        }

        //Gathering items
        bool gamefinish = true;
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 20; i++){
                if (finger[i]->isColliding(characters[j].playerSprite)){
                    finger[i]->setPosition(999,999);
                    finger[i]->setActive(false);
                }
                if (finger[i]->getActive() == true){gamefinish = false;}
            }
            if (gamefinish){ cout << "Game Finished" << endl; return 0;}
            
        }

        //Updating window       

        window.clear(Color::Black);

        draw_grid(gridWidth, rectSize, window, rect);

        for (int i = 0; i < 3; i++){window.draw(characters[i].playerSprite);}
        for (int i = 0; i < 20; i++){window.draw(finger[i]->itemSprite);}
        
        window.display();
    }
 
    
} 
         