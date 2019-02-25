#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <stdio.h>

using namespace std;

void hex(int n, int i){
    if(n == 0 && i != 0){
        return;
    }else if (n == 0 && i == 0){
        cout<<0;
    }else if(n < 16 && i == 0){
        cout<<0;
    }
    
    int rem = n % 16;
    n /= 16;
    hex(n,1); 
    
    if (rem > 9){
        cout<<(char)(rem - 10 + 'a');
    }else{
        cout<<rem;
    }
}

int XOR(int a, int b){
    
    int binaryA[8], binaryB[8], binaryC[8];
    int c = 0; 
    for(int i = 7; i > -1; i--){
        if(a >= 1){
            binaryA[i] = a % 2;
            a = a / 2;
        }else{
            binaryA[i] = 0;
        }
        if(b >= 1){
            binaryB[i] = b % 2;
            b = b / 2;
        }else{
            binaryB[i] = 0;
        }
    }
    
    //Llenas el arreglo S MEMSET
    for(int i = 0; i < 8; i++){
        cout<<binaryA[i]<<" - ";
    }cout<<endl;
    
    //Llenas el arreglo S MEMSET
    for(int i = 0; i < 8; i++){
        cout<<binaryB[i]<<" - ";
    }cout<<endl;
    
    for(int i = 0; i < 8; i++){
        if(binaryA[i] == binaryB[i]){
            binaryC[i] = 0;
        }else{
            binaryC[i] = 1;
        }
    }
    
    for(int i = 0; i < 8; i++){
        if(binaryC[i] == 1){
            c = c + pow(2, 7 - i);
        }
    }
    
    return c;
}

void showbits(unsigned short int x, unsigned short int n[8]) {
    int aux = 0;
    
    for(int i = (sizeof(unsigned short int) * 4) - 1; i >= 0; i--) {
       (x & (1u << i)) ? n[aux] = 1 : n[aux] = 0;
       aux++;
    }
}

int main() { 
    
    string plaintext;
    unsigned short int S[256];
    getline(cin, plaintext);
    int SIZE = plaintext.length() + (16 - (plaintext.length() % 16)) + 16; //SIZE ES EL PADDING + CHECKSUM (N')
    unsigned short int m[SIZE];//[8];
    
    //Llenas el arreglo S MEMSET
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }
    
    //Padding
    //unsigned short int n[8];
    int aux = 0;
    for(unsigned short int i = 0; i < SIZE; i++){
        if(aux == plaintext.length()){
            aux = 0;
        }
        if(i < plaintext.length()){
            //showbits(plaintext[i], n);
            m[i] = plaintext[i];
            
        }else if(i >= plaintext.length() && i < plaintext.length() + (16 - (plaintext.length() % 16))){
            //showbits(plaintext[aux], n);
            m[i] = plaintext[aux];
        }else {
            //showbits(0, n);
            m[i] = 0;
        }
        /*for(int j = 0; j < 8; j++){
            m[i][j] = n[j];
            cout<<m[i][j]<<" - ";
        }*/
        aux++;
        cout<<m[i]<<" - ";
        //cout<<endl;
    }
    
    cout<<endl;
    
    //Declaro variables que servirán para hacer XOR
    unsigned short int L = 0, c;
    
    //CHECKSUM
    for(int i = 0; i < ((SIZE - 16) / 16); i++){
        for(int j = 0; j < 16; j++){
            c = m[16 * i + j]; 
            m[j + SIZE - 16] = m[j + SIZE - 16] ^ S[c ^ L];
            L = m[j + SIZE - 16];
        }
    }
    
    for(int i = 0; i < SIZE; i++){
        //cout<<m[i]<<" - ";
    }
    //cout<<endl;
    
    //Llenas el arreglo X MEMSET
    unsigned short int X[48];
    for(int i = 0; i < 48; i++){
        X[i] = 0;
    }
    
    int t;
    
    //HASH
    for(int i = 0; i < SIZE / 16; i++){
        for(int j = 0; j < 16; j++){
            X[j + 16] = m[16 * i + j];
            X[j + 32] = X[j + 16] ^ X[j];
            
        }
        
        t = 0;
        for(int j = 0; j < 18; j++){
            for(int k = 0; k < 48; k++){
                t = X[k] ^ S[t];
                X[k] = t;
            }
            t = (t + j) % 256;
        }
    }
    
    //Imprime el resultado en Hexadecimal
    for(int i = 0; i < 16; i++){
        cout<<hex<<X[i].num;
    }
    cout<<endl;
    
    return 0; 
}