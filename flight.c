// Online C++ compiler to run C++ program online
#include <iostream>

#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 5
#define MAX_BOOKINGS 5

// Structure to hold flight details
typedef struct {
    int flight_id;
    char flight_name[30];
    char departure[30];
    char arrival[30];
    int seats_available;
} Flight;

// Structure to hold booking details
typedef struct {
    int booking_id;
    int flight_id;
    char passenger_name[50];
} Booking;

// Initialize flight data
Flight flights[MAX_FLIGHTS] = {
    {1, "Air India 101", "New York", "London", 5},
    {2, "Emirates 202", "Dubai", "Paris", 4},
    {3, "Delta 303", "Los Angeles", "Tokyo", 2},
    {4, "British Airways 404", "London", "New York", 3},
    {5, "Qatar Airways 505", "Doha", "Sydney", 6}
};

// Array to store bookings
Booking bookings[MAX_BOOKINGS];

// Function to display available flights
void display_flights() {
    printf("\nAvailable Flights:\n");
    printf("ID\tFlight Name\t\t\tDeparture\tArrival\tSeats Available\n");
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (flights[i].seats_available > 0) {
            printf("%d\t%s\t\t%s\t%s\t%d\n", flights[i].flight_id, flights[i].flight_name, 
                   flights[i].departure, flights[i].arrival, flights[i].seats_available);
        }
    }
}

// Function to book a flight
void book_flight() {
    int flight_id, booking_id;
    char passenger_name[50];

    display_flights();
    
    printf("\nEnter Flight ID to book: ");
    scanf("%d", &flight_id);

    int flight_index = -1;
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (flights[i].flight_id == flight_id && flights[i].seats_available > 0) {
            flight_index = i;
            break;
        }
    }

    if (flight_index == -1) {
        printf("Invalid flight ID or no seats available.\n");
        return;
    }

    printf("Enter your name: ");
    getchar();  // To consume newline character from previous input
    fgets(passenger_name, 50, stdin);
    passenger_name[strcspn(passenger_name, "\n")] = '\0';  // Remove trailing newline

    // Find a free booking slot
    for (int i = 0; i < MAX_BOOKINGS; i++) {
        if (bookings[i].booking_id == 0) {
            booking_id = i + 1;  // Start booking IDs from 1
            bookings[i].booking_id = booking_id;
            bookings[i].flight_id = flight_id;
            strcpy(bookings[i].passenger_name, passenger_name);
            flights[flight_index].seats_available--;
            printf("\nBooking successful! Your booking ID is %d\n", booking_id);
            return;
        }
    }

    printf("Booking limit reached. No available booking slots.\n");
}

// Function to cancel a booking
void cancel_booking() {
    int booking_id;

    printf("\nEnter your booking ID to cancel: ");
    scanf("%d", &booking_id);

    int booking_index = -1;
    for (int i = 0; i < MAX_BOOKINGS; i++) {
        if (bookings[i].booking_id == booking_id) {
            booking_index = i;
            break;
        }
    }

    if (booking_index == -1) {
        printf("Invalid booking ID.\n");
        return;
    }

    int flight_id = bookings[booking_index].flight_id;
    int flight_index = -1;
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (flights[i].flight_id == flight_id) {
            flight_index = i;
            break;
        }
    }

    flights[flight_index].seats_available++;
    bookings[booking_index].booking_id = 0;  // Mark the booking as canceled
    printf("\nBooking canceled successfully.\n");
}

// Function to view all current bookings
void view_bookings() {
    printf("\nCurrent Bookings:\n");
    for (int i = 0; i < MAX_BOOKINGS; i++) {
        if (bookings[i].booking_id != 0) {
            printf("Booking ID: %d, Passenger: %s, Flight ID: %d\n", bookings[i].booking_id, 
                   bookings[i].passenger_name, bookings[i].flight_id);
        }
    }
}

// Main function to display the menu
int main() {
    int choice;

    while (1) {
        printf("\n--- Flight Reservation System ---\n");
        printf("1. Display available flights\n");
        printf("2. Book a flight\n");
        printf("3. Cancel a booking\n");
        printf("4. View current bookings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_flights();
                break;
            case 2:
                book_flight();
                break;
            case 3:
                cancel_booking();
                break;
            case 4:
                view_bookings();
                break;
            case 5:
                printf("Exiting the system...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
