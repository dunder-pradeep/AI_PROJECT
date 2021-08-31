#include "data_structues.h"
#include <assert.h>
#include<iostream>
#include "print.h"

const int N = 27,MAGIC_NUMBER = 42;

void reset(set<int>& a,Player& A,Player& B){
    a.clear();
    A.moves.clear();
    B.moves.clear();
    for(int i = 1;i <= N;i++)
        a.insert(i);
}

vector<vector<point>> generateCollinearPoints(){
    vector<point> allPoints;
    vector<vector<point>> collinearLines;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            for(int k = 0;k < 3;k++){
               allPoints.push_back({i,j,k}); 
            }
        }
    }
    // choose three points and check if they are collinear..
    point origin = {0,0,0};
    for(int i = 0;i < allPoints.size();i++){
        for(int j = i + 1;j < allPoints.size();j++){
            for(int k = j + 1;k < allPoints.size();k++){
                point ij = allPoints[i] - allPoints[j],ik = allPoints[i] - allPoints[k];
                if(ij * ik == origin && i != j && j != k && i != k)
                    collinearLines.push_back({allPoints[i],allPoints[j],allPoints[k]});
            }
        }
    }
return collinearLines;
}

void print(vector<struct move> moves){
    cout << "[";
    for(struct move m:moves){
        cout << "{ " << m.pt.x <<","<<m.pt.y <<","<<m.pt.z<<","<<m.n << "} ";
    }
    cout <<"]" << endl;
}

void print(vector<struct point> points){
    cout << "[";
    for(struct point p:points){
        cout << "{ " << p.x <<","<<p.y <<","<<p.z<<"} ";
    }
    cout <<"]" << endl;
}
void print(vector<vector<struct move>> v){
    cout << "[ ";
    for(vector<struct move> m:v){
        print(m);
    }
    cout << " ]" << endl;
}

point getCollinearPoint(point a,point b,vector<vector<point>> collinearLines){
  //  // loop through all points which can be collinear..
  //  // check if there is a point of same x..
  //  int matchCount = (a.x == b.x) + (a.y == b.y) + (a.z == b.z);
  //  if(matchCount == 0){
  //      // this must be one of the main diagonals..!
  //      // check all of them because there is only 4..
  //  }
  //  else{
  //      // if there are two matches then the line just changes the third axis..
  //      // if there is only one match then it is a diagonal of some face..
  //      if(matchCount == 2){
  //         set<int> possibleValues = {0,1,2};
  //         if(a.x != b.x){
  //           // then {0,1,2} - {a.x,b.x} is the ans..so on..
  //              possibleValues.erase(a.x);
  //              possibleValues.erase(b.x);
  //              return {*possibleValues.begin(),a.y,a.z};
  //         }  
  //         else if(a.y != b.y){
  //              possibleValues.erase(a.y);
  //              possibleValues.erase(b.y);
  //              return {a.x,*possibleValues.begin(),a.z};
  //         }
  //         else if(a.z != b.z){
  //              possibleValues.erase(a.z);
  //              possibleValues.erase(b.z);
  //              return {a.x,a.y,*possibleValues.begin()};
  //         }
  //      }
  //      if(matchCount == 1){
  //           set<int> possibleD1values = {0,1,2},possibleD2values = {0,1,2}; // let it match in one dir then we retain it and for the point to be diag ,, this point should not have a match with any of the other x,y !!
  //           // if the point is mid of the face then you cannot have a 
  //           if(a.x == b.x){
  //              possibleD1values.erase(a.y);possibleD1values.erase(b.y);
  //              possibleD2values.erase(a.z);possibleD2values.erase(b.z);
  //              return {a.x,*possibleD1values.begin(),*possibleD2values.begin()};
  //           }
  //           if(a.y == b.y){
  //              possibleD1values.erase(a.x);possibleD1values.erase(b.x);
  //              possibleD2values.erase(a.z);possibleD2values.erase(b.z);
  //              return {*possibleD1values.begin(),a.y,*possibleD2values.begin()};
  //           }
  //           if(a.z == b.z){
  //              possibleD1values.erase(a.x);possibleD1values.erase(b.x);
  //              possibleD2values.erase(a.y);possibleD2values.erase(b.y);
  //              return {*possibleD1values.begin(),*possibleD2values.begin(),a.z};
  //           }
  //      }
  //  }

  //  return {-1,-1,-1};
  
  // loop through all collinear lines .. if two matches then return the third..
  for(vector<point> pts:collinearLines){
        for(int i = 0;i < 3;i++){
            for(int j = i + 1;j < 3;j++){
                if((pts[i] == a && pts[j] == b) || (pts[j] == a && pts[i] == b)){
                    set<int> s = {0,1,2};
                    s.erase(i);s.erase(j);
                    return pts[*s.begin()];
                }
            }
        }
  }
  return {-1,-1,-1};
}


Player :: Player(){

}

