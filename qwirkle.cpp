
#include "LinkedList.h"
#include "Bag.h"
#include "Tile.h"
#include "Player.h"
#include "Game.h"
#include "Board.h"

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#define EXIT_SUCCESS    0

void startProgram();

void checkPlayerCount();

void checkFileName();

void printMenu();

void listCredits();

bool helpCommand = false;
bool betterInvalidInput = false;
bool morePlayers = false;
int playerCount = 2;

int main(void) {
   std::cout << "-------------------------" << std::endl;
   std::cout << "   Welcome to Qwirkle" << std::endl;
   std::cout << "-------------------------" << std::endl;
   startProgram();

   return EXIT_SUCCESS;
}

void printMenu(){
      std::cout << "          Menu" << std::endl;
      std::cout << "-------------------------" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Credits (student info)" << std::endl;
      if(helpCommand){
         std::cout << "4. Minor: Toggle Help Command. " << std::endl; std::cout << "       \033[0;32m-Currently [On]-Off\033[0m" << std::endl;
      }else{
         std::cout << "4. Minor: Toggle Help Command. " << std::endl; std::cout << "       \033[0;31m-Currently On-[Off]\033[0m" << std::endl;
      }
      if(betterInvalidInput){
         std::cout << "5. Minor: Toggle Better Invalid Input. " << std::endl; std::cout << "       \033[0;32m-Currently [On]-Off\033[0m" << std::endl;
      }else{
         std::cout << "5. Minor: Toggle Better Invalid Input. " << std::endl; std::cout << "       \033[0;31m-Currently On-[Off]\033[0m" << std::endl;
      }
      if(morePlayers){
         std::cout << "6. Major: 3-4 Players Mode. " << std::endl; std::cout << "       \033[0;32m-Currently [On]-Off\033[0m" << std::endl;
      }else{
         std::cout << "6. Major: 3-4 Players Mode. " << std::endl; std::cout << "       \033[0;31m-Currently On-[Off]\033[0m" << std::endl; 
      }
      std::cout << "7. Quit" << std::endl;
      std::cout << "Current amount of players: " << playerCount << std::endl;
      std::cout << "-------------------------" << std::endl;
      std::cout << ">";
}

void startProgram(){ 
   //track what choice the player has made
   int choice = 0;
   //if choice is invalid, repeat menu function
   bool optionSelected = false;
   bool toggle = false;

   //Get input from player to decide what function to start
   while(!optionSelected){
      printMenu();
        if(std::cin.eof() == 1){
            std::cout << "Goodbye." << std::endl;
            exit(0);
        }else{
            std::cin >> choice;
        }
      
      //check to see if an integer was entered / std::cin = true
      if(std::cin){
         if(choice == 1){
            Game* game = new Game(helpCommand, betterInvalidInput, morePlayers, playerCount);
            std::cout << "Starting new game" << std::endl;
            optionSelected = true;
            game->newGame(helpCommand, betterInvalidInput, morePlayers, playerCount);
            delete game;
         }else if(choice == 2){
            std::cout << "Loading Game" << std::endl;
            //validate filename
            std::cin.clear();
            std::cin.ignore(256,'\n');
            checkFileName();
            optionSelected = true;
         }else if(choice == 3){
            std::cout << "Displaying Credits" << std::endl;
            listCredits();
         }else if(choice == 4){
            toggle = true;
            optionSelected = false;
            if(helpCommand == false){
               helpCommand = true;
            }else{
               helpCommand = false;
            }
         }else if(choice == 5){
            toggle = true;
            optionSelected = false;
            if(betterInvalidInput == false){
               betterInvalidInput = true;
            }else{
               betterInvalidInput = false;
            }
         }else if(choice == 6){
            toggle = true;
            optionSelected = false;
            //ask how many players
            if(morePlayers == false){
               checkPlayerCount();
               morePlayers = true;
            }else{
               morePlayers = false;
               playerCount = 2;
            }
         }else if(choice == 7){
            std::cout << "Goodbye" << std::endl;
            optionSelected = true;
         }else{
            optionSelected = false;
            std::cout <<"Invalid Option: Int out of range" << std::endl;
         }
      }else{
         if(toggle == false){
            choice = 0;
            std::cout << "Invalid option" << std::endl;
            std::cout << " " << std::endl;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            optionSelected = false;
         }else{
            toggle = false;
            choice = 0;
            std::cin.clear();
            std::cin.ignore(256,'\n');
            optionSelected = false;
         }
      }      
   }
}

void checkPlayerCount(){
   bool validCount = false;
   int choice;
   do{
      std::cout << "How many players will be playing? 3 or 4?" << std::endl;
      std::cout << ">";

      if(std::cin.eof() == 1){
         std::cout << "Goodbye." << std::endl;
         exit(0);
      }else{
         std::cin >> choice;
      }

      if(std::cin){
         if(choice == 3){
            playerCount = 3;
            validCount = true;
         }
         else if(choice == 4){
            playerCount = 4;
            validCount = true;
         }
         else{
            choice = 0;
         }
      }else{
         std::cout << "Invalid choice" << std::endl;
         choice = 0;
         std::cin.clear();
         std::cin.ignore(256,'\n');
         validCount = false;
      }
   }while(!validCount);
}

void checkFileName(){
   bool validFile = false;
   std::string choice;

   do{
   std::cout << "Enter filename to be loaded" << std::endl;
   std::cout << ">";

   if(std::cin.eof() == 1){
      std::cout << "Goodbye." << std::endl;
      exit(0);
   }else{
      std::getline(std::cin, choice);
   }
   if(choice.back() == '\r'){choice.pop_back();}
   choice = choice+".save";
   std::ifstream input(choice);
   
   if(input.fail()){
      validFile = false;
      choice = " ";
      std::cout << "Invalid filename" << std::endl;
   }else{
      validFile = true;
   }
   }while (!validFile);
   
   Game* game = new Game();
   game->loadGame(choice);
   delete game;
}

void listCredits(){
   std::cout << "-------------------------------------" << std::endl;
   std::cout << "Name: Pemal Padukkage" << std::endl;
   std::cout << "Student ID: s3744264" << std::endl;
   std::cout << "Email: s3744264@student.rmit.edu.au" << std::endl;
   std::cout << "" <<std::endl;
   std::cout << "Name: Qingzhao Liu" << std::endl;
   std::cout << "Student ID: s3631678" << std::endl;
   std::cout << "Email: s3631678@student.rmit.edu.au" << std::endl;
   std::cout << "" <<std::endl;
   std::cout << "Name: Sophie Sha" << std::endl;
   std::cout << "Student ID: 3742024" << std::endl;
   std::cout << "Email: s3742024@student.rmit.edu.au" << std::endl;
   std::cout << "" <<std::endl;
   std::cout << "Name: Travis Constable" << std::endl;
   std::cout << "Student ID: 3506912" << std::endl;
   std::cout << "Email: s3506912@student.rmit.edu.au" << std::endl;
   std::cout << "" <<std::endl;
   std::cout << "-------------------------------------" << std::endl;
   startProgram();
}