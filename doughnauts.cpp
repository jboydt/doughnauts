// #include "fight.h"
// #include "fight_history.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <cstdint>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using std::array;
using std::vector;
using std::cout;
using std::cin;
using std::endl;    
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::istringstream;
using std::stringstream;
using std::ostringstream;
using std::setw;
using std::setfill;
using std::ostream;



struct doughnautDetails {
  int index;
  string name;
  int health;
  int speed;
  string moveA;
  string moveB;
  string moveC;
  
  // constructor for creating a doughnaut
  doughnautDetails() {
    index = 0;
    string name = "doughnautName";
    health = 100;
    speed = 50;
    moveA = "First Move";
    moveB = "Second Move";
    moveC = "Third Move";
  } 
  
  friend ostream& operator<< (ostream& outs, const doughnautDetails& dd) {
    outs << std::left << setw(3) << setfill(' ') << dd.index
         << std::left << setw(15) << setfill(' ') << dd.name
         << std::left << setw(7) << setfill(' ') << dd.health
         << std::left << setw(7) << setfill(' ') << dd.speed
         << std::left << setw(12) << setfill(' ') << dd.moveA
         << std::left << setw(12) << setfill(' ') << dd.moveB
         << std::left << setw(12) << setfill(' ') << dd.moveC;
    return outs;
  }
};

struct moveDetails {
  unsigned int index;
  string name;
  string description;
  
  // constructor for creating a move
    moveDetails() {
      index = 1;
      name = "moveName";
      description = "This move does something";
    }
    
  // Overlod operator <<
  // Allows convinient stream output of moves
  friend ostream& operator<< (ostream& outs, const moveDetails& md) {
    outs << std::left << setw(3) << setfill(' ') << md.index
         << std::left << setw(15) << setfill(' ')  << md.name
         << std::left << setw(100) << setfill(' ') << md.description;
    return outs;
  }
  // Overload operator ==
  // Allows for comparisons of two moves (some future usage)
  bool operator== (const moveDetails& md) const {
    return (
      index == md.index &&
      name == md.name &&
      description == md.description
    );
  };
  
  
};



class DoughNaut {
  public:
  
  // Main Menu
  void MainMenu();
  
  // create a stored move to be used when buidling a doughnaut
  void createMove();
  
  // load moves into vector
  bool loadMoves(string filename);
  
  // Output Moves
  string outputMoves();
  
  // Create a complete DoughNaut with stats and a moveset
  void createDoughNaut();
  
  // load doughnaut characters into vector
  bool loadDoughnauts(string filename);
  
  // output doughnauts
  string outputDoughnauts();
  
  // Arena Menu
  void arenaMenu();
  
  // Exit
  void Exit();
  
  private:
    unsigned int choice;
    vector<moveDetails> moves;
    vector<moveDetails> appendMoveHolder;
    vector<doughnautDetails> doughnauts;
    vector<doughnautDetails> appendDoughnautHolder;
    vector<doughnautDetails> playerOne;
    vector<doughnautDetails> playerTwo;
    moveDetails tokenizeMoves(string input);
    doughnautDetails tokenizeDoughnauts(string input);
};


int main() {
  // Fight f1;

  // FightHistory fh;

  // for (unsigned int i=0; i<1000; i++) {
  //   fh.addFight(f1);
  // }
  srand(time(0));
  DoughNaut D;
  D.loadMoves("moves.txt");
  D.loadDoughnauts("doughnauts.txt");
  cout << "\nWelcome to Doughnauts\n"
       << "Design or fight doughnauts in a turn-based fighting game\n" << endl;
       
  D.MainMenu();
  
  return 0;
}

void DoughNaut::MainMenu() {
  cout << std::left << setw(3) << setfill(' ') << "#" << "Main Menu\n"
       << std::left << setw(3) << setfill(' ') << "1" << "Enter the Arena\n"
       << std::left << setw(3) << setfill(' ') << "2" << "Browse Doughnauts\n"
       << std::left << setw(3) << setfill(' ') << "3" << "Browse Moves\n"
       << std::left << setw(3) << setfill(' ') << "4" << "Create a new Move\n"
       << std::left << setw(3) << setfill(' ') << "5" << "Design a new DoughNaut\n"
       << std::left << setw(3) << setfill(' ') << "6" << "Exit\n"
       << "Enter option: ";
  cin >> choice;
  cout << endl;
  switch (choice) {
    case 1: {
      arenaMenu();
      break;
    }
    case 2: {
      cout << outputDoughnauts() << endl;
      MainMenu();
      break;
    }
    case 3: {
      cout << outputMoves() << endl;
      MainMenu();
      break;
    }
    case 4: {
      createMove();
      break;
    }
    case 5: {
      createDoughNaut();
      break;
    }
    case 6: {
      Exit();
      break;
    }
    default: {
      cout << "Menu Option does not exist!\n"
           << "Please try again.\n";
      MainMenu();
      return;
    }
  }
}

