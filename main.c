#include <stdio.h>
#include <unistd.h>

#define NUM_EXECUTIVE_SEATS 10
#define NUM_ECONOMY_SEATS 18

typedef struct reservation
{
    char clientName[50];
    int clientAge;
    int clientContact;
    char clientGender;
    char travelClass;
    int seatNumber;
} Reservation;

void displaySeats(const int seats[], int numSeats) {
    printf("Available Seats:\n");
    for (int i = 0; i < numSeats; ++i) {
        if (seats[i] == 0) {
            printf("Seat %d\n", i + 1);
        }
    }
    printf("\n");
}

void print_reservation (Reservation client){
    printf("Name: %s\n", client.clientName);
    printf("Age: %d\n", client.clientAge);
    printf("Contact: %d\n", client.clientContact);
    printf("Gender: %c\n", client.clientGender);
    printf("Seat Number: %d\n", client.seatNumber);
};

void seatReservation(int seats[], int numSeats, char travelClass) {
    struct reservation newClient;

    printf("Enter reservation name: ");
    scanf("%49s", newClient.clientName);

    printf("Enter your age: ");
    scanf("%d", &newClient.clientAge);

    printf("Enter your contact information: ");
    scanf("%d", &newClient.clientContact);

    printf("Enter your gender: ");
    scanf(" %c", &newClient.clientGender);

    newClient.travelClass = travelClass;

    printf("Enter your preferred seat number: ");
    scanf("%d", &newClient.seatNumber);


    if (newClient.seatNumber < 1 || newClient.seatNumber > numSeats || seats[newClient.seatNumber - 1] == 1) {
        printf("Invalid seat number or seat has already booked. Please choose another seat.\n");
        return;
    }
    seats[newClient.seatNumber - 1] = 1;

    FILE *file = fopen("client_manifest.txt", "a");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "%s %d %d %c %c %d\n", newClient.clientName, newClient.clientAge,
            newClient.clientContact, newClient.clientGender, newClient.travelClass,
            newClient.seatNumber);

    fclose(file);

    printf("Your booking details:\n");
    print_reservation(newClient);
}
void displayReservationFromFile(){

    FILE *file = fopen("client_manifest.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    printf("\nReservation Details:\n");

    Reservation newClient; // Declare a variable of type Reservation

    fseek(file, -sizeof(Reservation), SEEK_END);

    // Read the last entry
    fscanf(file, "%s %d %d %c %c %d\n", newClient.clientName, &newClient.clientAge,
           &newClient.clientContact, &newClient.clientGender, &newClient.travelClass,
           &newClient.seatNumber);

    print_reservation(newClient);

    fclose(file);
}

int main() {
    int executiveSeats[NUM_EXECUTIVE_SEATS] = {0};
    int economySeats[NUM_ECONOMY_SEATS] = {0};
    char travelClass;
    int seatNumber;

    printf("Hello!\nWelcome to GARI BOOKING.\n");
    sleep(2);

    printf("What type of vehicle would you prefer? Select 1.Economy 2.Executive\n");
    scanf(" %c", &travelClass);

    switch (travelClass) {
        case '1':
            printf("You have selected to travel in the Economy Class.\n");
            printf("Select a specific seat for your travel.\n");
            printf("The following are the available seats:\n");

            displaySeats(economySeats, NUM_ECONOMY_SEATS);

            seatReservation(economySeats, NUM_ECONOMY_SEATS, travelClass);
            break;

        case '2':
            printf("You have selected to travel in the Executive class.\n");
            printf("Select a specific seat for your travel.\n");
            printf("The following are the available seats:\n");

            displaySeats(executiveSeats, NUM_EXECUTIVE_SEATS);

            seatReservation(executiveSeats, NUM_EXECUTIVE_SEATS, travelClass);
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    displayReservationFromFile();

    printf("Your booking details have been saved.\n");

    return 0;
}