struct move Player :: getRandomMove(set<int>& s,vector<vector<vector<pair<int,int>>>>& grid,int who){
    cout << "get random " << endl;
    struct point randPoint = getRandPoint(grid); 
    int idx = rand() % s.size();
    set<int>::iterator it = s.begin();
    while(idx){it++;idx--;}
    int n = *it;
    grid[randPoint.x][randPoint.y][randPoint.z].first = who;
    grid[randPoint.x][randPoint.y][randPoint.z].second = *it;
    s.erase(it);
    return {randPoint,n};
}

struct move Player :: getLineFromOnePoint(set<int>& s,vector<vector<vector<pair<int,int>>>>& grid,int who,vector<struct move> moves,vector<vector<point>> collinearLines){
   // fix a point .. go through all collinear lines and check if there is one which satisfies the req cond. 
   for(struct move m : moves){
        // first verify that you have two number such that they sum upto 42 - n
       int newNumber = -1; 
       for(int i:s){
            for(int j:s){
                if(i != j && i + j == MAGIC_NUMBER - m.n)
                    newNumber = i;
            }
        }
       if(newNumber == -1)
           continue;
       // now for all lines check if there are two empty slots and one match..
       for(vector<point> line:collinearLines){
            bool match = false;
            for(int i = 0;i < 3;i++)
                if(line[i] == m.pt)
                    match = true;
            if(!match)
                continue;
            int empty = 0;
            point emptyPoint;
            for(int i = 0;i < 3;i++){
                if(grid[line[i].x][line[i].y][line[i].z].first == -1){
                    empty++;
                    emptyPoint = line[i];
            }
            if(empty != 2)
                continue;
            grid[emptyPoint.x][emptyPoint.y][emptyPoint.z].first = who;
            grid[emptyPoint.x][emptyPoint.y][emptyPoint.z].second = newNumber;
            s.erase(newNumber);
            return {emptyPoint,newNumber};
       }
       }
   }
   return {-1,-1,-1,-1};
}

bool Player :: predictMove(set<int>& s,vector<struct move> opponentMoves,vector<vector<vector<pair<int,int>>>>& grid,int who,vector<vector<point>> collinearLines){
        // first try to see if there is a point which is not taken if taken wins you the round !!
        struct move winMove = getWinningMove(s,grid,moves,collinearLines);
        if(winMove.n != -1){
            cout << "This player did a winning move !" << endl;
            // this player won.. so add the move to list and return true.
            moves.push_back(winMove);
            
            grid[winMove.pt.x][winMove.pt.y][winMove.pt.z].first = who;
            grid[winMove.pt.x][winMove.pt.y][winMove.pt.z].second = winMove.n;
            s.erase(winMove.n);
            return true;
        }
        
        // if that is not possible aswell then pick a point such that after you pick it  you move to a state where you need one more move to win..ie pick a point st ..
        // 1. a point in moves is already present in the line
        // 2. there are 2 free points in that line .
        // 3. obviously the line is collinear..!
        struct move betterThanRandom = getLineFromOnePoint(s,grid,who,moves,collinearLines);
        if(betterThanRandom.n != -1){
            cout << "Did a better move than random.. !" << endl;
            moves.push_back(betterThanRandom);
            return false;
        }
        // grief the other guy ..!
        struct move griefMove = getWinningMove(s,grid,opponentMoves,collinearLines);
        if(griefMove.n != -1){
            cout << "This Player griefed the other Player's win" << endl;
            moves.push_back(griefMove);
            grid[griefMove.pt.x][griefMove.pt.y][griefMove.pt.z].first = griefMove.n;
            grid[griefMove.pt.x][griefMove.pt.y][griefMove.pt.z].second = griefMove.n;
            s.erase(griefMove.n);
            return false; // remember you didnt win ..!
        }
        // if nothing worked and we have no option then random it is..!
        cout << "Random round" <<endl;
        struct move randMove = getRandomMove(s,grid,who);
        moves.push_back(randMove);
        return false;
    }

struct move Player :: getWinningMove(set<int>& s,vector<vector<vector<pair<int,int>>>> grid,vector<struct move> moves,vector<vector<point>> collinearLines){
    if(moves.size() <= 1)
        return {-1,-1,-1,-1};
    for(int i = 0;i < moves.size();i++){
        for(int j = i + 1;j < moves.size();j++){
            int newValue = MAGIC_NUMBER - (moves[i].n + moves[j].n);
            // if the new value is not available to take then cant win from this pair..
            if(s.find(newValue) == s.end())
                continue;
            point newPoint = getCollinearPoint(moves[i].pt,moves[j].pt,collinearLines);
            //check if it is already visited..
            if(newPoint.x != -1 && grid[newPoint.x][newPoint.y][newPoint.z].first == -1)
                return {newPoint,newValue};
        }
    }
    return {-1,-1,-1,-1};
}

struct point Player :: getRandPoint(vector<vector<vector<pair<int,int>>>> grid){
    // find a point that is not visited yet..!
    int x = rand()%3,y = rand()%3,z = rand()%3;
    while(grid[x][y][z].first != -1){
        x = rand()%3;
        y = rand()%3;
        z = rand()%3;
    }
    return {x,y,z};
}

