package main

import (
    "fmt"
)

type LFSR struct {
    state uint32
}

func NewLFSR(seed uint32) *LFSR {
    return &LFSR{state: seed & 0xFFFFFF} // Ensure the seed is 24-bit
}

func (l *LFSR) NextRandom() int32 {
    // Compute the feedback bit using the specified tap positions
	f23:=(l.state >> 23)&1
    f22:=(l.state >> 22)&1
    f21:=(l.state >> 21)&1
    f16:=(l.state >> 16)&1
	feedback := ((l.state >> 23) ^ (l.state >> 22) ^ (l.state >> 21) ^ (l.state >> 16)) & 1
	f:=f23^f22^f21^f16
	_=f
	//


	// fmt.Printf("feedback: %d/%d  f23,f22,f21,f16: %d,%d,%d,%d\n",feedback,f, f23,f22,f21,f16)

    // Shift the state left by 1 bit and insert the feedback bit at the least significant bit position
    l.state = ((l.state << 1) | feedback) & 0xFFFFFF // Ensure the state is within 24 bits

    // // Adjust the state to stay within the range of 24-bit signed integers
    // if l.state > 0x7FFFFF {
    //     return int32(l.state) - 0x1000000
    // }
	if l.state > 0xFFFFFF {
		l.state = l.state - 0x1000000
	}

		return int32(l.state)
}

func main() {
    seed1 := uint32(192831)
    seed2 := uint32(123123)
    lfsr1 := NewLFSR(seed1)
    lfsr2 := NewLFSR(seed2)

	for i:=0; i<100000; i++ {
		num1 := lfsr1.NextRandom()
		num2 := lfsr2.NextRandom()
		num := num1 | num2
		num=(num>>18)&15;
		if num<10 {
		fmt.Printf("%d ", num)
		}
	}
}

