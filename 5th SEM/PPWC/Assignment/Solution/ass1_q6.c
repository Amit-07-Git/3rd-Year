#include <stdio.h>

int main() {
    float takeoffSpeed_kmh, distance_m;
    float takeoffSpeed_ms, acceleration, time;

    printf("Enter takeoff speed (km/hr): ");
    scanf("%f", &takeoffSpeed_kmh);

    printf("Enter acceleration distance (meters): ");
    scanf("%f", &distance_m);

    takeoffSpeed_ms = takeoffSpeed_kmh * 1000.0f / 3600.0f;
    
    acceleration = (takeoffSpeed_ms * takeoffSpeed_ms) / (2.0f * distance_m);

    time = takeoffSpeed_ms / acceleration;

    printf("Acceleration: %.2f m/s^2\n", acceleration);
    printf("Time to reach takeoff speed: %.2f seconds\n", time);

    return 0;
}
