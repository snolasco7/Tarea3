#include "Character1.h"

std::string toString1(int number)
{
    if (number == 0)
        return "0";

    if(number < 0)
        return "-"+toString1(-number);

    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

Character1::Character1(SDL_Renderer* renderer)
{
    moves["estatica"]=getMove(renderer,"estatica",4);
    moves["caminar"]=getMove(renderer,"caminar",5);
    moves["golpe"]=getMove(renderer,"golpe",3);
    moves["patada"]=getMove(renderer,"patada",6);


    this->current_move = "caminar";
    this->current_sprite = 0;
    this->current_sprite_frame = 0;
}

Move* Character1::getMove(SDL_Renderer *renderer, string name, int sprite_amount)
{
    vector<Sprite*>sprites;
    for(int i=1;i<=sprite_amount;i++)
    {
        string path="assets/" + name + "/" + toString1(i) + ".png";
        sprites.push_back(new Sprite(renderer,path,10));
    }
    return new Move(renderer,sprites);
}

Character1::~Character1()
{
    //dtor
}

void Character1::logic()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if( currentKeyStates[ SDL_SCANCODE_C ] )
    {
        this->current_move = "caminar";
        this->current_sprite = 0;
    }
    if( currentKeyStates[ SDL_SCANCODE_V ] )
    {
        this->current_move = "golpe";
        this->current_sprite = 0;
    }
    if( currentKeyStates[ SDL_SCANCODE_B ] )
    {
        this->current_move = "patada";
        this->current_sprite = 0;
    }

    current_sprite_frame++;
    if(current_sprite_frame>=moves[current_move]->sprites[current_sprite]->frames)
    {
        current_sprite++;
        if(current_sprite>=moves[current_move]->sprites.size())
        {
            current_move= "estatica";
            current_sprite=0;
        }
        current_sprite_frame=0;
    }
}

void Character1::draw()
{
    moves[current_move]->draw(current_sprite);
}
