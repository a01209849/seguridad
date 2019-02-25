#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <stdio.h>

using namespace std;

void hex(int n, int i){
    if (n == 0){
        return;
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
    
    int SBOX[256] = {0x29, 0x2e, 0x43, 0xc9, 0xa2, 0xd8, 0x7c, 0x01, 0x3d, 0x36, 0x54, 0xa1,
        0xec, 0xf0, 0x06, 0x13, 0x62, 0xa7, 0x05, 0xf3, 0xc0, 0xc7, 0x73, 0x8c,
        0x98, 0x93, 0x2b, 0xd9, 0xbc, 0x4c, 0x82, 0xca, 0x1e, 0x9b, 0x57, 0x3c,
        0xfd, 0xd4, 0xe0, 0x16, 0x67, 0x42, 0x6f, 0x18, 0x8a, 0x17, 0xe5, 0x12,
        0xbe, 0x4e, 0xc4, 0xd6, 0xda, 0x9e, 0xde, 0x49, 0xa0, 0xfb, 0xf5, 0x8e,
        0xbb, 0x2f, 0xee, 0x7a, 0xa9, 0x68, 0x79, 0x91, 0x15, 0xb2, 0x07, 0x3f,
        0x94, 0xc2, 0x10, 0x89, 0x0b, 0x22, 0x5f, 0x21, 0x80, 0x7f, 0x5d, 0x9a,
        0x5a, 0x90, 0x32, 0x27, 0x35, 0x3e, 0xcc, 0xe7, 0xbf, 0xf7, 0x97, 0x03,
        0xff, 0x19, 0x30, 0xb3, 0x48, 0xa5, 0xb5, 0xd1, 0xd7, 0x5e, 0x92, 0x2a,
        0xac, 0x56, 0xaa, 0xc6, 0x4f, 0xb8, 0x38, 0xd2, 0x96, 0xa4, 0x7d, 0xb6,
        0x76, 0xfc, 0x6b, 0xe2, 0x9c, 0x74, 0x04, 0xf1, 0x45, 0x9d, 0x70, 0x59,
        0x64, 0x71, 0x87, 0x20, 0x86, 0x5b, 0xcf, 0x65, 0xe6, 0x2d, 0xa8, 0x02,
        0x1b, 0x60, 0x25, 0xad, 0xae, 0xb0, 0xb9, 0xf6, 0x1c, 0x46, 0x61, 0x69,
        0x34, 0x40, 0x7e, 0x0f, 0x55, 0x47, 0xa3, 0x23, 0xdd, 0x51, 0xaf, 0x3a,
        0xc3, 0x5c, 0xf9, 0xce, 0xba, 0xc5, 0xea, 0x26, 0x2c, 0x53, 0x0d, 0x6e,
        0x85, 0x28, 0x84, 0x09, 0xd3, 0xdf, 0xcd, 0xf4, 0x41, 0x81, 0x4d, 0x52,
        0x6a, 0xdc, 0x37, 0xc8, 0x6c, 0xc1, 0xab, 0xfa, 0x24, 0xe1, 0x7b, 0x08,
        0x0c, 0xbd, 0xb1, 0x4a, 0x78, 0x88, 0x95, 0x8b, 0xe3, 0x63, 0xe8, 0x6d,
        0xe9, 0xcb, 0xd5, 0xfe, 0x3b, 0x00, 0x1d, 0x39, 0xf2, 0xef, 0xb7, 0x0e,
        0x66, 0x58, 0xd0, 0xe4, 0xa6, 0x77, 0x72, 0xf8, 0xeb, 0x75, 0x4b, 0x0a,
        0x31, 0x44, 0x50, 0xb4, 0x8f, 0xed, 0x1f, 0x1a, 0xdb, 0x99, 0x8d, 0x33,
        0x9f, 0x11, 0x83, 0x14};
    
    string plaintext;
    getline(cin, plaintext);
    if(plaintext[0] == 34 ){
        plaintext = "";
    }
    int Msize;
    if(plaintext.length() == 16){
        Msize = plaintext.length() + 16;
    }else{
        Msize = plaintext.length();
    }
    
    int nbytes = 16 - (Msize % 16);
    Byte S[256];
    if(nbytes == 0){
        nbytes = 16;
    }
    int SIZE = Msize + nbytes + 16; //SIZE ES EL PADDING + CHECKSUM (N')
    
    Byte m[SIZE];
    //Llenas el arreglo S 
    for(int i = 0; i < 256; i++){
        S[i] = dec_bin(SBOX[i]);
    }
    
    //PADDING SI ES MULTIPLO DE 16 SE AGREGAN OTROS 16
    for(int i = 0; i < SIZE; i++){
        if(i < Msize){
            m[i] = dec_bin(plaintext[i]);
        }else if(i >= Msize && i < (Msize + nbytes)){
            m[i] = dec_bin(16 - (Msize % 16));
        }else{
            m[i] = dec_bin(0);
        }
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
        hex(X[i].num,0);
    }
    
    return 0;
    
}