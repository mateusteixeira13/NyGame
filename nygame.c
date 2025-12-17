#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep((x)/1000)
#else
#include <unistd.h>
#endif


typedef struct {
    int age;
    char name[250];
} UserData_t;

typedef struct {
    int errors;
} ApplicationGuard_t;

typedef enum{
    OK_INPUT,
    NO_INPUT
} UserInput;

typedef struct{
    int option;
    char choice[4];
    char text[251];
    int a;
    int b;
    int c;
} ApplicationData_t;

#define RELEASE "0.1"


ApplicationGuard_t app_status = {0};

void clear_user_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

UserInput getuser_name(UserData_t *data){
    while (1) {
        if (fgets(data->name, sizeof(data->name), stdin) == NULL) {
            app_status.errors++;
            return NO_INPUT; 
        }

        data->name[strcspn(data->name, "\n")] = '\0';

        if (data->name[0] != '\0') {
            return OK_INPUT;
        }

        printf("Oops! An error occurred, please try typing again!: ");
        app_status.errors++;
    }
    return NO_INPUT;
}

void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menu(){
    clear();
    printf("========== Menu =============\n");
    printf("1- Type a text\n");
    printf("2- Games\n");
    printf("3- View my information\n");
    printf("4- About the program and help(?)\n");
    printf("5- Exit\n");
    printf("=============================\n");
}


UserInput text(ApplicationData_t *app_data){
    printf("Maximum 250 characters (Automatically saved)\n");

    FILE *fp = fopen("data.txt", "wb");
    if (!fp) {
        perror("fopen");
        return NO_INPUT;
    }

    fclose(fp);

    while (1) {
        if (fgets(app_data->text, sizeof(app_data->text), stdin) == NULL) {
            app_status.errors++;
            return NO_INPUT; 
        }

        app_data->text[strcspn(app_data->text, "\n")] = '\0';

        if (app_data->text[0] != '\0') {
            FILE *fp = fopen("data.txt", "wb");
            if (!fp) {
                perror("fopen");
                app_status.errors++;
                return NO_INPUT;
            }

            fprintf(fp, "%s", app_data->text);
            fclose(fp);
            return OK_INPUT;
        }

        printf("Oops! An error occurred, please try typing again!: ");
    }

    return NO_INPUT;
}

int ApplicationGuard(){
    if(app_status.errors >= 5){
        clear();
        printf("We interrupted execution because the program presented several significant failures\n");
        printf("What to do?\n");
        printf("Close and reopen the program, or if that doesn't work try restarting the machine\n");
        while (1){
            usleep(16);
        }
    }
    return 0;
}

UserInput math_game(ApplicationData_t *app_data){
    int answer = 0;
    math:
        app_data->a = rand() % 1000 + 1;
        app_data->b = rand() % 1000 + 1;
        app_data->c = app_data->a + app_data->b;
        printf("How much is: %d + %d?\n", app_data->a, app_data->b);
        scanf("%d", &app_data->option);
        clear_user_input();
      
        answer = app_data->option;
        if(answer == app_data->c){
            printf("Correct answer!\n");
        } else {
            printf("Oops! Wrong answer, the answer is %d\n", app_data->c);
        }
        while (1){
            printf("Do you want to continue? y/n: ");
            fgets(app_data->choice, sizeof(app_data->choice), stdin);
            app_data->choice[strcspn(app_data->choice, "\n")] = '\0';

            clear_user_input();
            if(strcmp(app_data->choice, "y") == 0){
                goto math;
            } else if(strcmp(app_data->choice, "n") == 0){
                menu();
                break;
            }
        }
        
    return OK_INPUT;
}

UserInput guessing_game(ApplicationData_t *app_data){
    int answer = 0;
    guess:
        app_data->c = rand() % 10 + 1;
        
        printf("\nGuessing Game!\n");
        printf("I'm thinking of a number from 1 to 10...\n");
        printf("What number am I thinking of? ");
        scanf("%d", &app_data->option);
        clear_user_input();
      
        answer = app_data->option;
        if(answer == app_data->c){
            printf("Correct answer!\n");
        } else {
            printf("Oops! Wrong answer, the number was %d\n", app_data->c);
        }
        while (1){
            printf("Do you want to continue? y/n: ");
            fgets(app_data->choice, sizeof(app_data->choice), stdin);
            app_data->choice[strcspn(app_data->choice, "\n")] = '\0';

            clear_user_input();
            if(strcmp(app_data->choice, "y") == 0){
                goto guess;
            } else if(strcmp(app_data->choice, "n") == 0){
                menu();
                break;
            }
        }
        
    return OK_INPUT; 
}

