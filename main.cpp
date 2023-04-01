#include <SFML/Graphics.hpp>
#include <iostream>
#include <pthread.h>
#include <sys/wait.h>
#include "Player.h"
using namespace sf;
using namespace std;

void* PlayerInput_1_wrapper(void* args);

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
    
    pthread_t t1,t2,t3;
    pthread_attr_t detach_attr;
    pthread_attr_init(&detach_attr);
    pthread_attr_setdetachstate(&detach_attr, PTHREAD_CREATE_DETACHED);
    //Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {window.close();}

            // Player Input
            if (event.type == Event::KeyPressed) {
                

                auto args2 = make_tuple(&characters[2], &event, rectSize);
                pthread_create(&t3, &detach_attr, PlayerInput_3_wrapper, static_cast<void*> (&args2));
                auto args1 = make_tuple(&characters[1], &event, rectSize);
                pthread_create(&t2, &detach_attr, PlayerInput_2_wrapper, static_cast<void*> (&args1));
                auto args = make_tuple(&characters[0], &event, rectSize);
                pthread_create(&t1, &detach_attr, PlayerInput_1_wrapper, static_cast<void*> (&args));
                
            } 
        }
 
        for (int i = 0; i < 3; i++)
        {
            while (!functionQueue[i].empty()) {
            functionQueue[i].front()();
            functionQueue[i].pop();
            }
        }
        
        //Gathering items
        bool gamefinish = true;
        for (int j = 0; j < 3; j++)
        {
           check_collision(characters[0], finger);
        }

        
        

        // if (gamefinish){ 
        //     cout << "Game Finished" << endl;
        //     for (int i = 0; i < 3; i++){
        //         cout << "Points of " << i << " " << characters[i].getpoints() << endl ;   
        //     }
        //     return 0;
        // }

        //Updating window       

        window.clear(Color::Black);

        draw_grid(gridWidth, rectSize, window, rect);

        for (int i = 0; i < 3; i++){window.draw(characters[i].playerSprite);}
        for (int i = 0; i < 20; i++){window.draw(finger[i]->itemSprite);}
        
        window.display();
    }
 
    
} 
         
