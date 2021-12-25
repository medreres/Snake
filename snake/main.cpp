
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ResourcePath.hpp"
#include <iostream>
using namespace sf;
using namespace std;
const int height = 600;
const int width = 800;
const int loop_pause = 130;
void if_eat(RectangleShape& player,RectangleShape& fruit,RectangleShape& tail,vector<RectangleShape>& tails)
{
    if(player.getPosition()==fruit.getPosition())
    {
        tail.setPosition(player.getPosition());
        tails.push_back(tail);
        fruit.setPosition(rand()%(width/20), rand()%(height/20));
        cout << fruit.getPosition().x << " " << fruit.getPosition().y << endl;
    }
}
int main(int, char const**)
{
    srand(time(NULL));
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //physics
    int direcion = -1;//0 upwards1 downwards,3 right,4 left
    Clock clock;
    //player
    sf::RectangleShape player (sf::Vector2f(40,40));
    player.setFillColor(Color(70,115,232));
    player.setPosition(width/2,height/2);
    player.setOrigin(player.getSize().x/2, player.getSize().y/2);
    //body
    RectangleShape tail (sf::Vector2f(40,40));
    tail.setFillColor(Color(70,115,232));
    //tail.setPosition(player.getPosition().x, player.getPosition().y+player.getSize().y);
    tail.setOrigin(player.getSize().x/2, player.getSize().y/2);
    vector<RectangleShape> tails;
    int last = tails.size()-1;
    
    
    //fruit
    RectangleShape fruit(sf::Vector2f(40,40));
    fruit.setFillColor(Color(231, 71, 29));
    fruit.setOrigin(player.getSize().x/2, player.getSize().y/2);
    fruit.setPosition(width/2+40, height/2+40);
    
    // Start the game loop
    while (window.isOpen())
    {
       
        sleep(Time(milliseconds(loop_pause)));
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            Time elapsed = clock.getElapsedTime();
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::H)
            {
                tail.setPosition(player.getPosition());
                tails.push_back(tail);
            }
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::W)
            {
                direcion = 0;
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::S)
            {
                direcion = 1;
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::D)
            {
                direcion = 2;
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::A)
            {
                direcion = 3;
            }
        }
        
        //moving player
        if_eat(player, fruit, tail, tails);
        if(last<0 && tails.size()!=0)
        {
            last = tails.size()-1;
        }
        if(tails.size()!=0)
        {
            tails[last--].setPosition(player.getPosition());
        }
        switch(direcion)
        {
            case 0:
                player.move(0, -player.getSize().y);
                break;
            case 1:
                player.move(0, player.getSize().y);
                break;
            case 2:
                player.move(player.getSize().x,0);
                break;
            case 3:
                player.move(-player.getSize().x,0);
                break;
            default:
                break;
        }
        if(player.getPosition().x<0)
        {
            player.setPosition(width, player.getPosition().y);
        }
        if(player.getPosition().x>width)
        {
            player.setPosition(0, player.getPosition().y);
        }
        if(player.getPosition().y>height)
        {
            player.setPosition(player.getPosition().x, 0);
        }
        if(player.getPosition().y<0)
        {
            player.setPosition(player.getPosition().x, height);
        }
       //earing fruit
        
        // Clear screen
        window.clear(Color(170, 215, 81));
        window.draw(fruit);
        window.draw(player);
        for (int i  = 0; i<tails.size(); i++)
        {
            window.draw(tails[i]);
        }
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
