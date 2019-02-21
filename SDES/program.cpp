#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <stdio.h>  
#include <stdlib.h>
#include <algorithm>

using namespace std;

/*FOR PRUEBAS
for(int i = 0; i < 8; i++){
    cout<<bin[i]<<" - ";
}cout<<endl;
END FOR PRUEBAS*/

int XOR(int a, int b){
    if(a == b){
        return 0;
    }else{
        return 1;
    }
}

int coor(int a, int b){
    if(a == b){
        if(a == 0){
            return 0;
        }else{
            return 3;
        }
    }else{
        if(a == 0){
            return 1;
        }else{
            return 2;
        }
    }
}

void toBit(int p[4], int x0, int y0, int x1, int y1, int s0[4][4], int s1[4][4]){
    
    int val1 = s0[x0][y0];
    int val2 = s1[x1][y1];
    
    if(val1 == 0){
        p[0] = 0;
        p[1] = 0;
    }else if(val1 == 1){
        p[0] = 0;
        p[1] = 1;
    }else if(val1 == 2){
        p[0] = 1;
        p[1] = 0;
    }else{
        p[0] = 1;
        p[1] = 1;
    }
    
    if(val2 == 0){
        p[2] = 0;
        p[3] = 0;
    }else if(val2 == 1){
        p[2] = 0;
        p[3] = 1;
    }else if(val2 == 2){
        p[2] = 1;
        p[3] = 0;
    }else{
        p[2] = 1;
        p[3] = 1;
    }
    
}

