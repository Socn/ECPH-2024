#include<iostream>
#include<vector>
using namespace std;
const string L = "VQCDUBOWODDKVFXQLUJSSKBVI";
const string R = "CJBKNCNDVWKRUYQRSNKZLJCUP";

int dist(char a, char b){
    int dis = abs(a-b);
    if(dis > 13){
        return 26 - dis;
    }
    return dis;
}

float checkL(string& str){
    int len = str.length();
    int cnt = 0;
    for(int i = 0; i < len; i++){
        int dis = dist(str[i], L[i]);
        if(dis == 3)dis *= 3;
        else if(dis == 6)dis *= 6;
        else if(dis == 10)dis *= 10;
        cnt+=dis;
    }
    return (float)cnt/len;
}

void shift(char* c, int dis){
    int a0z25 = *c - 'A';
    int a0z25dis = (a0z25 + dis + 26) % 26;
    *c = a0z25dis + 'A';
}

vector<int> shifts = {-13,-12,-11,-10,-8,-7,-6,-5,-3,-2,2,3,5,6,7,8,10,11,12};

void constructStr(){
    string str = "";
    for(int len = 0; len<25-1; len++){
        str += R[len];
        for(int i=0; i<len+1; i++){
            for(auto& dis: shifts){
                string temp = str;
                shift(&temp[i], dis);
                if(checkL(temp) == 2.0){
                    cout<<temp<<endl;
                }
            }
        }
    }
}

int main(){
    constructStr();
    return 0;
}