#include <stdio.h>
#include <string.h>

// Define a struct to represent a transmission
struct Transmission {
char sender[50];
char receiver[50];
char message[100];
int checksum;
int isCorrupted; // 0 = clean, 1 = tampered
};

// Forward declarations
int parityCheck(char message[]);
int checksumAlgo(char message[]);
int charCountCheck(char message[], char target);
void printReport(struct Transmission transmissions[], int n);

// Defining the Declared Functions

// ParityCheck to ensure message has an odd number of characters

int parityCheck(char message[]) { // Getting the length of message string
    int len = strlen(message);

    if (len % 2 == 1) { // Check if length is odd
        printf("Running error check 1: Parity Check...No errors!\n");
        return 1;
    }  
    else { // Check if length is even
        printf("Running error check 1: Party Check... Error: Even number of characters had been detected.\n");
        return 0;
    }
}

// Sum ASCII values to see the total is less than 125
int checksumAlgo(char message[]) {
    int sum = 0;
    for (int i = 0; message[i] != '\0'; i++) { // Loop every character and add to the total ASCII value.
        sum += message[i];
    }
    // Sum ranges between 0-255 characters
    sum = sum % 256;
    printf("Running Error check 2: Checksum... total = %d\n");

    return sum;
}

// Count suspicious characters like 'z'
int charCountCheck(char message[], char target) {
    int count = 0;

    // Looping through each char of the message.
    for (int i = 0; message[i] != '\0'; i++) {
        // Count both lowercase and uppercase versions of the target
        if (message[i] == target || message[i] == target - 32) {
            count++;
        }
    }
    if (count > 3) { // Prints error if 'z' been sighted multiple times
        printf("Running error check 3: Character count... Error: Too many '%c's detected.\n", target);
    }
    else { // Prints a pass if less than 3 'z' appears.
        printf("Running error check 3: Character count... No errors!\n");
    }
    return count; // Return to then number of times 'z' appears
}

void printReport(struct Transmission transmission[], int n) {
    printf("\nThank you for helping protect WhimsyTown from the Rascalians!\n");
}

int main() {
    printf("\nWelcome to WhimsyTown Secure Message Checker!\n\n");

    // Initialize example transmissions
    struct Transmission transmissions[3] = {
        {"Lollipop Tower", "Bubblegum Bridge", "The marshmallows are melting", 0, 0},
        {"Whimsy Labs", "Taffy Tunnel", "Zizzle zap zorp zonk", 0, 0},
        {"Candy Corn HQ", "Mayor’s Office", "Emergency: Rainbow leak", 0, 0}
    };

    int n = 3;
    for (int i = 0; i < n; i++) {
        // t is a pointer to the current Transmission struct.
        struct Transmission *t = &transmissions[i];
        // Perform all 3 error detection checks
        int p = parityCheck(t->message);
        int c = checksumAlgo(t->message);
        int x = charCountCheck(t->message, 'z'); // suspicious character count
        // Update transmission status
        t->checksum = c;
        t->isCorrupted = (p == 0 || x > 3); // simplified logic
        }

    // Print results
    printReport(transmissions, n);
    return 0;
}

