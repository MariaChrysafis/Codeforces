package main

import (
	"fmt"
)

func main() {
	var t int
	fmt.Scan(&t)
	for tc := 0; tc < t; tc++ {
		var s string
		var n int
		fmt.Scan(&n)
		fmt.Scan(&s)
		winner := 0
		for x := 1; x <= len(s); x++ {
			for y := 1; y <= len(s); y++ {
				counter := [2]int{0, 0}
				winners := [2]int{0, 0}
				for ind, c := range s {
					cur := int(c) - int('A')
					counter[cur] += 1
					if counter[cur] == x {
						winners[cur] += 1
						if winners[cur] == y && ind == len(s)-1 {
							winner |= (1 << cur)
						}
					}
				}
			}
		}
		if winner == 3 || winner == 0 {
			fmt.Println("?")
		} else if winner == 1 {
			fmt.Println("A")
		} else {
			fmt.Println("B")
		}
	}
}
