#include <bits/stdc++.h>
using namespace std;

void display(vector<char>& state){
    cout<<state[0]<<"|"<<state[1]<<"|"<<state[2]<<"\n";
    cout<<state[3]<<"|"<<state[4]<<"|"<<state[5]<<"\n";
    cout<<state[6]<<"|"<<state[7]<<"|"<<state[8]<<"\n";
}

bool gameIsOver(vector<char>& state){
    //check Rows
    if(state[0] == state[1] && state[0] == state[2]) return true;
    if(state[3] == state[4] && state[3] == state[5]) return true;
    if(state[6] == state[7] && state[6] == state[8]) return true;
    
    //check Columns
    if(state[0] == state[3] && state[0] == state[6]) return true;
    if(state[1] == state[4] && state[1] == state[7]) return true;
    if(state[2] == state[5] && state[2] == state[8]) return true;
    
    //check Diagonals
    if(state[0] == state[4] && state[0] == state[8]) return true;
    if(state[2] == state[4] && state[2] == state[6]) return true;
    
    for(int i=0; i<9; ++i){
        if(state[i] != 'x' && state[i] != 'o') return false;
    }
    
    return true;
}

bool winnerIs(vector<char>& state, bool& tie){


    //check Rows
    tie = false;
    if(state[0] == state[1] && state[0] == state[2]) {
        if(state[0] =='x') return false;
        else return true;
    }
    if(state[3] == state[4] && state[3] == state[5]) {
        if(state[3] =='x') return false;
        else return true;
    }
    if(state[6] == state[7] && state[6] == state[8]) {
        if(state[6] =='x') return false;
        else return true;
    }

    //check Columns
    if(state[0] == state[3] && state[0] == state[6]) {
        if(state[0] =='x') return false;
        else return true;
    }
    if(state[1] == state[4] && state[1] == state[7]) {
        if(state[1] =='x') return false;
        else return true;
    }
    if(state[2] == state[5] && state[2] == state[8]) {
        if(state[2] =='x') return false;
        else return true;
    }

    //check Diagonals
    if(state[0] == state[4] && state[0] == state[8]) {
        if(state[0] =='x') return false;
        else return true;
    }
    if(state[2] == state[4] && state[2] == state[6]) {
        if(state[2] =='x') return false;
        else return true;
    }
    
    tie = true;
    return true;
}

int eval(vector<char> state, bool turn, bool block){
    block = false;
    int row1=0;
    int row2 =0;
    int row3 =0;

    for(int i=0;i<3;i++){
        if(state[i] == 'x') row1++;
        if(state[i] == 'o') row1--;

        if(state[i+3] == 'x') row2++;
        if(state[i+3] == 'o') row2--;
    
        if(state[i+6] == 'x') row3++;
        if(state[i+6] == 'o') row3--;
    }

    int col1=0;
    int col2 =0;
    int col3 =0;

    for(int i =0;i<9; i+=3){
        if(state[i] == 'x') col1++;
        if(state[i] == 'o') col1--;

        if(state[i+1] == 'x') col2++;
        if(state[i+1] == 'o') col2--;
    
        if(state[i+2] == 'x') col3++;
        if(state[i+2] == 'o') col3--;
    }
    int diag1 =0;
    int diag2 =0;

    for(int i=0;i<9;i+=4){
        if(state[i] == 'x') diag1++;
        if(state[i] == 'o') diag1--;
    }

     for(int i=2;i<7;i+=2){
        if(state[i] == 'x') diag2++;
        if(state[i] == 'o') diag2--;
    }
    
    int a =  max({row1, row2, row3, col1, col2, col3, diag1, diag2});
    int b =  min({row1, row2, row3, col1, col2, col3, diag1, diag2});

    if(turn){
        //if( a ==2) return 20;
        if(a == 2) return 20000;

        if(b == -2) block = true;
        if(b==-3) return -20000;
    }

    else {
        //if( a == -2) return -20;
        if(b == -2) return -20000;
        
        if(a == 2) block = true;
        if(a==3) return 20000;
    }

    int ans =0;
    for(int i=0;i<9;++i){
        if(state[i] == 'x'){
            if(i == 4) ans+=15;
            else if (i == 0 || i==2 || i== 6 || i==8) ans+=3;
            else ans++;
        }

        if(state[i] =='o'){
            if(i == 4) ans-=15;
            else if (i == 0 || i==2 || i== 6 || i==8) ans-=3;
            else ans--;
        }
    }
        
    return ans;
}