// Game definitions ..

Game :: Game(int pi1,int pi2,int mx){
    p1 = pi1;
    p2 = pi2;
    mxWins = mx;
    player1 = Player();
    player2 = Player();
    n1 = n2 = round = 0;
    for(int i = 1;i <= N;i++)
        availableNumbers.insert(i);

    grid.resize(3);
    for(int i = 0;i < 3;i++)
        grid[i].resize(3);
    for(int i = 0;i < 3;i++)
        for(int j = 0;j < 3;j++)
            grid[i][j].resize(3);
    fill(grid.begin(),grid.end(),vector<vector<pair<int,int>>>(3,vector<pair<int,int>>(3,{-1,0})));

    collinearPoints = generateCollinearPoints();
}

bool Game :: validate(int x,int y,int z,int n){
    if(grid[x][y][z].first != -1)
        return false;
    if(availableNumbers.find(n) == availableNumbers.end())
        return false;
    return true;
}

void Game :: updateWins(){
    n1 = n2 = 0;
    winningMovesP1.clear(); winningMovesP2.clear();
    for(int i = 0;i < player1.moves.size();i++){
        for(int j = i + 1;j < player1.moves.size();j++){
            // get the winning move .. check if it already exists in the current set..!
            struct point colPoint = getCollinearPoint(player1.moves[i].pt,player1.moves[j].pt,collinearPoints);
            if(colPoint.x == -1)
                continue;
            // for this to be winning we need MAGIC - (i.n + j.n) as the value..
            struct move winMove = {colPoint,MAGIC_NUMBER - (player1.moves[i].n + player1.moves[j].n)};
            // check if it exists here..
            bool exists = false;
            for(int k = j + 1;k < player1.moves.size();k++)
                if(player1.moves[k] == winMove)
                    exists = true;
            if(exists){
                n1++;
                winningMovesP1.push_back({player1.moves[i],player1.moves[j],winMove});
            }
    }
    } 
    // same but for player 2..
    for(int i = 0;i < player2.moves.size();i++){
        for(int j = i + 1;j < player2.moves.size();j++){
            // get the winning move .. check if it already exists in the current set..!
            struct point colPoint = getCollinearPoint(player2.moves[i].pt,player2.moves[j].pt,collinearPoints);
            if(colPoint.x == -1)
                continue;
            // for this to be winning we need MAGIC - (i.n + j.n) as the value..
            struct move winMove = {colPoint,MAGIC_NUMBER - (player2.moves[i].n + player2.moves[j].n)};
            // check if it exists here..
            bool exists = false;
            for(int k = j + 1;k < player2.moves.size();k++)
                if(player2.moves[k] == winMove){
                    exists = true;
                    winningMovesP2.push_back({player2.moves[i],player2.moves[j],winMove});
                }
            if(exists)
                n2++;
        }
    } 
}

void Game :: gameLoop(){
    while(true){
        // recalculate wins..
        updateWins();
        // print a line so each round is clear..
        printline(150);
        // print out Round information .. .. 
        cout << "Round " << round + 1 << endl;
        cout << "Score : " << n1 << " - " << n2 << endl;
        cout << "Player 1 : ";
        print(player1.moves);
        cout << "win lines : ";
        print(winningMovesP1);
        cout << "Player 2 : ";
        print(player2.moves);
        cout << "win lines : ";
        print(winningMovesP2);
        cout << "Available numbers : ";
        print(availableNumbers);
        // done .. :)
        if(n1 == mxWins){cout << "Player 1 won" << endl;return;}
        if(n2 == mxWins){cout << "Player 2 won" << endl;return;}
        if(availableNumbers.size() == 0){
            if(n1 > n2) cout << "Player 1 won.." << endl;
            if(n2 > n1) cout << "Player 2 won.." << endl;
            if(n1 == n2) cout << "Draw" << endl;
            return;
        }
        int x,y,z,n;
        if(round&1){
            if(p1 == 1){
                // human input ..
                cin >> x >> y >> z >> n;
                while(!validate(x,y,z,n)){
                    cout << "Invalid input try again(x,y,z,n) : " ;
                    cin >> x >> y >> z >> n;
                }
            }
            else if(p1 == 2){
               struct move randMove = player1.getRandomMove(availableNumbers,grid,1); 
               player1.moves.push_back(randMove);
            }
            else{
                (player1.predictMove(availableNumbers,player2.moves,grid,0,collinearPoints));
            }
        }
        else{
            if(p2 == 1){}
            else if(p2 == 2){
               struct move randMove = player2.getRandomMove(availableNumbers,grid,1); 
               player2.moves.push_back(randMove);
            }
            else{
                (player2.predictMove(availableNumbers,player1.moves,grid,1,collinearPoints));
            }
        }
        round++;
        // info about avail numbers..
        //getchar();
    }
}

