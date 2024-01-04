# include <bits/stdc++.h>
# include <vector>
# include <cstdlib>
# define pl1 'X'
# define pl2 'O'
using namespace std;

void printboard(vector<vector<char>> &b);
bool isPrime(long long int n);
bool hcheck(vector<vector<char>> &b);
bool vcheck(vector<vector<char>> &b);
bool dcheck(vector<vector<char>> &b);
bool entry(vector<vector<int>> &e, int r, int c);
bool movesleft(vector<vector<char>> &b);
int score(vector<vector<char>> &b);
int minimax(vector<vector<char>> &b, int depth, bool p);
vector<int> bestmove(vector<vector<char>> &b);

int main(){
    cout<<"---WELCOME TO TIC TAC TOE---\n";
    string p1,p2,line = "----------------------------\n";
    int mode;
    cout<<"Mode 1 - Two Players\nMode 2 - Easy, with Computer\nMode 3 - Difficult, with Computer\n";
    cout<<"Which mode do you want to play? ";cin>>mode;
    if(mode==1){
        cout<<"Enter the Name of Player 1: ";cin>>p1;
        cout<<"Enter the Name of Player 2: ";cin>>p2;
    }
    else if(mode==2||mode==3){
        cout<<"Enter your Name: ";cin>>p1;
        p2 = "Computer";
    }
    else{
        cout<<"Mode "<<mode<<" is not available!!\n";
        return 0;
    }

    cout<<p1<<"(P1)"<<" - X | "<<p2<<"(P2)"<<" - O\n";
    cout<<line;

    vector<vector<char>> board(3,vector<char>(3,'#'));

    vector<vector<int>> ind;
    ind = {
        {1,1},{1,2},{1,3},{2,1},{2,2},{2,3},{3,1},{3,2},{3,3}
    };

    int count;
    long long int num;

    if(mode==2||mode==3){
        cout<<"Enter a Prime Number to get first turn: ";cin>>num;
        isPrime(num) ? count = 1 : count = 2;
        cout<<line;
    }
    else{
        count = 1;
    }

    cout<<"Game Board\n";
    cout<<"Range = (Row : 1-3) | (Column : 1-3)\n";
    printboard(board);
    cout<<line;

    bool check = true;
    
    while(check){
        int row,col;

        vector<vector<int>>::iterator it = ind.begin();

        cout<<"Turn: ";count%2 ? cout<<p1<<"(P1)"<<endl : cout<<p2<<"(P2)"<<endl;

        if(count%2){
            bool entry_check = true;
            while(entry_check){
                cout<<"Enter Row Number: ";cin>>row;
                cout<<"Enter Column Number: ";cin>>col;
                entry_check = !(entry(ind,row,col));
                if(entry_check){cout<<"Invalid Entry!!\n";}
            }
        }
        else{
            if(mode==1){
                bool entry_check = true;
                while(entry_check){
                    cout<<"Enter Row Number: ";cin>>row;
                    cout<<"Enter Column Number: ";cin>>col;
                    entry_check = !(entry(ind,row,col));
                    if(entry_check){cout<<"Invalid Entry!!\n";}
                }
            }
            else if(mode==2){
                int arr[1000];
                for(int i=0;i<1000;i++){
                    arr[i] = rand()%(ind.size());
                }
                row = ind[arr[0]][0];
                col = ind[arr[0]][1];
            }
            else{
                vector<int> m;
                m = bestmove(board);
                row = m[0]+1;
                col = m[1]+1;
            }
        }

        for(int i=0;i<ind.size();i++){
            if(ind[i][0]==row && ind[i][1]==col){ind.erase(it+i);}
        }  

        count%2 ? board[row-1][col-1] = pl1 : board[row-1][col-1] = pl2;
        printboard(board);
        cout<<line;

        check = !(hcheck(board)||vcheck(board)||dcheck(board));
        if(!check){
            string ps1 = p1 + " Won!!\n";
            string ps2 = p2 + " Won!!\n";
            count%2 ? cout<<ps1 : cout<<ps2;
            return 0;
        }
        if(!movesleft(board)){
            cout<<"Game Tie!!\n";
        return 0;
        }
        count++;
    }
}

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
    for(i=2;i<sqrt(n/2)+1;i++){
        if(n%i==0){return false;}
    }
    return true;
}