UserInput three_cups(ApplicationData_t *app_data){
    int answer = 0;

    three:
        app_data->c = rand() % 3 + 1;
    
        printf("1- Cup 1\n");
        printf("2- Cup 2\n");
        printf("3- Cup 3\n");
        printf("Which cup is the ball in? ");
        scanf("%d", &app_data->option);
        clear_user_input();
      
        answer = app_data->option;
        if(answer == app_data->c){
            printf("Correct answer!\n");
        } else {
            printf("Oops! Wrong answer, the ball was in cup %d\n", app_data->c);
        }
        while (1){
            printf("Do you want to continue? y/n: ");
            fgets(app_data->choice, sizeof(app_data->choice), stdin);
            app_data->choice[strcspn(app_data->choice, "\n")] = '\0';

            clear_user_input();
            if(strcmp(app_data->choice, "y") == 0){
                goto three;
            } else if(strcmp(app_data->choice, "n") == 0){
                menu();
                break;
            }
        }
        
    return OK_INPUT;
}

UserInput games(ApplicationData_t *app_data){
    printf("Welcome! List of games:\n");
    printf("1- Math game\n");
    printf("2- Guessing game\n");
    printf("3- Three Cups game\n");
    printf("4- Return to main menu\n");
    while (1){
        printf("Please enter your choice: ");
        if(!scanf("%d", &app_data->option)){
            printf("Please enter a valid option\n");
            clear_user_input();
            continue;
        } else {
            clear_user_input();
            break;
        }
    }
    switch (app_data->option){
    case 1:
        math_game(app_data);
        break;
    case 2:
        guessing_game(app_data);
        break;
    case 3:
        three_cups(app_data);
        break;
    case 4:
        menu();
        break;
    default:
        app_status.errors++;
        break;
    }
    return OK_INPUT;

}

void info(UserData_t *data, ApplicationData_t *app_data){
    printf("Name: %s\n", data->name);
    printf("Age: %d\n", data->age);
    printf("To return to the main menu type y: ");
    while (1){
        fgets(app_data->choice, sizeof(app_data->choice), stdin);
        app_data->choice[strcspn(app_data->choice, "\n")] = '\0';

        clear_user_input();
        if(strcmp(app_data->choice, "y") == 0){
           menu();
           break;
        } else {
            printf("An error occurred! Type again\n");
            app_status.errors++;
            continue;
        }
    }
}

void about_help(ApplicationData_t *app_data){
    printf("NyGame!\n");
    printf("Version: %s\n", RELEASE);
    printf("Welcome!\n");
    printf("Q- The program failed, what to do?\n");
    printf("A- Wait for the program guard to alarm, or if it doesn't work try closing the program or restarting the machine if it's severe\n");
    printf("To return to the main menu type y: ");
    while (1){
        fgets(app_data->choice, sizeof(app_data->choice), stdin);
        app_data->choice[strcspn(app_data->choice, "\n")] = '\0';

        clear_user_input();
        if(strcmp(app_data->choice, "y") == 0){
           menu();
           break;
        } else {
            printf("An error occurred! Type again\n");
            app_status.errors++;
            continue;
        }
    }
}


UserInput getmenu_input(UserData_t *data, ApplicationData_t *app_data){
    menu();
    while (1){
        printf("Please enter your choice: ");
        if(!scanf("%d", &app_data->option)){
            printf("Please enter a valid option\n");
            clear_user_input();
            continue;
        } else {
            clear_user_input();
            break;
        }
    }
   
    switch (app_data->option){
    case 1:
        text(app_data);
        break;
    case 2:
        games(app_data);
        break;
    case 3:
        info(data, app_data);
        break;
    case 4:
        about_help(app_data);
        break;
    case 5:
        exit(0);
        break;
    default:
        app_status.errors++;
        break;
    }
    return NO_INPUT;
}

int main(){
    UserData_t user = {0};
    ApplicationData_t app_data = {0};

    printf("NyGame!\n");

    srand((time(NULL)));

    printf("Hello and welcome!\n");
    printf("To continue, enter your name: ");
    if(getuser_name(&user) == NO_INPUT){
        printf("An error occurred! Please try again!\n");
        return -1;
    }

    printf("Hello! Welcome %s! What a beautiful name!\n", user.name);
    printf("Now enter your age: ");
    scanf("%d", &user.age);
    clear_user_input();

    clear();

    printf("Welcome! What would you like to do?\n");

    while (1){
        getmenu_input(&user, &app_data);
        ApplicationGuard();
    }
    
    return 0;
}
