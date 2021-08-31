#include "print.h"
#include "data_structues.h"

using namespace std;


int main(){
    srand(time(0)); // seed it ..
    Game game(2,0,20); // human vs ai ? 
    game.gameLoop();
    return 0;
}
