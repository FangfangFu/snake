#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cstdlib>
#include <iostream>
#include <deque>

enum class Direction {UP, DOWN, LEFT, RIGHT};
struct Position {
    int x;
    int y;
};
class Player {
private:
    int startX;
    int startY;
    int originalX;
    int originalY;
    Direction startDirection;
    Direction originalDirection;
    float timeElapsed;
    const float MOVE_TIME = 150.0f;
    int length;
    std::deque<Position> queue;
    Position position;

public:
    //Constructor
    Player(const int x, const int y, const Direction direction){
        startX = x;
        startY = y;
        originalX = x;
        originalY = y;
        startDirection = direction;
        originalDirection = direction;
        length = 1;
        position.x = x;
        position.y = y;
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
                position.y = startY;
                if(startY < 1){
                    ResetPlayer();
                    return true;
                }
            }else if (startDirection == Direction::DOWN){
                startY += 1;
                position.y = startY;
                if(startY > 13){
                    ResetPlayer();
                    return true;
                }
            }else if (startDirection == Direction::LEFT){
                startX -= 1;
                position.x = startX;
                if(startX < 1){
                    ResetPlayer();
                    return true;
                }
            }else if (startDirection == Direction::RIGHT){
                startX += 1;
                position.x = startX;
                if(startX > 18){
                    ResetPlayer();
                    return true;
                }
            }
            for(int i = 0; i < queue.size(); ++i){
                if(startX == queue[i].x & startY == queue[i].y){
                    ResetPlayer();
                    return true;
                }
            }
            timeElapsed -= MOVE_TIME;
            if (queue.size() == length){
                queue.push_front(position);
                queue.pop_back();
            } else{
                queue.push_front(position);
            }
            return false;
        }
        
    }

    ResetPlayer(){
        startX = originalX;
        startY = originalY;
        startDirection = originalDirection;
        position.x = originalX;
        position.y = originalY;
        length = 1;
        queue.clear();
        queue.push_front(position);
    }

    
    std::deque<Position> GetPositions(){
        return queue;
    }
    
    IncrementLength(){
        ++length;
    }

};

#endif //SNAKE_HPP