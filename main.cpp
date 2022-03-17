#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "snake.cpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <Windows.h>

using std::cout , std::endl ;
bool game_over = 0;
sf::Vector2f curr_direction = sf::Vector2f{0,STEP};

direct direction_;

int main(){

sf::RenderWindow window(sf::VideoMode(405, 405), "SFML works!");
//window.setFramerateLimit(60); 
//window.setVerticalSyncEnabled(1);
sf::View view(sf::FloatRect(0, 0, window.getSize().y, window.getSize().x));

sf::Font font;
if (!font.loadFromFile("src/Pixeboy.ttf")) std::cout << "Error Loading Font" << std::endl;
sf::Text gameover;
sf::Text play_again;
sf::Text exit_txt;
sf::Text score;
Snake snake;
Apple apple;

gameover.setFont(font); play_again.setFont(font);exit_txt.setFont(font);score.setFont(font);
gameover.setCharacterSize(100); play_again.setCharacterSize(50) ; exit_txt.setCharacterSize(50);score.setCharacterSize(20);
gameover.setString("Game Over");play_again.setString("Play Again"); exit_txt.setString("exit");score.setString("score: "+std::to_string(apple.score));
snake.text_center(window, gameover,0,-50); snake.text_center(window, play_again,0,50); snake.text_center(window, exit_txt,0,100);
snake.text_center(window,score,155,-(window.getSize().y/2)+9);

float dt = 0;
float dtMult;
float Time;
float Time1;
float move_t = 0.2;
bool move_b = true;
bool m_pressed = false;
sf::Vector2f last_direction;
sf::Clock clock;
snake.snake_bod.push_back(snake_body());
snake.add_body();
snake.add_body();
snake.add_body();
window.setView(view);


    while (window.isOpen())
    {   
        window.clear();
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        Time += currentTime;
        Time1 += currentTime;
        sf::Event event;

        sf::Vector2i mousePos = sf::Mouse::getPosition( window );
        sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and !(curr_direction == direction_.left)) {last_direction = curr_direction; curr_direction = direction_.right;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and !(curr_direction == direction_.right)) {last_direction = curr_direction; curr_direction = direction_.left;}         
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !(curr_direction == direction_.down))    {last_direction = curr_direction; curr_direction = direction_.up;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !(curr_direction == direction_.up))    {last_direction = curr_direction; curr_direction = direction_.down;}
            if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::H)) snake.snek_head.setPosition(0,10);

            if (event.type == sf::Event::MouseMoved){

                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
            }

            if(event.type == sf::Event::MouseButtonPressed){
                m_pressed = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
          
            }
        
        }
        if (snake.text_selection(window,play_again,mousePosF,m_pressed,game_over,0,50)){
            snake.snek_head.setPosition(0,15);
            curr_direction = direction_.down;
            game_over = 0;
            apple.score = 0;
            score.setString("score: "+std::to_string(apple.score));
            while(snake.snake_bod.size() != 4){
                snake.snake_bod.pop_back();
            }
            for (int i = 0; i < snake.snake_bod.size(); i++){
                snake.snake_bod[i].body.setPosition(-15,-15);
                snake.snake_bod[i].x = -15;
                snake.snake_bod[i].y = -15;
            }
            
        }
        if (snake.text_selection(window,exit_txt,mousePosF,m_pressed,game_over,0,100) == 1){
            exit(0);
        }

        if (Time1 <= move_t and move_b == true and game_over == 0){
            if(apple.check_collision(snake)){snake.add_body();score.setString("score: "+std::to_string(apple.score));}
            snake.move(curr_direction,last_direction);
            cout << last_direction.x <<"::"<< last_direction.y << endl;
            //cout << snake.snek_head.getPosition().x <<"::"<<snake.snek_head.getPosition().y << endl;
            move_b = false;
        }
        else if ((Time1 >= move_t)) {
            move_b = true;
            Time1 = 0;
            }
        
        if(snake.self_collision()) game_over = 1;

        if (game_over) // make it blink when dead 
        {
            window.draw(gameover);
            //window.draw(play_again);
            //window.draw(exit_txt);

        } else {

            apple.draw(window);
            snake.draw(window);
            }
        window.draw(score);
        window.display();
        m_pressed = false;

        
    }
    return 0;
    
}
// TODO:
// ADD HIGH SCORE || SPEED UP SNAKE AFTER A WHILE

