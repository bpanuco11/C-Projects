
#include <iostream>
#include "Board.h"
#include "Ship.h"

void gamePrologue();
void gameRulesCommands();


int main()
{
    /*Game Title*/
    cout << "\t\t\t\t    |~~{O}~~~~~~~~{ BATTLESHIP 2032 }~~~~~~~{X}~~|" << "\n\n";
    gamePrologue();
    gameRulesCommands();

    /*Board*/
    string board[10][10];

    /*Ships inside Board*/
    Ship ships[5];
    ships[0] = Ship(3, 'S', "Submarine");
    ships[1] = Ship(2, 'F', "Frigate");
    ships[2] = Ship(3, 'D', "Destroyer");
    ships[3] = Ship(4, 'B', "Battleship");
    ships[4] = Ship(5, 'A', "Aircraft Carrier");

    /*Size of the fleet*/
    int size = sizeof(ships) / sizeof(ships[0]);

    /*Generates Board with Fleet*/
    Board newBoard(board, ships, size);

    if(newBoard.getMissedShots() != 12 && !newBoard.getVictoryResult())
        cout << "\nQuit Successful!\n\n";


    return 0;
  
}// end main function

void gameRulesCommands() {

    cout << "\nRules: \n\n";
    cout << "1. All 5 Enemy Ships MUST Be Taken Down.\n";
    cout << "2. 12 Misses in a Row is an Instant Game Over.\n\n\n";
    cout << "Commands: \n\n";
    cout << "(Q) To Quit Game Enter: \'Q\' or \'q\'.\n";
    cout << "(S) To Make Ships Visible Enter: \'S\' or \'s\'.\n";
    cout << "(Z) To Hide Ships Enter: \'Z\' or \'z\'.\n\n\n";

}

void gamePrologue() {

    cout << "Prologue:\n\n";

    cout << "\t\t\t\t\t\t   AGAINST ALL ODDS \n\t\t\t\t\t\t   ~~~~~~~~~~~~~~~~\n\n";
    cout << "\t\tThe year is 2032, a time of war on the enriched waters"
         <<" of the Mediterranean Sea. \n\t\tYou, the commander, are in"
         << " charge of a destroyer near the enemy lines. To your "
         << " luck, \n\t\tyou find yourself facing an enemy fleet consisting of"
         << " an aircraft carrier, a battleship,\n\t\ta destroyer, a"
         << " frigate, and a submarine.\n\n";

    cout << "\t\t\t\t\t\t       STRANDED" << "\n\t\t\t\t\t\t       ~~~~~~~~\n\n";
    cout << "\t\tAlthough the satellites are down, you rely on the ship's sonar"
        << " capable of detecting \n\t\tenemy movement near a ten - by - ten grid."
        << " Beware, hitting your targets is critical.\n\t\tOur fleet is limited to 15"
        << " missiles; missing all shots will expose the ship to the enemy.\n\n";

    cout << "\t\t\t\t\t\t      GAME OVER?" << "\n\t\t\t\t\t\t      ~~~~~~~~~~\n\n";
    cout << "\t\tConsider taking all fleets down, as it only takes one"
        << " to take us down. Will you have \n\t\tthe skills necessary"
        << " to make it out victorious, or will you be sunk into"
        << " the void? \n\t\tRemember, coordinate correctly.\n\n\n";
    

    char startKey;
    cout << "Enter any Key to Start the Ship Commander! ~~> ";
    cin >> startKey;
    cout << "\n";

}