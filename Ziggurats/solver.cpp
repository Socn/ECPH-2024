/*
Ziggurats Solver

use SG to solve the game
took site 8 as example
*/

#include<iostream>
#include<deque>
#include<map>
#include<string>

using namespace std;

const int layerCnt[10] = {6};
const int zigCnt = 1;
const char site[] = "8.out";

bool MAP[10][10][10] = {
    {
        {0},
        {0,0},
        {0,0,0},
        {0,0,0,0},
        {0,0,0,0,0},
        {0,1,0,0,0,0},
    }};

int layerWidth(int layer){
    return layer+1;
}

struct point{
    int x;
    int y;
};

struct choice{
    bool type; //false 1x1 true 1x2
    int zig;
    point a,b;
};

map<string, int> sg;

string toString(int step){
    string ret=to_string(step);
    for(int zig=0;zig<zigCnt;zig++){
        for(int i=0;i<layerCnt[zig];i++){
            for(int j=0;j<layerWidth(i);j++){
                ret+=MAP[zig][i][j]?"0":".";
            }
        }
    }
    
    return ret;
}

bool check(choice c){
    if(c.type == false){ // 1x1
        if(c.a.x == layerCnt[c.zig]-1){
            if(c.a.y == 0 || c.a.y == layerWidth(c.a.x)-1)return true;
            return !(MAP[c.zig][c.a.x-1][c.a.y-1] && MAP[c.zig][c.a.x-1][c.a.y] && MAP[c.zig][c.a.x][c.a.y-1] && MAP[c.zig][c.a.x][c.a.y+1]);
        }
        if(c.a.x != 0){
            if(c.a.y == 0 || c.a.y == layerWidth(c.a.x)-1)return MAP[c.zig][c.a.x+1][c.a.y] && MAP[c.zig][c.a.x+1][c.a.y+1];
            return MAP[c.zig][c.a.x+1][c.a.y] && MAP[c.zig][c.a.x+1][c.a.y+1] && !(MAP[c.zig][c.a.x-1][c.a.y-1] && MAP[c.zig][c.a.x-1][c.a.y] && MAP[c.zig][c.a.x][c.a.y-1] && MAP[c.zig][c.a.x][c.a.y+1]);
        }
        if(c.a.x == 0)return MAP[c.zig][c.a.x+1][c.a.y] && MAP[c.zig][c.a.x+1][c.a.y+1];
    }

    if(c.type == true){ // 1x2
        if(c.a.x == layerCnt[c.zig]-1)return true;
        if(c.a.x != 0){
            return MAP[c.zig][c.a.x+1][c.a.y] && MAP[c.zig][c.b.x+1][c.b.y+1];
        }
        if(c.a.x == 0)return false;
    }

    return false;
}

deque<choice> makeChoice(){
    deque<choice> ret = {};
    for(int zig = 0;zig<zigCnt;zig++){
        for(int i=0;i<layerCnt[zig];i++){
            for(int j=0;j<layerWidth(i);j++){
                point a={i,j};
                point b={i,j+1};
                if(!MAP[zig][i][j]){ // 1x1
                    if(check({false, zig, a})){
                        choice c={false, zig, a};
                        ret.push_back(c);
                    }
                }
                if(j+1<layerWidth(i)){
                    if(!MAP[zig][i][j]&&!MAP[zig][i][j+1]){ // 1x2
                        if(check({true, zig, a, b})){
                            choice c={true, zig, a, b};
                            ret.push_back(c);
                        }
                    }
                }
            }
        }
    }
    
    return ret;
}

deque<choice> madeChoice;
void print(){
    for(int zig=0;zig<zigCnt;zig++){
        for(int i=0;i<layerCnt[zig];i++){
            for(int j=0;j<layerWidth(i);j++){
                printf(MAP[zig][i][j]?"0":".");
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("==== Choices ====\n");
    for(auto &i: madeChoice){
        if(i.type==false){
            printf("1x1 %d %d %d\n", i.zig, i.a.x, i.a.y);
        }
        else{
            printf("1x2 %d %d %d %d %d\n", i.zig, i.a.x, i.a.y, i.b.x, i.b.y);
        }
    }
    printf("==== End Choices ====\n");
}

bool flag = true;
int getSG(int step){
    string mapString = toString(step);
    if(!flag && step > 1)return 0;
    if(sg.count(mapString)>0){
        return sg[mapString];
    }
    deque<choice> q=makeChoice();
    if(q.size()==0){
        return sg[mapString]=0;
    }
    bool book[100]={0};
    for(auto &i: q){
        if(i.type==false){
            MAP[i.zig][i.a.x][i.a.y] = 1;
        }
        else{
            MAP[i.zig][i.a.x][i.a.y] = 1;
            MAP[i.zig][i.b.x][i.b.y] = 1;
        }
        madeChoice.push_back(i);
        if(step == 0)flag = true;
        book[getSG(step+1)] = true;
        madeChoice.pop_back();
        if(i.type==false){
            MAP[i.zig][i.a.x][i.a.y] = 0;
        }
        else{
            MAP[i.zig][i.a.x][i.a.y] = 0;
            MAP[i.zig][i.b.x][i.b.y] = 0;
        }
    } 
    for(int i=0;i<100;i++){
        if(!book[i]){
            if(i==0 && step == 1){
                print();
            }
            if(i == 0 && step == 2){
                flag = false;
            }
            return sg[mapString]=i;
        }
    }
    return 0;
}


int main(){
    freopen(site,"w",stdout);
    getSG(0);
}