int main() {
    
    char option;
    cin>>option;
    
    string k;
    cin>>k;
    
    string plaintext;
    cin>>plaintext;
    
    int bin[8];

    for(int i = 0; i < 8; i++){ 
        if(plaintext[i] == '0')
            bin[i] = 0;
        else{
            bin[i] = 1;
        }
    }
    
    int key[10];

    for(int i = 0; i < 10; i++){ 
        if(k[i] == '0')
            key[i] = 0;
        else{
            key[i] = 1;
        }
    }
    
    //STEP 1
    //PERMUTACION BITS
    swap(bin[0], bin[3]);
    swap(bin[0], bin[4]);
    swap(bin[0], bin[6]);
    swap(bin[0], bin[7]);
    swap(bin[0], bin[5]);
    swap(bin[0], bin[1]);

    //PERMUTACION KEY
    swap(key[0], key[6]);
    swap(key[0], key[3]);
    swap(key[0], key[4]);
    swap(key[0], key[1]);
    swap(key[0], key[2]);
    swap(key[9], key[5]);
    swap(key[7], key[8]);
    
    //SHIFT 1st HALF
    swap(key[0], key[1]);
    swap(key[1], key[2]);
    swap(key[2], key[3]);
    swap(key[3], key[4]);
    
    //SHIFT 2nd HALF
    swap(key[5], key[6]);
    swap(key[6], key[7]);
    swap(key[7], key[8]);
    swap(key[8], key[9]);
    
    //SUBKEY 1
    int sk1[8];
    sk1[0] = key[5];
    sk1[1] = key[2];
    sk1[2] = key[6];
    sk1[3] = key[3];
    sk1[4] = key[7];
    sk1[5] = key[4];
    sk1[6] = key[9];
    sk1[7] = key[8];
    
    //SHIFT 2nd & 3rd HALF
    for(int i = 0; i < 2; i++){
        swap(key[0], key[1]);
        swap(key[1], key[2]);
        swap(key[2], key[3]);
        swap(key[3], key[4]);
        swap(key[5], key[6]);
        swap(key[6], key[7]);
        swap(key[7], key[8]);
        swap(key[8], key[9]);
    }
    
    //SUBKEY 2
    int sk2[8];
    sk2[0] = key[5];
    sk2[1] = key[2];
    sk2[2] = key[6];
    sk2[3] = key[3];
    sk2[4] = key[7];
    sk2[5] = key[4];
    sk2[6] = key[9];
    sk2[7] = key[8];
    
    int SBOX_S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    int SBOX_S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
    //END STEP 1
    
    //STEP 2
    //EXPANDED HALF RIGHT
    int exP1[8];
    exP1[0] = bin[7];
    exP1[1] = bin[4];
    exP1[2] = bin[5];
    exP1[3] = bin[6];
    exP1[4] = bin[5];
    exP1[5] = bin[6];
    exP1[6] = bin[7];
    exP1[7] = bin[4];
    
    //CHECAMOS SI SE ENCRIPTA O DESENCRIPTA
    if(option == 'E'){
        //XOR SK1 ^ EXP1
        exP1[0] = XOR(exP1[0], sk1[0]);
        exP1[1] = XOR(exP1[1], sk1[1]);
        exP1[2] = XOR(exP1[2], sk1[2]);
        exP1[3] = XOR(exP1[3], sk1[3]);
        exP1[4] = XOR(exP1[4], sk1[4]);
        exP1[5] = XOR(exP1[5], sk1[5]);
        exP1[6] = XOR(exP1[6], sk1[6]);
        exP1[7] = XOR(exP1[7], sk1[7]);
    }else{
        //XOR SK2 ^ EXP1
        exP1[0] = XOR(exP1[0], sk2[0]);
        exP1[1] = XOR(exP1[1], sk2[1]);
        exP1[2] = XOR(exP1[2], sk2[2]);
        exP1[3] = XOR(exP1[3], sk2[3]);
        exP1[4] = XOR(exP1[4], sk2[4]);
        exP1[5] = XOR(exP1[5], sk2[5]);
        exP1[6] = XOR(exP1[6], sk2[6]);
        exP1[7] = XOR(exP1[7], sk2[7]);
    }
    
    //COORDENADAS MATRIZ S0 Y S1
    int S0X = coor(exP1[0], exP1[3]);
    int S0Y = coor(exP1[1], exP1[2]);
    int S1X = coor(exP1[4], exP1[7]);
    int S1Y = coor(exP1[5], exP1[6]);
    
    //PER ES IGUAL A COORDENADAS
    int per[4];
    toBit(per, S0X, S0Y, S1X, S1Y, SBOX_S0, SBOX_S1);
    
    //PERMUTACION EN PER
    swap(per[0], per[1]);
    swap(per[1], per[3]);
    
    //XOR LEFT Y PERMUTACION
    bin[0] = XOR(bin[0], per[0]);
    bin[1] = XOR(bin[1], per[1]);
    bin[2] = XOR(bin[2], per[2]);
    bin[3] = XOR(bin[3], per[3]);
    
    //END STEP 2
    
    //STEP 3
    //CAMBIO LEFT POR RIGHT
    swap(bin[0], bin[4]);
    swap(bin[1], bin[5]);
    swap(bin[2], bin[6]);
    swap(bin[3], bin[7]);
    
    //END STEP 3
    
    //STEP 4
    //HACEMOS LO MISMO CON K2
    //EXPANDED HALF RIGHT
    exP1[0] = bin[7];
    exP1[1] = bin[4];
    exP1[2] = bin[5];
    exP1[3] = bin[6];
    exP1[4] = bin[5];
    exP1[5] = bin[6];
    exP1[6] = bin[7];
    exP1[7] = bin[4];
    
    //CHECAMOS SI SE ENCRIPTA O DESENCRIPTA
    if(option == 'E'){
        //XOR SK1 ^ EXP1
        exP1[0] = XOR(exP1[0], sk2[0]);
        exP1[1] = XOR(exP1[1], sk2[1]);
        exP1[2] = XOR(exP1[2], sk2[2]);
        exP1[3] = XOR(exP1[3], sk2[3]);
        exP1[4] = XOR(exP1[4], sk2[4]);
        exP1[5] = XOR(exP1[5], sk2[5]);
        exP1[6] = XOR(exP1[6], sk2[6]);
        exP1[7] = XOR(exP1[7], sk2[7]);
    }else{
        //XOR SK2 ^ EXP1
        exP1[0] = XOR(exP1[0], sk1[0]);
        exP1[1] = XOR(exP1[1], sk1[1]);
        exP1[2] = XOR(exP1[2], sk1[2]);
        exP1[3] = XOR(exP1[3], sk1[3]);
        exP1[4] = XOR(exP1[4], sk1[4]);
        exP1[5] = XOR(exP1[5], sk1[5]);
        exP1[6] = XOR(exP1[6], sk1[6]);
        exP1[7] = XOR(exP1[7], sk1[7]);
    }
    
    //COORDENADAS MATRIZ S0 Y S1
    S0X = coor(exP1[0], exP1[3]);
    S0Y = coor(exP1[1], exP1[2]);
    S1X = coor(exP1[4], exP1[7]);
    S1Y = coor(exP1[5], exP1[6]);
    
    //PER ES IGUAL A COORDENADAS
    per[4];
    toBit(per, S0X, S0Y, S1X, S1Y, SBOX_S0, SBOX_S1);
    
    //PERMUTACION EN PER
    swap(per[0], per[1]);
    swap(per[1], per[3]);
    
    //XOR LEFT Y PERMUTACION
    bin[0] = XOR(bin[0], per[0]);
    bin[1] = XOR(bin[1], per[1]);
    bin[2] = XOR(bin[2], per[2]);
    bin[3] = XOR(bin[3], per[3]);
    
    //END STEP 4
    
    //STEP 5
    //PERMUTACION INVERSA
    
    swap(bin[0], bin[1]);
    swap(bin[0], bin[5]);
    swap(bin[0], bin[7]);
    swap(bin[0], bin[6]);
    swap(bin[0], bin[4]);
    swap(bin[0], bin[3]);
    
    //END STEP 5
    
    for(int i = 0; i < 8; i++){
        cout<<bin[i];
    }cout<<endl;
}