#ifndef UTILITY_HPP
#define UTILITY_HPP


int ConvertToPixel(int playerPosition){
    return playerPosition * 64;
}

int ConvertToGameCoordinate(int pixelPosition){
    return pixelPosition / 64;
}


#endif //UTILITY_HPP