void DoughNaut::arenaMenu() {
  cout << "Welcome to the Arena!\n"
       << std::left << setw(3) << setfill(' ') << "#" << "Options\n"
       << std::left << setw(3) << setfill(' ') << "1" << "Battle AI\n"
       << std::left << setw(3) << setfill(' ') << "2" << "Challenge a user\n"
       << "Enter Option: ";
  cin >> choice;
  if (choice == 1) {
    cout << outputDoughnauts();
    cout << "Enter combatant #: ";
      cin >> choice;
    playerOne.push_back(doughnauts.at(choice));
    cout << "Prepare yourself, " << playerOne.at(0).name << endl;
    // randomize AI
    choice = (rand() % doughnauts.size());
    playerTwo.push_back(doughnauts.at(choice));
    cout << playerTwo.at(0).name << " seeks your head!";
  }
  
  
  
}
void DoughNaut::createMove() {
  moveDetails md;
  
  // Get user index 
  // Will auto index in future
  md.index = moves.size() + 1;
  cout << "Enter name: ";
    cin >> md.name;
  cout << "Enter description: ";
    cin >> md.description;
  appendMoveHolder.push_back(md);
  // Before moving on, make sure everything is filled in
  cout << "\nYour move: \n"
       << appendMoveHolder.at(0).name  << ","
       << appendMoveHolder.at(0).description << endl;
       
  cout << std::left << setw(3) << setfill(' ') << "#" << "Options\n"
       << std::left << setw(3) << setfill(' ') << "1" << "Confirm\n"
       << std::left << setw(3) << setfill(' ') << "2" << "Edit your move\n"
       << std::left << setw(3) << setfill(' ') << "3" << "Main Menu\n"
       << std::left << setw(3) << setfill(' ') << "4" << "Exit\n"
       << "Enter option: ";
  cin >> choice;
    switch (choice) {
      case 1: {
        cout << "\nOpening moves.txt for appending..." << endl;
        // Declare our Stream and open all at once
        ofstream fout("moves.txt", std::ios::app);
          // Output/Append to move.txt
        if (fout.good()) {
          fout << md.index << "," 
               << md.name  << ","
               << md.description << "\n";
        // Close out Streams
          fout.close();
                cout << "Successfully added " << appendMoveHolder.at(0).name << endl << endl;
        }
        else {
          cout << "Failed to append\n";
        }
        MainMenu();
        break;
      }
      case 2: {
        appendMoveHolder.clear();
        createMove();
        break;
      }
      case 3: {
        appendMoveHolder.clear();
        MainMenu();
        break;
      }
      case 4: {
        appendMoveHolder.clear();
        Exit();
      }
        break;
      default: {
        break;
      }
   }
}

string DoughNaut::outputMoves() {
  // header
  cout << std::left << setw(3) << setfill(' ') << "#"
         << std::left << setw(15) << setfill(' ')  << "Name"
         << std::left << setw(100) << setfill(' ') << "Description"
         << endl;
  // moves
  ostringstream outs;
  for (auto i = moves.begin(); i != moves.end(); i++) {
    outs << *i << endl;
  }
  
  
  return outs.str();
}

void DoughNaut::createDoughNaut() {
  doughnautDetails dd;
  // Usage
  cout << "Welcome to the DoughNaut Creation Studio\n"
       << "Here are the recommended guidelines for balancing your DoughNaut\n"
       << "Health: 100-250\n"
       << "Speed: 0-100\n" << endl;
  // get stats
  dd.index = doughnauts.size() + 1;
  cout << "Name your DoughNaut: ";
    cin >> dd.name;
  cout << "Enter Health: ";
    cin >> dd.health;
  cout << "Enter Speed: ";
    cin >> dd.speed;
  // view moves
  cout << "\nNow Select three unique moves\n";
  cout << outputMoves() << endl;
  // select moves
  cout  << "A move is selected by inputting the corresponding #\n";
  cout  << "Enter MoveA: ";
    cin >> choice;
    dd.moveA = moves.at(choice).name;
  cout  << "Enter MoveB: ";
    cin >> choice;
    dd.moveB = moves.at(choice).name;
  cout  << "Enter MoveC: ";
    cin >> choice;
    dd.moveC = moves.at(choice).name;

  appendDoughnautHolder.push_back(dd);
  cout << "\nYour combatant looks like: \n"
       << appendDoughnautHolder.at(0) << endl << endl;
    
  cout << std::left << setw(3) << setfill(' ') << "#" << "Options\n"
       << std::left << setw(3) << setfill(' ') << "1" << "Confirm\n"
       << std::left << setw(3) << setfill(' ') << "2" << "Edit\n"
       << std::left << setw(3) << setfill(' ') << "3" << "Main Menu\n"
       << std::left << setw(3) << setfill(' ') << "4" << "Exit\n"
       << "Enter option: ";
  cin >> choice;
    switch (choice) {
      case 1: {
        cout << "\nOpening doughnauts.txt for appending..." << endl;
        // Declare our Stream and open all at once
        ofstream fout("doughnauts.txt", std::ios::app);
          // Output/Append to move.txt
        if (fout.good()) {
          fout << dd.name << "," 
               << dd.health << ","
               << dd.speed << ","
               << dd.moveA << ","
               << dd.moveB << ","
               << dd.moveC 
               << "\n";
        // Close out Streams
          fout.close();
            cout << "Successfully created " << appendDoughnautHolder.at(0).name << endl << endl;
            doughnauts.push_back(appendDoughnautHolder.at(0));
            appendDoughnautHolder.clear();
        }
        else {
          cout << "Failed to append\n";
        }
        MainMenu();
        break;
      }
      case 2: {
        appendDoughnautHolder.clear();
        createDoughNaut();
        break;
      }
      case 3: {
        appendDoughnautHolder.clear();
        MainMenu();
        break;
      }
      case 4: {
        appendDoughnautHolder.clear();
        Exit();
      }
        break;
      default: {
        break;
      }
   }
}

