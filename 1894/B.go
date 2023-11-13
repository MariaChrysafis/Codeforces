package main

import (
	"fmt"
)

func solver(arr []int) []int {
	oc := make(map[int]int)
	ans := make([]int, len(arr))
	for i := 0; i < len(ans); i++ {
		ans[i] = 2
	}
	for _, x := range arr {
		oc[x] += 1
	}
	cntr := 0
	oc2 := 0
	for key, value := range oc {
		if value >= 2 {
			value = 0
			oc2 += 1
			for i := 0; i < len(arr); i++ {
				if arr[i] == key {
					ans[i] = cntr%3 + 1
					cntr++
					value += 1
					if value == 2 {
						break
					}
				}
			}
			if oc2 == 2 {
				break
			}
			cntr -= 1
		}
	}
	if oc2 >= 2 {
		return ans
	}
	return make([]int, 0)
}

func main() {
	var t int
	fmt.Scan(&t)
	for tc := 0; tc < t; tc++ {
		var n int
		fmt.Scan(&n)
		arr := make([]int, n)
		for i := 0; i < n; i++ {
			fmt.Scan(&arr[i])
		}
		ans := solver(arr)
		if len(ans) == 0 {
			fmt.Println(-1)
			continue
		}
		for i := 0; i < len(ans); i++ {
			fmt.Print(ans[i], " ")
		}
		fmt.Println()
	}
}
