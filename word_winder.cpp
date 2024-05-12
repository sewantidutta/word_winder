#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <time.h>
#include <winbase.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void set_color(int color) {
    SetConsoleTextAttribute(console, color);
}

bool isAlpha(string str){
    for(char c : str){
        if (!isalpha(c)) return false;
    }
    return true;
}

string get_user_guess() {
    string guess;
    cout << "Enter your guess (5 letters): ";
    cin >> guess;
  
    while ( !(isAlpha(guess)) || guess.length() != 5) {
        cout << "Invalid input. Enter a 5-letter word: ";
        cin >> guess;
    }

    transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

    return guess;
}

bool check_guess(const string& guess, const string& word, vector<bool>& guessed) {

    vector<string> result(guess.size());
    vector<int> letterCounts(26, 0);
  for (char c : word) {
    letterCounts[c - 'a']++;
  }
 for (int i = 0; i < guess.size(); ++i) {
    char ch = guess[i];
    // If the character is in the word and at the correct position
    if (guess[i] == word[i]) {
      result[i] = "green";
      letterCounts[ch - 'a']--; // Decrement count for correctly placed letter
    }
 }
 for (int i = 0; i < guess.size(); ++i) {
    char ch = guess[i];
    if ( letterCounts[ch - 'a'] > 0) {
      // Character is present but not in the correct position
      result[i] = "yellow";
      letterCounts[ch - 'a']--; // Decrement count for used letter (yellow)
    } else if( result[i]!="green") {
      // Character not present in the word
      result[i] = "no color";
    }
 }
int i=0;
 for(string x : result ){
    if(x=="green"){
        set_color(2); // Green color
            cout << guess[i] << " ";
            set_color(7);
    }else if(x=="yellow"){
        set_color(6); // Yellow color
                std::cout << guess[i] << " ";
                set_color(7);
    }else {
        cout<< guess[i] << " ";
    }
    ++i;
 }

   cout << "\n";
}

void print_game_state(int attempts, const string& guess, const string& word) {
    if(word==guess) {
        set_color(FOREGROUND_RED);
         cout<<"Congratulations! You've guessed the correct word.";
         set_color(7);
    }else{
    if (attempts > 0) {
        cout<<"\n";
        cout << "Attempts remaining: " << attempts << "\n";
    } else {
        set_color(FOREGROUND_RED);
        cout << "Oops!! You've run out of attempts. The word was: ";
          set_color(7);
          set_color(FOREGROUND_GREEN);
        cout<< word << "\n";
        set_color(7);
    }
    }
}

int main(){
    ifstream myFile;
    vector<string> words;
    string word;
    myFile.open("file.txt");
    if(myFile.is_open()){
        while (myFile >> word) {
            words.push_back(word);
        }
        myFile.close();
    }else{
        cout << "Failed to open file!" << endl;
    }
    srand(time(NULL));
    int random_index = rand() % words.size();
    string chosen_word = words[random_index];

    int attempts = 6;
    string guess;
    vector<bool> guessed(100, false);
    
    set_color(FOREGROUND_BLUE);
    cout<<"\n";
    cout<<"WELCOME TO THE WORD WINDER"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"1.You need to guess a word having 5 letters. \n The guessed word can be name of city, state, country, non-living object, animal or bird. "<<endl;
    cout<<"2.You'll only get 6 tries to guess the word."<<endl;
    cout<<"3. If any alphabet of the guessed word is present in the correct position, the alphabet will turn green. "<<endl;
    cout<<"3. If any alphabet of the guessed word is in the incorrect position, the alphabet will turn yellow."<<endl;
    cout<<"4. If any alphabet of the guessed word is not in there in the word to be guessed, the alphabet won't have any  color."<<endl;
    cout<<"ALL THE BEST!!"<<endl;
    set_color(7);


     while (attempts > 0 && guess != chosen_word) {
        guess = get_user_guess();
        --attempts;
        check_guess(guess, chosen_word, guessed);
        print_game_state(attempts, guess, chosen_word);
        cout<<"\n";
    
    }

    return 0;

    }