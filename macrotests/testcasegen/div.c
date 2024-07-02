#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define MIN_24BIT -8388608
#define MAX_24BIT  8388607

int32_t divide_24bit(int32_t a, int32_t b) {
    // Handle division by zero case
    if (b == 0) {
        return (a < 0) ? MIN_24BIT : MAX_24BIT; // Return max or min 24-bit value
    }
    int32_t result = a / b;
    if (result > MAX_24BIT) result = MAX_24BIT;
    if (result < MIN_24BIT) result = MIN_24BIT;
    return result;
}

void test_divide_24bit() {
    int32_t dividends[] = {
        MIN_24BIT+1, 
        MIN_24BIT / 2, 
        MIN_24BIT / 4, 
        -1000000, -1000, -100, -10, -1, 
        0, 
        1, 10, 100, 1000, 1000000, 
        MAX_24BIT / 4, 
        MAX_24BIT / 2, 
        MAX_24BIT-1,
        2, -2, 3, -3, 5, -5, 7, -7, 13, -13, 17, -17, 19, -19,
        844, -9939, 125, -67005, 200, -41943, 300, -27981, 400, -20971, 500, -16777
    };

    int32_t divisors[] = {
        MIN_24BIT+1, 
        MIN_24BIT / 2, 
        MIN_24BIT / 4, -1000000, -1000, -100, -10, -1, 
        1, 10, 100, 1000, 1000000, 
        MAX_24BIT / 4, 
        MAX_24BIT / 2, 
        MAX_24BIT-1,
        2, -2, 3, -3, 5, -5, 7, -7, 13, -13, 17, -17, 19, -19,
        844, -9939, 125, -67005, 200, -41943, 300, -27981, 400, -20971, 500, -16777
    };

    int num_dividends = sizeof(dividends) / sizeof(dividends[0]);
    int num_divisors = sizeof(divisors) / sizeof(divisors[0]);
    int lineNo=10000;
    char s[10000];

    for (int i = 0; i < num_dividends; i++) {
        for (int j = 0; j < num_divisors; j++) {
            int32_t a = dividends[i];
            int32_t b = divisors[j];

//        if (a<-MAX_24BIT/2+1) continue;
//        if (a>MAX_24BIT/2+1) continue;
//        if (b<-MAX_24BIT/3) continue;
//        if (b>MAX_24BIT/3) continue;


            // Skip division by zero cases
            if (b == 0) continue;

            int32_t result = divide_24bit(a, b);

            // Expected result using 64-bit division to avoid overflow in calculation
            int64_t expected_result = (int64_t)a / (int64_t)b;
            if (expected_result > MAX_24BIT) expected_result = MAX_24BIT;
            if (expected_result < MIN_24BIT) expected_result = MIN_24BIT;

            sprintf(s,"LET A=%d / %d : IF A <> %d THEN PRINT \"%d/%d should be %d but is calculated as \";A", a, b, result,a,b,result);
            printf("L%d: .data %d, L%d-$-1, \"%s\",0 \r\n", lineNo, lineNo, lineNo+1,s);  

            lineNo++;
        }
    }
    sprintf(s,"PRINT \"OK\":END");
    printf("L%d: .data %d, Lend-$-1, \"%s\",0 \r\n", lineNo, lineNo,s);  
}

int main() {
    test_divide_24bit();
    return 0;
}
