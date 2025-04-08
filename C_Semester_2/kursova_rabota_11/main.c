#include <stdio.h>
#include <stdlib.h>

int sumOfDigits(int num) {
    if (num == 0) {
        return 0;
    } else {
        return num % 10 + sumOfDigits(num / 10);
    }
}

int sumOfDigitsInRange(int A, int B) {
    if (A > B) {
        return 0;
    } else {
        return sumOfDigits(A) + sumOfDigitsInRange(A + 1, B);
    }
}

int main() {
    int A, B;

    printf("Enter the values of A and B (separated by space): ");
    scanf("%d %d", &A, &B);

    printf("Sum of digits in the range [%d...%d]: %d\n", A, B, sumOfDigitsInRange(A, B));

    return 0;
}
