#include <stdio.h>

#define MAX_ROOMS 5

void displayMenu(){
        printf("===== Smart Home Menu =====\n");
        printf("1. Toggle Light\n");
        printf("2. Read Temperature\n");
        printf("3. Check Motion Sensor\n");
        printf("4. Lock/Unlock Security System\n");
        printf("5. House Status Summary\n");
        printf("6. Exit\n");
}

void initializeSystem(int roomCount, int lights[], int temp[], int motion[], int locks[]) {
    for (int i = 0; i < roomCount; i++) {
        lights[i] = 0;  
        temp[i] = 22 + (i % 5);  
        motion[i] = 0; 
        locks[i] = 1; 
    }
    printf("Initializing system...\n");
}

void controlLights(int room, int lights[]) {
    if (lights[room] == 0) {
        lights[room] = 1; 
        printf("Light in Room %d is now ON.\n", room + 1);
    } else {
        lights[room] = 0;
        printf("Light in Room %d is now OFF.\n", room + 1);
    }
}

void readTemperature(int room, int temp[]) {
    printf("Temperature in Room %d is %d°C.\n", room + 1, temp[room]);
}

void detectMotion(int motion[]) {
    int detected = 0;
    for (int i = 0; i < 5; i++) {
        if (motion[i] == 1) {
            detected = 1;
            break;
        }
    }
    if (detected)
        printf("Motion detected in the house.\n");
    else
        printf("No motion detected.\n");
}

void securitySystem(int room, int locks[]) {
    if (locks[room] == 1) {
        locks[room] = 0; 
        printf("Door in Room %d is now UNLOCKED.\n", room + 1);
    } else {
        locks[room] = 1;  
        printf("Door in Room %d is now LOCKED.\n", room + 1);
    }
}

void analyzeHouseStatus(int roomCount, int lights[], int temp[], int motion[], int locks[]) {
    printf("House Status:\n");
    for (int i = 0; i < roomCount; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s Motion, %s\n",
            i + 1,
            lights[i] == 0 ? "OFF" : "ON",
            temp[i],
            motion[i] == 0 ? "No" : "Detected",
            locks[i] == 0 ? "Unlocked" : "Locked");
    }
}

void checkAutoLock(int roomCount, int motion[], int locks[], int *noMotionCount) {
    for (int i = 0; i < roomCount; i++) {
        if (motion[i] == 0) {
            (*noMotionCount)++;
        } else {
            *noMotionCount = 0;
        }
    }
    
    if (*noMotionCount >= 5) {
        printf("Auto-locking all doors due to no motion detected for 5 inputs.\n");
        for (int i = 0; i < roomCount; i++) {
            locks[i] = 1;
        }
    }
}

void checkTemperatureAlert(int roomCount, int temp[]) {
    for (int i = 0; i < roomCount; i++) {
        if (temp[i] > 30) {
            printf("Warning: Room %d temperature is above 30°C! Current Temp: %d°C.\n", i + 1, temp[i]);
        }
    }
}

void energySavingMode(int roomCount, int lights[]) {
    int allLightsOn = 1;
    for (int i = 0; i < roomCount; i++) {
        if (lights[i] == 0) {
            allLightsOn = 0;
            break;
        }
    }
    if (allLightsOn) {
        printf("Energy Saving Mode: All lights are ON for too long, consider turning them OFF.\n");
    }
}

int main() {

    int roomCount;    
    printf("Enter number of rooms: ");
    while(1){
        scanf("%d", &roomCount);
        if (roomCount <= MAX_ROOMS) break;    
        printf("Please enter a valid number of rooms: ");      
    }
    int lights[roomCount], temp[roomCount], motion[roomCount], locks[roomCount];
    int noMotionCount = 0; 
    initializeSystem(roomCount, lights, temp, motion, locks);    
    int choice, room;
    
    while (choice != 6) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice == 6) break;
        switch(choice) {
            case 1:
                printf("Enter room number to toggle light (1-%d): ", roomCount);
                scanf("%d", &room);
                controlLights(room - 1, lights);
                break;
            case 2:
                printf("Enter room number to read temperature (1-%d): ", roomCount);
                scanf("%d", &room);
                readTemperature(room - 1, temp);
                break;
            case 3:
                detectMotion(motion);
                break;
            case 4:
                printf("Enter room number to lock/unlock security system (1-%d): ", roomCount);
                scanf("%d", &room);
                securitySystem(room - 1, locks);
                break;
            case 5:
                analyzeHouseStatus(roomCount, lights, temp, motion, locks);
                checkAutoLock(roomCount, motion, locks, &noMotionCount);
                checkTemperatureAlert(roomCount, temp);
                energySavingMode(roomCount, lights);
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
        printf("Exiting...\n");      
    }    
    return 0;
}
