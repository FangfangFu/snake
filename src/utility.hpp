#ifndef UTILITY_HPP
#define UTILITY_HPP

// Convert game coordinate into pixel
int ConvertToPixel(int playerPosition){
    return playerPosition * 64;
}
// Convert pixel into game coordinate
int ConvertToGameCoordinate(int pixelPosition){
    return pixelPosition / 64;
}


#endif //UTILITY_HPP