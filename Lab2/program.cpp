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
    
    string key;
    string plaintext;
    int aux;
    int S[256];
    int j = 0;
    
    getline(cin, key);
    getline(cin, plaintext);
    
    //Llenas el arreglo S
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }
    
    //Permutación de S
    for(int i = 0; i < 256; i++){
        j = (j + S[i] + key[i % key.length()]) % 256;
        aux = S[j];
        S[j] = S[i];
        S[i] = aux;
    }
    
    //Obtener Key Stream
    
    int i = 0, l = 0, k[plaintext.length()];
    aux = 0;
    j = 0;
    
    while(l < plaintext.length()){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        aux = S[j];
        S[j] = S[i];
        S[i] = aux;
        k[l] = S[(S[i] + S[j]) % 256];
        l++;
    }
    
    //Lo siguiente hace la operacion XOR
    unsigned char a, b; 
    int c;
    
    for(i = 0; i < sizeof(k)/sizeof(*k); i++){
        a = k[i];
        b = plaintext[i];
        c = a^b;
        hex(c,0);
    }
    
    return 0; 
}