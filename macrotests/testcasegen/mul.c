#include <stdio.h>
#include <stdint.h>

#define MIN_24BIT -8388608
#define MAX_24BIT  8388607

int32_t multiply_24bit(int32_t a, int32_t b) {
    int32_t result = a * b;
    if (result > MAX_24BIT) result = MAX_24BIT;
    if (result < MIN_24BIT) result = MIN_24BIT;
    return result;
}

void test_multiply_24bit() {
    int32_t test_cases[] = {
        MIN_24BIT, MIN_24BIT / 2, MIN_24BIT / 4, -1000000, -1000, -100, -10, -1, 
        0, 
        1, 10, 100, 1000, 1000000, MAX_24BIT / 4, MAX_24BIT / 2, MAX_24BIT,
        2, -2, 3, -3, 5, -5, 7, -7, 13, -13, 17, -17, 19, -19,
        844, 9939, 125, 67005, 200, 41943, 300, 27981, 400, 20971, 500, 16777,
        -844, 9939, -125, 67005, -200, 41943, -300, 27981, -400, 20971, -500, 16777
    };

    int num_test_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int lineNo=10000;
    char s[10000];

    for (int i = 0; i < num_test_cases; i++) {
        for (int j = 0; j < num_test_cases; j++) {
            int32_t a = test_cases[i];
            int32_t b = test_cases[j];

            // Skip cases that would cause overflow
            if ((a > 0 && b > 0 && a > MAX_24BIT / b) ||
                (a > 0 && b < 0 && a > MIN_24BIT / b) ||
                (a < 0 && b > 0 && a < MIN_24BIT / b) ||
                (a < 0 && b < 0 && a < MAX_24BIT / b)) {
                continue;
            }

            int32_t result = multiply_24bit(a, b);

            // Expected result using 64-bit multiplication to avoid overflow in calculation
            int64_t expected_result = (int64_t)a * (int64_t)b;
            if (expected_result > MAX_24BIT) expected_result = MAX_24BIT;
            if (expected_result < MIN_24BIT) expected_result = MIN_24BIT;

            sprintf(s,"LET A=%d * %d : IF A <> %d THEN PRINT \"%d*%d should be %d but is calculated as \";A", a, b, result,a,b,result);
            printf("L%d: .data %d, L%d-$-1, \"%s\",0 \r\n", lineNo, lineNo, lineNo+1,s);  

            lineNo++;
        }
    }
    sprintf(s,"PRINT \"OK\":END");
    printf("L%d: .data %d, Lend-$-1, \"%s\",0 \r\n", lineNo, lineNo,s);  

}

int main() {
    test_multiply_24bit();
    return 0;
}
