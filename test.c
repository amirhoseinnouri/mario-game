#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>


#define WIDTH 100
#define HEIGHT 12
#define MARIO '@' 
#define EMPTY ' '
#define BRICK '#'
#define STEP '['
#define FLAG '>'

#define MARIO_EMOJI "👾"
#define BRICK_EMOJI "🧱"
#define STEP_EMOJI "🔲"
#define FLAG_EMOJI "🏁"


#define MAX_USERS 100
#define MAX_NAME 20
#define DATA_FILE "users.dat"

typedef struct {
    char username[MAX_NAME];
    char password[MAX_NAME];
    int gamesPlayed;
} User;

User users[MAX_USERS];
int userCount = 0;
User *currentUser = NULL;
char gameHistory[1000];
int marioX = 2, marioY = HEIGHT - 2;
int score = 0;
char gameBoard[HEIGHT][WIDTH];

void initGame(int mapChoice);
void drawGame();
void moveMario(int dx, int dy);
void gameLoop();
void mainMenu();
void signUp();
void signIn();
void viewHistory();
void changePassword();
void loadUsers();
void saveUsers();
void saveGameHistory(const char* result);
void displayMapChoice();
void loadGameHistory();

void initGame(int mapChoice) {
    char *map1[] = {
        "####################################################################################################",
        "#                                        👾        |  |                                            #",
        "#                👾👾                    👾👾👾       |  |                                         #",
        "#               👾👾👾                    👾        |  |                                           #",
        "#                                                🔲🔲🔲🔲🔲                                        #",
        "#                                                 🔲🔲🔲                    🔲🔲🔲🔲🔲🔲🔲🔲       #",
        "#                                                                              |   |                #",
        "#          🔲🔲🔲🔲                                                   🔲🔲🔲🔲🔲   |   |            #",
        "#          🔲🔲🔲🔲   🔲🔲🔲🔲                                            |  |     |   |            #",
        "#                   🔲🔲🔲🔲                                   🔲🔲🔲🔲   |  |     |   |            #",
        "#                                                             |  |    |  |     |   |   end=>🏁      #",
        "####################################################################################################"
    };
    
    char *map2[] = {
        "####################################################################################################",
        "#                                        👾        |  |                                            #",
        "#                👾👾                    👾👾👾       |  |                                         #",
        "#               👾👾👾                    👾        |  |                                           #",
        "#                                                🔲🔲🔲🔲🔲                                        #",
        "#                                                 🔲🔲🔲                    🔲🔲🔲🔲🔲🔲🔲🔲       #",
        "#                                                                              |   |                #",
        "#          🔲🔲🔲🔲                                                   🔲🔲🔲🔲🔲   |   |           #",
        "#          🔲🔲🔲🔲   🔲🔲🔲🔲                                            |  |     |   |            #",
        "#                   🔲🔲🔲🔲                                   🔲🔲🔲🔲   |  |     |   |            #",
        "#                                                             |  |    |  |     |   |   end=>🏁      #",
        "####################################################################################################"
    };
    
    char **map = (mapChoice == 1) ? map1 : map2;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            gameBoard[y][x] = map[y][x];
        }
    }
}


void drawGame() {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == marioX && y == marioY) {
                printw("%s", MARIO_EMOJI);  
            } else if (gameBoard[y][x] == '#') {
                printw("%s", BRICK_EMOJI); 
            } else if (gameBoard[y][x] == '[') {
                printw("%s", STEP_EMOJI); 
            } else if (gameBoard[y][x] == '>') {
                printw("%s", FLAG_EMOJI); 
            } else {
                printw("%c", gameBoard[y][x]);
            }
        }
        printw("\n");
    }
    refresh();
}


void moveMario(int dx, int dy) {
    int newX = marioX + dx;
    int newY = marioY + dy;

    if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT) {
        if (gameBoard[newY][newX] != '#' && gameBoard[newY][newX] != BRICK) {
            marioX = newX; 
        }
    }


    if (gameBoard[marioY][marioX] == '>') {
        score += 100; 
        printw("\nYou reached the end! Your score is: %d\n", score); 
        usleep(2000000);
        endwin();
        exit(0); 
    }
}


void gameLoop() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    while (1) {
        drawGame();
        int ch = getch();
        if (ch == 'q') break;
        else if (ch == KEY_RIGHT) moveMario(1, 0);
        else if (ch == KEY_LEFT) moveMario(-1, 0);
        else if (ch == KEY_UP) moveMario(0, -1); 
        else if (ch == KEY_DOWN) moveMario(0, 1);
        usleep(50000); 
    }
    endwin();
}


void mainMenu() {
    int choice;
    while (1) {
        printf("\n1. Start Game\n2. Sign Up\n3. Sign In\n4. View History\n5. Change Password\n6. Exit\nChoose an option: ");
        scanf("%d", &choice);
        if (choice == 1) {
            displayMapChoice();  
            gameLoop();
        } else if (choice == 2) {
            signUp();
        } else if (choice == 3) {
            signIn();
        } else if (choice == 4) {
            viewHistory();
        } else if (choice == 5) {
            changePassword();
        } else if (choice == 6) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }
}


void displayMapChoice() {
    int mapChoice;
    printf("\nSelect the map:\n1. Map 1\n2. Map 2\nEnter your choice: ");
    scanf("%d", &mapChoice);
    initGame(mapChoice);  
}


void signUp() {
    char username[MAX_NAME], password[MAX_NAME];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("User already exists!\n");
            return;
        }
    }

    // Add new user
    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].gamesPlayed = 0;
    userCount++;
    saveUsers();
    printf("Account created successfully!\n");
}

void signIn() {
    char username[MAX_NAME], password[MAX_NAME];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);


    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            currentUser = &users[i];
            printf("Welcome, %s!\n", username);
            return;
        }
    }
    printf("Invalid credentials!\n");
}


void viewHistory() {
    if (currentUser == NULL) {
        printf("You must be logged in to view history!\n");
        return;
    }

    printf("Game History for %s:\n%s", currentUser->username, gameHistory);
}

// Change password
void changePassword() {
    if (currentUser == NULL) {
        printf("You must be logged in to change your password!\n");
        return;
    }

    char newPassword[MAX_NAME];
    printf("Enter new password: ");
    scanf("%s", newPassword);

    strcpy(currentUser->password, newPassword);
    saveUsers();
    printf("Password changed successfully!\n");
}


void loadUsers() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        return;  // No users yet, file doesn't exist
    }

    while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
        userCount++;
    }
    fclose(file);
}


void saveUsers() {
    FILE *file = fopen(DATA_FILE, "w");
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }
    fclose(file);
}


void saveGameHistory(const char* result) {
    if (currentUser == NULL) {
        return;
    }
    strcat(gameHistory, currentUser->username);
    strcat(gameHistory, " ");
    strcat(gameHistory, result);
    strcat(gameHistory, "\n");
    currentUser->gamesPlayed++;
    saveUsers();
}

void loadGameHistory() {
    FILE *file = fopen("gameHistory.dat", "r");
    if (file != NULL) {
        fread(gameHistory, sizeof(gameHistory), 1, file);
        fclose(file);
    }
}

int main() {
    srand(time(NULL));
    loadUsers();
    loadGameHistory();
    mainMenu();
    return 0;
}

//end 
