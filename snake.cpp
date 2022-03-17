#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <Windows.h>

using std::cout , std::endl ;

extern const float STEP = 15.f;
sf::Vector2f SNAKE_SIZE{STEP,STEP};

struct snake_body
{   
    int x;
    int y;
    sf::RectangleShape body{SNAKE_SIZE};
    //body.setFillColor(sf::Color::Green);

};

struct direct{// (0,1):down (0,-1):up (-1,0):Left (1,0):Right
    sf::Vector2f down = sf::Vector2f{0,STEP};
    sf::Vector2f up = sf::Vector2f{0,-STEP};
    sf::Vector2f left = sf::Vector2f{-STEP,0};
    sf::Vector2f right = sf::Vector2f{STEP,0};
};
extern direct direction_;

class Snake{

    public:    
    
    int x = 0;
    int y = 0;
    int end_x;
    int end_y;
    sf::RectangleShape snek_head{SNAKE_SIZE};
    std::vector<snake_body> snake_bod;
    


    void update_pos(){
        int cur_x = snek_head.getPosition().x;
        int cur_y = snek_head.getPosition().y;
        int body_x;
        int body_y;
        for (int i = 0; i < snake_bod.size(); i++){
        
            body_x = snake_bod[i].x;
            body_y = snake_bod[i].y;
            snake_bod[i].y = cur_y;
            snake_bod[i].x = cur_x;
            snake_bod[i].body.setPosition(cur_x,cur_y);
            cur_x = body_x;
            cur_y = body_y;
        }
        

    }
    void draw(sf::RenderWindow& win){
        for (int i = 0; i < snake_bod.size(); i++)
        {
        win.draw(snake_bod[i].body);
        }
        win.draw(snek_head);
        
        
    }
    void wrap(){
    int cur_x = snek_head.getPosition().x;
    int cur_y = snek_head.getPosition().y;
        if (cur_x < 0 ) snek_head.setPosition(405,cur_y);
        if (cur_x >= 405) snek_head.setPosition(0,cur_y);
        if (cur_y < 0 ) snek_head.setPosition(cur_x,405);
        if (cur_y >= 405) snek_head.setPosition(cur_x,0);
    }

    void makethatshitnotkillitself(sf::Vector2f &dir,sf::Vector2f &last_direction){
        if (dir == direction_.down){
            if (last_direction == direction_.up){
                dir = direction_.up;
            }
        }
        if (dir == direction_.up){
            if (last_direction == direction_.down){
                dir = direction_.down;
            }
        }
        if (dir == direction_.left){
            if (last_direction == direction_.right){
                dir = direction_.right;
            }
        }
        if (dir == direction_.right){
            if (last_direction == direction_.left){
                dir = direction_.left;
            }
        }

    }

    void move(sf::Vector2f &dir,sf::Vector2f &last_direction){
    update_pos();
    makethatshitnotkillitself(dir,last_direction);
    snek_head.move(dir.x,dir.y);
    wrap();
    self_collision();
    }

    void add_body(){
    snake_bod.push_back(snake_body());
    snake_bod.back().body.setPosition(-15,-15);
    for (int i = 0; i < snake_bod.size(); i++){
        snake_bod[i].body.setFillColor(sf::Color::Green);
    }
    snek_head.setFillColor(sf::Color::Yellow);
    update_pos();
    }


    bool self_collision(){
        for (int i = 0; i < snake_bod.size(); i++){
    
            if(snek_head.getPosition().x == snake_bod[i].x && snek_head.getPosition().y == snake_bod[i].y  ){
                return 1 ;
            }
        }
        return 0;
    }

    bool text_selection(sf::RenderWindow& win,sf::Text &text,sf::Vector2f mousePos,bool m_pressed, bool end_game,int Xoffset=0,int Yoffset=0){
        int size_ = text.getCharacterSize() +10;
        if (text.getGlobalBounds().contains(mousePos) and end_game == 1 ){
            text.setCharacterSize(size_);
            text_center(win,text,Xoffset,Yoffset);
            win.draw(text);
            text.setCharacterSize((size_-10));
            text_center(win,text,Xoffset,Yoffset);
        } else if (end_game) {
            win.draw(text);
        }
        if(m_pressed and end_game and text.getGlobalBounds().contains(mousePos)) return 1;
        else return 0;
    }
    void text_center(sf::RenderWindow& win,sf::Text &text,int Xoffset=0,int Yoffset=0){
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin((int)(textRect.left + textRect.width/2.0f),(int)(textRect.top  + textRect.height/2.0f));
        text.setPosition(sf::Vector2f((int)(win.getView().getCenter().x+Xoffset),(int)(win.getView().getCenter().y+Yoffset)));
        //int conversion is needed to make the text not blurry
    }
};


class Apple{
    public:
    int x = -15;
    int y = -15;
    int score = 0;
    sf::RectangleShape body{SNAKE_SIZE};
    Apple()
    {
    body.setFillColor(sf::Color::Red);
    new_pos();
    }

    void new_pos(){
        int x_ = x;
        int y_ = y;
        int a;
        bool loop = true;
        for(;;){
            a = (rand()%385);
            if (a%15 == 0){
                x = a;
                break;
            }}
        for(;;){
            a = (rand()%385);
            if (a%15 == 0){
                y = a;
                break;
            }
        }
        body.setPosition(x,y);
    }

    void draw(sf::RenderWindow& win){
        win.draw(body);
    }

    bool check_collision(Snake snake ){
            if(snake.snek_head.getGlobalBounds().intersects(body.getGlobalBounds())){
                snake.add_body();
                new_pos();
                ++score;
                return 1;}
            return 0;
    }

};
