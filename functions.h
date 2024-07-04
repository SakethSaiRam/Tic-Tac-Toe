# include <bits/stdc++.h>
# include <vector>
# include <cstdlib>
# define pl1 'X'
# define pl2 'O'
using namespace std;
void printboard(vector<vector<char>> &b){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool hcheck(vector<vector<char>> &b){
    for(int i=0;i<3;i++){
        if(b[i][0]!='#'&&b[i][1]!='#'&&b[i][2]!='#'){
            if(b[i][0]==b[i][1]&&b[i][1]==b[i][2]){
                return true;
            }
        }
    }
    return false;
}
bool vcheck(vector<vector<char>> &b){
    for(int i=0;i<3;i++){
        if(b[0][i]!='#'&&b[1][i]!='#'&&b[2][i]!='#'){
            if(b[0][i]==b[1][i]&&b[1][i]==b[2][i]){
                return true;
            }
        }
    }
    return false;
}
bool dcheck(vector<vector<char>> &b){
    if((b[0][0]!='#'&&b[1][1]!='#'&&b[2][2]!='#')||(b[0][2]!='#'&&b[1][1]!='#'&&b[2][0]!='#')){
        bool d1 = ((b[0][0]==b[1][1])&&(b[1][1]==b[2][2]));
        bool d2 = ((b[0][2]==b[1][1])&&(b[1][1]==b[2][0]));
        return d1||d2;
    }
    return false;
}
bool entry(vector<vector<int>> &e, int r, int c){
    for(int i=0;i<e.size();i++){
        if(e[i][0]==r&&e[i][1]==c){
            return true;
        }
    }
    return false;
}
bool movesleft(vector<vector<char>> &b){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(b[i][j]=='#'){return true;}
        }
    }
    return false;
}
int score(vector<vector<char>> &b){
    for(int i=0;i<3;i++){
        if(b[i][0]==b[i][1]&&b[i][1]==b[i][2]){
            if(b[i][0]==pl1){return 10;}
            else if(b[i][0]==pl2){return -10;}
        }
    }
    for(int i=0;i<3;i++){
        if(b[0][i]==b[1][i]&&b[1][i]==b[2][i]){
            if(b[0][i]==pl1){return 10;}
            else if(b[0][i]==pl2){return -10;}
        }
    }
    bool d1 = ((b[0][0]==b[1][1])&&(b[1][1]==b[2][2]));
    bool d2 = ((b[0][2]==b[1][1])&&(b[1][1]==b[2][0]));
    if(d1||d2){
        if(b[1][1]==pl1){return 10;}
        else if(b[1][1]==pl2){return -10;}
    }
    return 0;
}
int minimax(vector<vector<char>> &b, int depth, bool p){
    int current_score = score(b);
    if(current_score!=0){return current_score;}
    if(!movesleft(b)){return 0;}
    if(p){
        int mbest = 1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(b[i][j]=='#'){
                    b[i][j] = pl2;
                    mbest = min(mbest, minimax(b,depth+1,!p));
                    b[i][j] = '#';
                }
            }
        }
        return mbest+depth;
    }
    else{
        int nbest = -1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(b[i][j]=='#'){
                    b[i][j] = pl1;
                    nbest = max(nbest, minimax(b,depth+1,!p));
                    b[i][j] = '#';
                }
            }
        }
        return nbest-depth;
    }
}
vector<int> bestmove(vector<vector<char>> &b){
    int bestval = 1000, moveval;
    vector <int> move = {-1,-1};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(b[i][j]=='#'){
                b[i][j] = pl2;
                moveval = minimax(b,0,false);
                b[i][j] = '#';
                if(moveval<bestval){
                    move[0] = i;
                    move[1] = j;
                    bestval = moveval;
                }
            }
        }
    }
    return move;
}
bool isPrime(long long int n){
    long long int i;
    for(i=2;i<sqrt(n)+1;i++){
        if(n%i==0){return false;}
    }
    return true;
}
