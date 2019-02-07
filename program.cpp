#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

bool validKey(string key){
  for(int i = 0; i < key.length(); i++){
    for(int j = 0; j < key.length(); j++){
      if(i != j){
        if(key[i] == key[j]){
          return false; //Regresa falso si la llave tiene letras repetidas
        }
      }
    }
  }
  return true;
}

int findLetter(char array[25], char c){
  for(int i = 0; i < 25; i++){
      if(array[i] == c){
          return i;
      }
      if(array[i] == 32){
        return 32;
      }
  }
}

int findNumber(int x, int y){
  int coord = (x * 5) + y;
  return coord;
}

int main() { 
  bool existe = false;
  char array[25];
  //cout<<"Introduce la llave: ";
  cin>>array;
  char c = 65;
  string key(array);
  int size = key.length(), cont = 0;
  
  if(validKey(key) == false){
    cout<<"La llave no es válida"<<endl;
    return 1;
  }
  
  for(int i = 0; i < 25; i++){
    for(int j = 0; j < size; j++){
        
        if(c == 74){ //revisa que no sea igual a J
          c++;   
        }
        
        if(array[j] == c){ //Verifica que la letra no esté dentro de la llave
          existe = true;
        }
    }
    
    if(existe == false){
      array[size + cont] = c;
      cont++;
    }else {
      existe = false;
    }
    
    c++;
  }
  
  string mensaje;
  getline(cin>>ws,mensaje);
  int cifrado[mensaje.length() * 2];
  int coord, cont2 = 0;
  
  for(int i = 0; i < mensaje.length(); i++){
    
      if(mensaje[i] > 64 && mensaje[i] < 91){
        coord = findLetter(array, mensaje[i]);
        cifrado[i] = coord / 5;
        cifrado[i + mensaje.length()] = (coord % 5);
      }else{
        cifrado[i] = 32;
        cifrado[i + mensaje.length()] = 32;
        cont2++;
      }
  }
  
  char encriptado[mensaje.length() - cont2];
  int aux = 0, numArreglo;
  for(int i = 0; i < (mensaje.length()*2); i = i + 2){
      if(cifrado[i] != 32){
        if(cifrado[i + 1] != 32){
          numArreglo = findNumber(cifrado[i], cifrado[i + 1]);
          encriptado[aux] = array[numArreglo];
          cout<<encriptado[aux];
          aux++;
        }else{
          numArreglo = findNumber(cifrado[i], cifrado[i + 2]);
          encriptado[aux] = array[numArreglo];
          cout<<encriptado[aux];
          aux++;
        }
      }else{
        i--;
      }
  }
  
  return 0;
 
 
 
}