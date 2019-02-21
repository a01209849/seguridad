#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <stdio.h>

using namespace std;

typedef struct {
    unsigned short int num;
    int x1;
    int x2;
    int x3;
    int x4;
    int x5;
    int x6;
    int x7;
    int x8;
} Byte;

Byte XOR(Byte A, Byte B){
    Byte C;
    unsigned short int acum = 0;
    
    if(A.x1 == B.x1){
        C.x1 = 0;
    }else{
        C.x1 = 1;
        acum += 1;
    }
    
    if(A.x2 == B.x2){
        C.x2 = 0;
    }else{
        C.x2 = 1;
        acum += 2;
    }
    
    if(A.x3 == B.x3){
        C.x3 = 0;
    }else{
        C.x3 = 1;
        acum += 4;
    }
    
    if(A.x4 == B.x4){
        C.x4 = 0;
    }else{
        C.x4 = 1;
        acum += 8;
    }
    
    if(A.x5 == B.x5){
        C.x5 = 0;
    }else{
        C.x5 = 1;
        acum += 16;
    }
    
    if(A.x6 == B.x6){
        C.x6 = 0;
    }else{
        C.x6 = 1;
        acum += 32;
    }
    
    if(A.x7 == B.x7){
        C.x7 = 0;
    }else{
        C.x7 = 1;
        acum += 64;
    }
    
    if(A.x8 == B.x8){
        C.x8 = 0;
    }else{
        C.x8 = 1;
        acum += 128;
    }
    
    C.num = acum;
    
    return C;
    
}

Byte dec_bin(int a){
    
    Byte B; 
    char c[8];
    B.num = a;
    
    for(int i = 7; i >= 0; i--){
        if(a >= 1){
            c[i] = a % 2;
            a = a / 2;
        }else{
            c[i] = 0;
        }
    }
    
    B.x1 = c[7]; B.x2 = c[6]; B.x3 = c[5]; B.x4 = c[4]; 
    B.x5 = c[3]; B.x6 = c[2]; B.x7 = c[1]; B.x8 = c[0];
    
    return B;
}

int main(){
    
    string plaintext;
    getline(cin, plaintext);
    int Msize = plaintext.length();
    
    Byte S[256];
    int SIZE = Msize + (16 - (Msize % 16)) + 16; //SIZE ES EL PADDING + CHECKSUM (N')
    Byte m[SIZE];
    
    //Llenas el arreglo S 
    for(int i = 0; i < 256; i++){
        S[i] = dec_bin(i);
    }
    
    //PADDING
    int aux = 0;
    for(int i = 0; i < SIZE; i++){
        if(aux == Msize){
            aux = 0;
        }
        if(i < Msize){
            m[i] = dec_bin(plaintext[i]);
            
        }else if(i >= Msize && i < (Msize + (16 - (Msize % 16)))){
            m[i] = dec_bin(plaintext[aux]);
        }else {
            m[i] = dec_bin(0);
        }
        aux++;
    }

    //Declaro variables que servirán para hacer XOR
    Byte L = dec_bin(0), c, cL; 
    
    //CHECKSUM
    for(int i = 0; i < ((SIZE - 16) / 16); i++){
        for(int j = 0; j < 16; j++){
            c = m[16 * i + j];
            m[j + SIZE - 16] = XOR(m[j + SIZE - 16], S[XOR(c, L).num]);
            L = m[j + SIZE - 16];
        }
    }
    
    //Llenas el arreglo X
    Byte X[48];
    for(int i = 0; i < 48; i++){
        X[i] = dec_bin(0);
    }
    
    Byte t;
    
    //HASH
    for(int i = 0; i < SIZE / 16; i++){
        for(int j = 0; j < 16; j++){
            X[j + 16] = m[16 * i + j];
            X[j + 32] = XOR(X[j + 16], X[j]);
            
        }
        
        t = dec_bin(0);
        for(int j = 0; j < 18; j++){
            for(int k = 0; k < 48; k++){
                t = XOR(X[k], S[t.num]);
                X[k] = t;
            }
            t = dec_bin((t.num + j) % 256);
        }
    }
    
    for(int i = 0; i < 16; i++){
        cout<<hex<<X[i].num;
    }
    
    return 0;
    
}