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
using std::array;
using std::vector;
using std::cout;
using std::cin;
using std::endl;    
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::stringstream;
using std::ostringstream;
using std::setw;
using std::setfill;

struct doughnautDetails {
  string name;
  int health;
  int speed;
  unsigned int moveA;
  unsigned int moveB;
  unsigned int moveC;
  
  // constructor for creating a doughnaut
  doughnautDetails() {
    string name = "doughnautName";
    int health = 100;
    int speed = 50;
    unsigned int moveA = 1;
    unsigned int moveB = 2;
    unsigned int moveC = 3;
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
};



class DoughNaut {
  public:
  
  // Main Menu
  void MainMenu();
  
  //Index a move to be utilized when building a doughnaut
  void createMove();
  
  //Create a complete DoughNaut with stats and a moveset
  doughnautDetails createDoughNaut();
  
  // Exit
  void Exit();
  
  private:
    unsigned int choice;
    vector<moveDetails> appendMoveHolder;
    vector<doughnautDetails> appendDoughnautHolder;
};


int main() {
  // Fight f1;

  // FightHistory fh;

  // for (unsigned int i=0; i<1000; i++) {
  //   fh.addFight(f1);
  // }
  DoughNaut D;
  cout << "\nWelcome to Doughnauts\n"
       << "Design or fight doughnauts in a turn-based fighting game\n" << endl;
  D.MainMenu();
  
  return 0;
}

void DoughNaut::MainMenu() {
  cout << std::left << setw(3) << setfill(' ') << "#" << "Main Menu\n"
       << std::left << setw(3) << setfill(' ') << "1" << "Enter the Arena\n"
       << std::left << setw(3) << setfill(' ') << "2" << "Create a new Move\n"
       << std::left << setw(3) << setfill(' ') << "3" << "Design a new DoughNaut\n"
       << std::left << setw(3) << setfill(' ') << "4" << "Exit\n"
       << "Enter option: ";
  cin >> choice;
  cout << endl;
  switch (choice) {
    case 1: {
     // New Menu with selecting a doughnaut
      break;
    }
    case 2: {
      createMove();
      break;
    }
    case 3: {
      createDoughNaut();
      break;
    }
    case 4: {
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

void DoughNaut::createMove() {
  moveDetails md;
  int index; 
  string name, description;
  
  // Get user index
  cout << "Enter index: ";
    cin >> md.index;
  cout << "Enter name: ";
    cin >> md.name;
  cout << "Enter description: ";
    cin >> md.description;
  appendMoveHolder.push_back(md);
  // Before moving on, make sure everything is filled in
  cout << "\nYour move: \n"
       << appendMoveHolder.at(0).index << "," 
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
          // Output/Append to data.txt
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
      default:
        break;
   }

}

doughnautDetails DoughNaut::createDoughNaut() {
  
  cout << "\nIn Progress";
}
void DoughNaut::Exit() {
  
  
  cout << "\nProgram succesfully terminated\n";
}