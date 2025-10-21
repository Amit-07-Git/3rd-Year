#include <stdio.h>
int main() {
    float meters;
    printf("Enter distance in meters: ");
    scanf("%f", &meters);
    printf("+------------------+----------------+\n");
    printf("| %-16s | %-14s |\n", "Unit", "Value");
    printf("+------------------+----------------+\n");
    printf("| %-16s | %14.2f |\n", "Meters", meters);
    printf("| %-16s | %14.2f |\n", "Kilometers", meters * 0.001f);
    printf("| %-16s | %14.2f |\n", "Centimeters", meters * 100.0f);
    printf("| %-16s | %14.2f |\n", "Millimeters", meters * 1000.0f);
    printf("| %-16s | %14.2f |\n", "Feet", meters * 3.28084f);
    printf("| %-16s | %14.2f |\n", "Inches", meters * 39.3701f);
    printf("+------------------+----------------+\n");
    return 0;
}
