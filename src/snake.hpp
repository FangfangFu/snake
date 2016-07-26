#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cstdlib>
enum class Direction {UP, DOWN, LEFT, RIGHT};

class Player {
private:
    int startX;
    int startY;
    Direction startDirection;
    float timeElapsed;
    const float MOVE_TIME = 250.0f;

public:
    //Constructor
    Player(const int x, const int y, const Direction direction){
        startX = x;
        startY = y;
        startDirection = direction;
    }
    Direction GetDirection(){
        return startDirection;
    }
    void SetDirection(const Direction direction) {
        startDirection = direction;   
    }
    const int GetPositionX(){
        return startX;
    }
    const int GetPositionY(){
        return startY;
    }
    void UpdatePosition(float elapsed){
        timeElapsed += elapsed;
        if (timeElapsed > MOVE_TIME){
            if (startDirection == Direction::UP){
                startY -= 1;
                if(startY < 1){
                    startY = 1;
                }
            }else if (startDirection == Direction::DOWN){
                startY += 1;
                if(startY > 13){
                    startY = 13;
                }
            }else if (startDirection == Direction::LEFT){
                startX -= 1;
                if(startX < 1){
                    startX = 1;
                }
            }else if (startDirection == Direction::RIGHT){
                startX += 1;
                if(startX > 18){
                    startX = 18;
                }
            }
            timeElapsed -= MOVE_TIME;
        }
        
    }//This function should move the Player position by 1 for either X or Y based on the current Direction.
    

};
#endif //SNAKE_HPP