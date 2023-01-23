#include <iostream>
#include <array>
#include <limits>
#include <random>
#include <string>

// Board size
const int BOARD_SIZE {10}; 

// types of ship
const int DESTROYER_SIZE {2};
const int SUBMARINE_SIZE {3};
const int BATTLESHIP_SIZE {4};
const int CARRIER_SIZE {5};

// Functions declaration
void welcome_menu();
void print_board(std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> grid);
void place_ship(std::array<std::array<char, BOARD_SIZE> , BOARD_SIZE> &grid, int size, char mark);
void strike(int turn,  std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> &enemy);
int random_turn(int x, int y);
char play_quit();

int main(){

    welcome_menu();
    char player_input = play_quit();

    // Ask the user to play or to quit the game
    if(player_input == 'q')
    {   
        std::cout << "Bye!" << std::endl;
        return 0;
    }
    else if(player_input == 'p')
    {   
        int turn = random_turn(1, 2); // Random turn generator
        bool start_game {false}; // Game status

        // Player 1 board variable 
        std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> player1_board;
        // // Player 2 board variable
        std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> player2_board;

        // Build the player1 board
        for(auto &row : player1_board)
        {
            for(auto &cell : row)
            {
                cell = '~';
            }
        }

        // Build the player 2 board
        for(auto &row : player2_board) 
        {
            for(auto &cell : row) 
            {
                cell = '~';
            }
        }
        
        std::cout << "Player 1 - place your ships" << std::endl;

        // Place destroyer
        std::cout << "First placement:  DESTROYER" << std::endl;
        place_ship(player1_board, DESTROYER_SIZE, 'D');

        // // Place submarine
        std::cout << "Second placement: SUBMARINE" << std::endl;
        place_ship(player1_board, SUBMARINE_SIZE, 'S');

        // Place battleship
        std::cout << "Third placement: BATTLESHIP " << std::endl;
        place_ship(player1_board, BATTLESHIP_SIZE, 'B');

        // Place carrier
        std::cout << "Third placement: BATTLESHIP " << std::endl;
        place_ship(player1_board, CARRIER_SIZE, 'C');

        print_board(player1_board);

        
        std::cout << "Player 2 - place your ships" << std::endl;
        // Place destroyer
        std::cout << "First placement:  DESTROYER" << std::endl;
        place_ship(player2_board, DESTROYER_SIZE, 'D');

        // Place submarine
        std::cout << "Second placement: SUBMARINE" << std::endl;
        place_ship(player2_board, SUBMARINE_SIZE, 'S');

        // Place battleship
        std::cout << "Third placement: BATTLESHIP " << std::endl;
        place_ship(player2_board, BATTLESHIP_SIZE, 'B');

        // Place carrier
        std::cout << "Third placement: BATTLESHIP " << std::endl;
        place_ship(player2_board, CARRIER_SIZE, 'C');

        print_board(player2_board);

        std::cout << std::endl;
        std::cout << "++++++++++++++++++++++++++" << std::endl;
        std::cout << "+ LET THE BATTLE BEGINS! +" << std::endl;
        std::cout << "++++++++++++++++++++++++++\n" << std::endl;
        
        // Start the game
        while(!start_game)
        {   
            if(turn == 1)
            {   
                std::cout << "Player 1's turn!\n";
                strike(1, player2_board);
                print_board(player2_board);
            }
            else
            {
                std::cout << "Player 2's turn!\n";
                strike(2, player1_board);
                print_board(player1_board);

            }    
            
            bool ships_sunk {true};
            // Check for all the ships to be sunk
            for(int i = 0; i < BOARD_SIZE; ++i)
            {
                for(int j = 0; j < BOARD_SIZE; ++j)
                {
                    if(turn == 1 && player2_board[i][j] == 'D' || player2_board[i][j] == 'S'
                    || player2_board[i][j] == 'B' || player2_board[i][j] == 'C')
                    {
                        ships_sunk = false;
                        break;
                    }
                    else if(turn == 2 && player1_board[i][j] == 'D')
                    {
                        ships_sunk = false;
                        break;
                    }
                }
            } 
            if(ships_sunk)
            {   
                std::cout << "GAME OVER! Player " << turn << " wins!" << std::endl;
                start_game = true;
            }
            // Switch turn
            if(turn == 1)
            {
                turn = 2;
            }
            else
            {
                turn = 1;
            }
        }   
    }
    return 0;
}

// Functions definition
void print_board(std::array<std::array<char, BOARD_SIZE> , BOARD_SIZE> grid) // Print the board of the selected player
{   
    std::cout << "   ";

    for(int i = 0; i < BOARD_SIZE; ++i)
    {   
        // Convert to char the corresponding ASCII number
        std::cout << static_cast<char>('A' + i) << " ";
    }

    std::cout << std::endl;
    for(int i = 0; i < BOARD_SIZE; ++i)
    {   
        std::cout << i << "  ";

        for(int j = 0; j < BOARD_SIZE; ++j)
        {
            std::cout << grid[i][j] << " ";
        }
        std:: cout << "\n";
    }
}