pair<int,int> minMax(vector<char> state,int depth, bool turn){
    if (gameIsOver(state)) {
        bool tie = false;
        bool computerWon = winnerIs(state, tie);
        if (tie) return {0,0};
        if (computerWon) return{ -20000 ,0};
        return {20000 ,0};
    }

    if(depth ==1){
        int mark =-1;
        if(turn){
            int mx = -30000;
            int blockMove = -1;
            int blockEval  =0;

            for(int i=0;i<9;++i){
                if(state[i]=='x' || state[i] == 'o') continue;
                state[i] = 'x';
                
                bool block =false;
                int temp = eval(state,turn,block);            
                
                if(block) {
                    blockMove = i;
                    blockEval =temp;
                }
                state[i] = '1' +i;
                
                if(temp>mx){
                    mx = temp;
                    mark = i;
                }
            }
            if(mx<19000 && blockMove!=-1)  return {blockEval, blockMove};
            return {mx,mark};
        }

        else{
            int mn = 30000;
            int blockMove =-1;
            int blockEval  =0;
            for(int i=0;i<9;++i){
                if(state[i]=='x' || state[i] == 'o') continue;
                state[i] = 'o';

                bool block = false;
                
                int temp = eval(state,turn,block);
                if(block) {
                    blockMove = i;
                    blockEval =temp;
                }

                state[i] = '1' +i;
                 if(temp <mn){
                    mn = temp;
                    mark = i;
                }
            }
            if(mn >-19000 && blockMove >=0) return{blockEval,blockMove};
            return {mn,mark};
        }
    }

    else {
        if(turn){
            int mx = -30000;
            int mark =-1;
            for(int i=0;i<9;++i){
                if(state[i]=='x' || state[i] == 'o') continue;
    
                state[i] ='x';
                auto temp = minMax(state, depth -1, !turn);
                state[i] = '1' +i;
                
                if(temp.first > mx){
                    mx = temp.first;
                    mark = i;
                }
            }
            return {mx, mark};
        }
        else{
            int mn = 30000;
            int mark =-1;
            int count =0;
            int state4=0;
           
            for(int i=0;i<9;++i){
                if(state[i]=='x' || state[i] == 'o') {count++; continue;}
                state[i] ='o';
                
                auto temp = minMax(state, depth -1, !turn);
                if(i==4) state4 =temp.first;
                
                state[i] = '1' +i;

                if(temp.first < mn){
                    mn = temp.first;
                    mark = i;
                }
            }

            if(state[4] =='5' && count==1) return {state4, 4};
            return {mn, mark};
        }
    }
}


int main() {
    
    int input,depth;
    cout<<"Choose the depth of the search, it must be a number >=1\n";
    cin >> depth;
    
    while(depth <1){
        cout << "Invalid number. Choose the depth of the search, it must be a number >=1\n";
        cin >> depth;
    }

    cout << "Press 1 to start playing and 0 for the computer to start\n";
    cin >> input;

    while(input != 0 && input != 1){
        cout << "Invalid number. Press 1 to start playing and 0 for the computer to start\n";
        cin >> input;
    }

    bool turn = input;

    vector<char> state(9);
    for(int i=0;i<9;i++){ state[i] = '1' + i;}

    while(!gameIsOver(state)){
        cout<<"\n";
        if(turn){ 
            cout<<"Choose a number from 1 to 9, according to the board below\n";
            display(state);
            int move;
            cin>> move;
            
            if(move > 9 || move < 1 || state[move -1] == 'x' || state[move -1] == 'o'){
                    while(move> 9 || move <1 || state[move -1] == 'x' || state[move -1] == 'o'){
                        if( move> 9 || move <1) cout<<"Choose a number between 1 and 9 inclusive that is available\n";
                        else cout<<"This spot is already taken\n";
                            
                        display(state);
                        cin>>move;
                }
            }
            
            state[move - 1] = 'x';
        }
        
        else{
            auto move = minMax(state, depth, turn);
            state[move.second] = 'o';
        }

        turn = !turn;
    }

    bool tie;
    bool computerWon = winnerIs(state, tie);
    
    if(tie){
        cout<<"The game is a tie\n";
        display(state);
    }
    else if(computerWon){
        cout<<"Better luck next time\n";
        display(state);

    }
    else{
        cout<<"Congratulations, you beat the machine\n";
        display(state);
    }

    return 0;
}