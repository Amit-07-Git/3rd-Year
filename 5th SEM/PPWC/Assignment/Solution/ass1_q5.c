#include <stdio.h>

int main() {
    char desiredGrade;
    float minAverage, currentAverage, finalWeight, neededScore;
    printf("Enter desired grade> ");
    scanf(" %c", &desiredGrade);
    printf("Enter minimum average required> ");
    scanf("%f", &minAverage);
    printf("Enter current average in course> ");
    scanf("%f", &currentAverage);
    printf("Enter how much the final counts\nas a percentage of the course grade> ");
    scanf("%f", &finalWeight);
    neededScore = (minAverage - currentAverage * (1 - finalWeight / 100.0f)) / (finalWeight / 100.0f);
    printf("You need a score of %.2f on the final to get a %c.\n", neededScore, desiredGrade);
    return 0;
}
