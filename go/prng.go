// package main

// import (
//     "fmt"
//     "math/rand"
//     "time"
// )

// // Function to calculate the greatest common divisor using the Euclidean algorithm
// func gcd(a, b uint32) uint32 {
//     for b != 0 {
//         a, b = b, a%b
//     }
//     return a
// }

// // Function to check if a number is co-prime with 2^24
// func isCoprimeWithModulus(increment uint32) bool {
//     const modulus uint32 = 1 << 24
//     return gcd(increment, modulus) == 1
// }

// func main() {
//     rand.Seed(time.Now().UnixNano())
//     const modulus uint32 = 1 << 24

//     for {
//         increment := uint32(rand.Int31n(int32(modulus)))
//         if isCoprimeWithModulus(increment) {
//             fmt.Printf("Found a good increment: %d\n", increment)
//             break
//         }
//     }
// }


// ent: 556987
// mats@Matss-MacBook-Pro go % go run prng.go
// Found a good increment: 11329711
// mats@Matss-MacBook-Pro go % go run prng.go
// Found a good increment: 13400971
// mats@Matss-MacBook-Pro go % go run prng.go
// Found a good increment: 14548843
// mats@Matss-MacBook-Pro go % go run prng.go
// Found a good increment: 11301903
// mats@Matss-MacBook-Pro go % go run prng.go
// Found a good increment: 2202643


package main

import (
    "fmt"
)

// Function to calculate the greatest common divisor using the Euclidean algorithm
func gcd(a, b uint32) uint32 {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

// Function to check if a number is co-prime with 2^24
func isCoprimeWithModulus(increment uint32) bool {
    const modulus uint32 = 1 << 24
    return gcd(increment, modulus) == 1
}

// Additive Congruential Generator structure
type ACG struct {
    state     uint32
    increment uint32
}

// Function to create a new ACG instance
func NewACG(seed uint32, increment uint32) *ACG {
    return &ACG{state: seed, increment: increment}
}

// Function to generate the next random number
func (a *ACG) NextRandom() uint32 {
    a.state = (a.state + a.increment) & 0xFFFFFF // Ensure the state is within 24 bits
    return a.state
}

// Function to generate a sequence of random numbers
func GenerateSequence(seed uint32, increment uint32, length int) []uint32 {
    acg := NewACG(seed, increment)
    sequence := make([]uint32, length)
    for i := 0; i < length; i++ {
        sequence[i] = acg.NextRandom()
    }
    return sequence
}

func main() {
    seed := uint32(12345678)
    increment := uint32(11301903)

    // Check if the chosen increment is valid
    if !isCoprimeWithModulus(increment) {
        fmt.Println("The chosen increment is not co-prime with the modulus. Please choose another increment.")
        return
    }

    length := 100
    randomSequence := GenerateSequence(seed, increment, length)

    fmt.Println("Random sequence:")
    for _, num := range randomSequence {
        fmt.Printf("%024b\n", num)
    }
}

