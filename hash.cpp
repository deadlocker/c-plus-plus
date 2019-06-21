#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#define size 15000
using namespace std;


int hashfunction(string);
void insert(string hashTable[], string);
void search(string hashTable[], string);

int main(){
    
    int number;
    string hashTable[size];
    string search_word;
    
    for(int i = 0; i < size; i++){
        hashTable[i] = "empty";
    }
    
    ifstream file;
    string word;
    file.open("dictionary");
    file >> word;  
    while(!file.eof()){
     insert(hashTable, word);
     file >> word;  
    }
    file.close();
    
    /*
    cout << "\n\n\n";
    for(int i = 0; i < size; i++){
        cout << hashTable[i] << "\t" << i << "\n";
    }
    */
    cout << "###########################################################\n";
    cout << "\t\tHash table is being constructed\n";
    cout <<"\t\thash Table is ready. Lets search now.\n";
    cout << "###########################################################\n";
    cout << "Enter how many words you want to search : \t";
    cin >> number;
    
    for(int i = 0; i < number; i++){
        cout << "Enter the word to search :\t";
        cin >> search_word;
        search(hashTable, search_word);
    }
    
    return 0;
}


int hashfunction(string key){
    int numeric = 0;
    for(int i = 0; i < key.length(); i++)
        numeric += key[i];
    return (numeric * key.length()) % size;
}

void insert(string hashTable[], string word){
    int hashKey;
    hashKey = hashfunction(word);
    again:
    if((hashTable[hashKey] == "empty")){
        hashTable[hashKey] = word;
    }else{
        hashKey = (hashKey + 1) % size;
        if(hashTable[hashKey] == "empty"){
            hashTable[hashKey] = word;
        }else{
            goto again;
        }
    }
}

/*
void insert(string hashTable[], string word){
    int hashKey;
    hashKey = hashfunction(word);
    if((hashTable[hashKey] == "empty")){
        hashTable[hashKey] = word;
    }else{
        hashKey = (hashKey + 1) % size;
        while(hashTable[hashKey] != "empty"){
            hashKey = (hashKey + 1) % size;
        }
        hashTable[hashKey] = word;
    }
}
*/


void search(string hashTable[], string word){
    int hashKey;
    int comparison = 0;
    hashKey = hashfunction(word);
    again:
    if(hashTable[hashKey] == word){
        cout << "The key word is found !!\n";
        cout << "Number of comaprisions required :\t" << comparison <<"\n";
    }else if((hashTable[hashKey] != word) && hashTable[hashKey] != "empty"){ 
        hashKey = hashKey + 1;
        comparison += 1;
        if(hashKey > size){
            hashKey = (hashKey + 1) % size;
        }
        if(hashTable[hashKey] == word){
            comparison += 1;
            cout << "The key word is found!!\n";
            cout << "Number of comaprisions required :\t" << comparison <<"\n";      
        }else{
            goto again;
        }
    }else{
        comparison += 1;
        cout << "The key word is not found!!\n";
        cout << "Number of comaprisions required :\t" << comparison <<"\n";   
    }
}