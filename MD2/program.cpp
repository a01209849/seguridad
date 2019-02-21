#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

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
        cout<<(char)(rem - 10 + 'A');
    }else{
        cout<<rem;
    }
}

int main() { 
    
    string plaintext;
    int S[256];
    getline(cin, plaintext);
    unsigned char message[plaintext.length()];
    
    //Llenas el arreglo chars
    for(int i = 0; i < plaintext.length(); i++){
        message[i] = plaintext[i];
    }
    
    //Llenas el arreglo S
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }
    
    //Padding
    size_t nbytes = sizeof(message);
    nbytes = 16 - (nbytes % 16);
    unsigned char m[sizeof(message) + nbytes + 16];
    int aux = 0;
    
    for(int i = 0; i < sizeof(message) + nbytes + 16; i++){
        if(aux == sizeof(message)){
            aux = 0;
        }
        if(i < (sizeof(message) + nbytes)){
            m[i] = message[aux];
        }else{
            m[i] = 48;
        }
        aux++;
    }
    
    //Declaro variables que servirán para hacer XOR
    unsigned char L = 0, c;
    
    /*//Llenas el arreglo C
    for(int i = 0; i < 16; i++){
        C[i] = &m[i + sizeof(message) + nbytes];
    }*/
    
    //CHECKSUM      m = tamaño del mensaje y C = tamaño 16?????
    for(int i = 0; i < (sizeof(m) / 16); i++){
        for(int j = 0; j < 16; j++){
            c = m[16 * i + i]; //Es multiplicación?????
            m[j + sizeof(message) + nbytes] = m[j + sizeof(message) + nbytes] ^ S[c ^ L];
            L = m[j + sizeof(message) + nbytes];
        }
    }
    
    
    //Llenas el arreglo X
    unsigned char X[48];
    for(int i = 0; i < 48; i++){
        X[i] = 0;
    }
    
    int t;
    
    //HASH
    for(int i = 0; i < (sizeof(m) + 16) / 16; i++){
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
        hex(X[i],0);
    }
    
    return 0; 
}