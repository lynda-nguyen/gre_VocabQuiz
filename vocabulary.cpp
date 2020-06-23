#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <limits>

using namespace std;

int askCards();
string readWord(string curLine, size_t seperator);
bool isWord(string input, string term);

int main()
{ 
    // reads line def from file but stores word
    int setInput; // line number
    string word;  // defined word used for comparison
    string line; // reads line from myfile
    double correctCount = 0; 
    list<string> review; // list to store incorrect vocab inputs
    int inc = 0; // increment for getline to pass lines until desired set
    string input; // user's input for vocab definition
    string elucidate; // stores the defined word

    setInput = askCards();

    // read in flashcard file 
    ifstream myfile ("flashcards.txt");
    if (myfile.is_open()){
        while (inc != setInput && getline(myfile, line) && setInput != 1){
            ++inc;
        } 

        for (unsigned int i = setInput; i < setInput + 10; i++){
            getline(myfile, line);
            size_t sep = line.find(':');
            elucidate = line.substr(sep + 1, line.length());
            
            word = readWord(line, sep);

            cout << elucidate << '\n' << "Enter defined word: ";
            cin >> input;

            bool match = isWord(input, word);

            if (match == false){
                review.push_back(word);
            }
            else {
                correctCount++;
            }
        }
        for (auto const& i:review){
            cout << "REVIEW: " << endl;
            cout << i << "\n";
        }
        cout << "Score: " << double((correctCount/10)*100); 
        cout << "% for set =" << setInput << endl;
        myfile.close();
    }
    else cout << "Unable to open file." << endl;
    return 0;
}

int askCards(){
    int set;    // line number
    cout << "Which set of flashcards: ";
    cin >> set;
    cin.ignore();

    return set;
}

// function to return the first word of the definition line
string readWord(string curLine, size_t seperator){
    string wordDef = curLine.substr(0, seperator);
    return wordDef;
}

// function to compare if input is the correct word
bool isWord(string input, string term){
    if (input == term){
        return true;
    }
    return false;
}
