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
    seed := uint32(1)
    lfsr := NewLFSR(seed)
	first:=lfsr.NextRandom()

	for i:=0; i<1000; i++ {
		num := lfsr.NextRandom()
		fmt.Printf("%06X\r\n", num)
		if num == first {
			fmt.Printf("Cycle detected after %d iterations\n", i)
			break
		}
	}
}

