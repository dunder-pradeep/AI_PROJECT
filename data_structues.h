#include <vector>
#include <set>

using namespace std;


//each move is characterised by x,y,z and the number..
struct point{
    int x,y,z;

    struct point operator-(const point& b){
        return {x - b.x,y - b.y,z - b.z};
    }
    struct point operator*(const int r){
        return {x*r,y*r,z*r};
    }
    struct point operator*(const point&b){
        return {y*b.z - z*b.y,z*b.x - x*b.z,x*b.y - y*b.x};
    }
    bool operator==(const point& b){
        return (x == b.x && y == b.y && z == b.z);
    }
};
struct move{
    struct point pt;
    int n;
    
    bool operator==(const move& b) const{
        return (pt.x == b.pt.x && pt.y == b.pt.y && pt.z == b.pt.z && n == b.n);
    }
};


//Player ..
//a player holds all the moves he has performed.. 
class Player{
    public:
        vector<struct move> moves;
        Player();
        // get move gets input and applies move...
        // while predict move takes in other players moves and moves accordingly
        // both return a bool indicating whether they made a line..!
        bool get_move();
        bool predictMove(set<int>&,vector<struct move>,vector<vector<vector<pair<int,int>>>>&,int,vector<vector<point>>);
        struct move getWinningMove(set<int>&,vector<vector<vector<pair<int,int>>>>,vector<struct move>,vector<vector<point>>);
        struct point getRandPoint(vector<vector<vector<pair<int,int>>>>);
        struct move getRandomMove(set<int>&,vector<vector<vector<pair<int,int>>>>&,int);
        struct move getLineFromOnePoint(set<int>&,vector<vector<vector<pair<int,int>>>>&,int,vector<struct move>,vector<vector<struct point>>);
};

// game class which maintains the order and the result of each round..
class Game{
    int p1,p2; // boolean for prediction..
    vector<vector<vector<pair<int,int>>>> grid; // maintains the grid of the current game. ie.{who owns it,what value}..
    vector<vector<struct move>> winningMovesP1,winningMovesP2;
    vector<vector<point>> collinearPoints; // precomputed collinear points..!
    set<int> availableNumbers;
    int n1,n2; // number of rounds won by player 1 and player 2..
    int round; // if even then player 1 decides if odd player 2 decides .. 
    int mxWins; // the first to win these many games is the winner..!
    Player player1,player2;
    public:
        Game(int,int,int);// takes in two int params 0 if human 1 if computer plays..2 if computer but random..
        bool validate(int,int,int,int);
        void gameLoop(); // main game loop..
        void updateWins();
        void reset(); // reset and start a new game..!

};


// method to reset all the global variables..
void reset(set<int>&,Player&,Player&);

// method to get a collinear point..
point getCollinearPoint(point,point);
// method to generate all possible collinear points in a cube..
vector<vector<point>> generateCollinearPoints();