string DoughNaut::outputDoughnauts() {
  // header
  cout << std::left << setw(3) << setfill(' ') << "#"
       << std::left << setw(15) << setfill(' ') << "Name"
       << std::left << setw(7) << setfill(' ') << "Health"
       << std::left << setw(7) << setfill(' ') << "Speed"
       << std::left << setw(12) << setfill(' ') << "MoveA"
       << std::left << setw(12) << setfill(' ') << "MoveB"
       << std::left << setw(12) << setfill(' ') << "MoveC"
       << endl;
  // moves
  ostringstream outs;
  for (auto i = doughnauts.begin(); i != doughnauts.end(); i++) {
    outs << *i << endl;
  }
  return outs.str(); 
}


void DoughNaut::Exit() {
  
  cout << "\nProgram succesfully terminated\n";
}

// Loads in moves data into a vector
bool DoughNaut::loadMoves(string filename) {
  // open file
  ifstream inputFile;
  inputFile.open(filename);
  // if open
  if(inputFile.is_open()) {
    string fileLine;
    unsigned int i = 0;
    while (getline(inputFile, fileLine)) {
      // ignore comment lines with # in file
      if ( fileLine[0] != '#') {
        moves.push_back(tokenizeMoves(fileLine));
        i++;
      }
    } 
    inputFile.close();
    cout << filename << " was loaded\n";
    return true;
  }
}

bool DoughNaut::loadDoughnauts(string filename) {
  // open file
  ifstream inputFile;
  inputFile.open(filename);
  // if open
  if(inputFile.is_open()) {
    string fileLine;
    unsigned int i = 0;
    // load fileline data into vector
    while (getline(inputFile, fileLine)) {
      // ignore comment lines with # in file
      if ( fileLine[0] != '#') {
        doughnauts.push_back(tokenizeDoughnauts(fileLine));
        i++;
      }
    } 
    inputFile.close();
    cout << filename << " was loaded\n\n";
    return true;
  }  
}

// Tokenize doughnauts stats
doughnautDetails DoughNaut::tokenizeDoughnauts(string input) {
  doughnautDetails dd;
  string convertIndex, convertHealth, convertSpeed;
  istringstream ss(input);
  // convert to #
  getline(ss, convertIndex, ',');
    stringstream ssCRN(convertIndex); 
    ssCRN >> dd.index;
    // clear string + buffer so it can be used again
    ssCRN.str("");
    ssCRN.clear();   
  getline(ss, dd.name, ',');
  // convert segment into integer
  getline(ss, convertHealth, ',');
    ssCRN << " " << convertHealth;
      ssCRN >> dd.health;
      ssCRN.str("");
      ssCRN.clear();
  getline(ss, convertSpeed, ',');
  // allows ssCRN to be used again
  ssCRN << " " << convertSpeed;
    ssCRN >> dd.speed;
    ssCRN.str("");
    ssCRN.clear();
  getline(ss, dd.moveA, ',');
  getline(ss, dd.moveB, ',');
  getline(ss, dd.moveC, ',');
  return dd;
}

// Tokenize moves file
moveDetails DoughNaut::tokenizeMoves(string input) {
  moveDetails md;
  string convertIndex;
  istringstream ss(input);
  // convert index to string
  getline(ss, convertIndex, ',');
    stringstream ssCRN(convertIndex);
    ssCRN >> md.index;
    // clear
    ssCRN.str("");
    ssCRN.clear();
  getline(ss, md.name, ',');
  getline(ss, md.description);
  return md;
}