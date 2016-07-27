#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cstdlib>
enum class Direction {UP, DOWN, LEFT, RIGHT};

class Player {
private:
    int startX;
    int startY;
    int originalX;
    int originalY;
    Direction startDirection;
    Direction originalDirection;
    float timeElapsed;
    const float MOVE_TIME = 250.0f;

public:
    //Constructor
    Player(const int x, const int y, const Direction direction){
        startX = x;
        startY = y;
        originalX = x;
        originalY = y;
        startDirection = direction;
        originalDirection = direction;
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
    bool UpdatePosition(float elapsed){
        timeElapsed += elapsed;
        if (timeElapsed > MOVE_TIME){
            if (startDirection == Direction::UP){
                startY -= 1;
                if(startY < 1){
                    ResetPlayer();
                    return true;
                }
            }else if (startDirection == Direction::DOWN){
                startY += 1;
                if(startY > 13){
                    ResetPlayer();
                    return true;
                }
            }else if (startDirection == Direction::LEFT){
                startX -= 1;
                if(startX < 1){
                    ResetPlayer();
                    return true;
                }
            }else if (startDirection == Direction::RIGHT){
                startX += 1;
                if(startX > 18){
                    ResetPlayer();
                    return true;
                }
            }
            timeElapsed -= MOVE_TIME;
            return false;
        }
        
    }

    ResetPlayer(){
        startX = originalX;
        startY = originalY;
        startDirection = originalDirection;
    }

};
#endif //SNAKE_HPP