// Function to place a certain on a given board
void place_ship(std::array<std::array<char, BOARD_SIZE> , BOARD_SIZE> &grid, int size, char mark)
{
    int row;
    int col;
    char direction; // horizontal - vertical
    bool is_placed {false}; // Check for a ship to be placed
    
    // Keep prompting the user to insert a valid input
    while(!is_placed)
    {  
        std::cout << "Select row (0 1 2 3 4 5 6 7 8 9) -> ";
        while(true)
        {   
            std::cin >> row;
            if(std::cin.fail())
            {
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a valid input for row (0 1 2 3 4 5 6 7 8 9) -> ";
            }
            else
            {
                break;
            }
        }

        std::cout << "Select col (0 1 2 3 4 5 6 7 8 9) -> ";

        // Keep prompting the user to insert a valid input
        while(true)
        {   
            std::cin >> col;
            if(std::cin.fail())
            {
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a valid input for col (0 1 2 3 4 5 6 7 8 9) -> ";
            }
            else
            {
                break;
            }
        }

        std::cout << "Select direction (h: horizontal - v: vertical) > ";
        std::cin >> direction;
    
        // Check valid horizontal placement
        if(direction == 'h' || direction == 'H')
        {
            if(col + size > BOARD_SIZE) // Check for board limits
            {
                std::cout << "Invalid placement: out of board limits" << std::endl;
            }
            else
            {
                bool overlap = false; // Check for overlapping ships

                for(int i = col; i < col + size; ++i)
                {
                    if(grid[row][i] != '~')
                    {   
                        overlap = true;
                        break;
                    }
                }
                if(overlap)
                {
                    std::cout << "Invalid placement: overlapping existing ship\n";
                }
                else
                {
                    is_placed = true;
                    for(int i = col; i < col + size; ++i)
                    {
                        grid[row][i] = mark; // Placement succeeded
                    }
                }
            }
        }  
        else if(direction == 'v' || direction == 'V') // Check valid vertical placement
        {
            if(row + size > BOARD_SIZE) // Check for board limits
            {
                std::cout << "Invalid placement: out of board limits" << std::endl;
            }
            else
            {   
                bool overlap = false;

                for(int i = row; i < row + size; ++i)
                {
                    if(grid[i][col] != '~')
                    {
                        overlap = true;
                        break;
                    }
                }
                if(overlap)
                {
                    std::cout << "Invalid placement: overlapping existing ship\n";
                }
                else
                {
                    is_placed = true;
                    for(int i = row; i < row + size; ++i)
                    {
                        grid[i][col] = mark;
                    }
                }
            }
        }
        else
        {
            std::cout << "Invalid input: enter h or v" << std::endl;
        }
    }
}

// Function to attack player's ship
void strike(int turn,  std::array<std::array<char, BOARD_SIZE>, BOARD_SIZE> &enemy)
{   
    int coordX;
    int coordY;  

    std::cout << "Enter X coord. > ";       
    
    // Keep prompting the user to insert the right value 
    while(true)
    {   
        std::cin >> coordX; // Accept X coordinate

        if(std::cin.fail())
        {
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Insert valid X cordinate > ";
            break;
        }
        else
        {
            break;
        }
    }

    std::cout << "Enter Y coord. > ";

    while(true)
        {   
            std::cin >> coordY; // Accept Y coordinate

            if(std::cin.fail())
            {
                std::cin.clear();  
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Insert valid Y cordinate > ";
            }
            else
            {
                break;
            }
        }

    if(enemy[coordX][coordY] == '~') // Miss
    {
        std::cout << "You missed!" << std::endl;
        std::cout << "Player " << turn << " shot at coordinates ( " << coordX  << "; " << coordX  << " )" << std::endl;
        enemy[coordX][coordY] = 'O';
    }
    else if(enemy[coordX][coordY] == 'D' || enemy[coordX][coordY] == 'S' || enemy[coordX][coordY] == 'B' 
    || enemy[coordX][coordY] == 'C') // Hit
    {
        std::cout << "Hit!" << std::endl;
        std::cout << "Player " << turn << "shot at coordinates ( " << coordX  << "; " << coordX  << " )" << std::endl;
        enemy[coordX][coordY] = 'X';
    } 
    else // Invalid location
    {
        std::cout << "Invalid location: you already shot here!" << std::endl;
    }
}

// Function to generate random numbers 
int random_turn(int initial, int last) 
{   
    std::random_device rd;  // Random device engine, usually based on /dev/random on UNIX-like systems
    std::mt19937_64 rng(rd()); 
    std::uniform_int_distribution<int> distribution(initial, last);
    return distribution(rng);  // Use rng as a generator
}

// Welcoming banner - Doom style
void welcome_menu()
{   
    std::cout << R"(

        ------------------------------------------------------
        |   ______       _   _   _           _     _         |
        |   | ___ \     | | | | | |         | |   (_)        |
        |   | |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __    |
        |   | ___ \/ _` | __| __| |/ _ \/ __| '_ \| | '_ \   |
        |   | |_/ / (_| | |_| |_| |  __/\__ \ | | | | |_) |  |
        |   \____/ \__,_|\__|\__|_|\___||___/_| |_|_| .__/   |
        |                                           | |      |
        |                                           |_|      |
        ------------------------------------------------------
                    [+] Developed by maxcohen [+]

                         PLAY [p] - QUIT [q]
    )";

    std::cout << std::endl;

}

// Keep prompting the user to insert 'p' or 'q' and return a char
char play_quit()
{
    char answer;
    while(true)
    {
        std::cout << " > ";
        std::cin >> answer;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter 'p' or 'q'";
        }
        else if(answer == 'p' || answer == 'q')
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Enter 'p' or 'q'";
        }
    }
    return answer;
}