#![allow(warnings)]
use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::vec_deque::VecDeque;
use std::io::{self, BufRead};
use std::mem;
//use multiset::HashMultiSet;


#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Faild read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn main() {
    let mut scan = Scanner::default();
    let out = &mut BufWriter::new(stdout());

    for _ in 0..(scan.next::<usize>()) {
        let n = scan.next::<usize>();
        let mut v: Vec<i32> = Vec::new();
        for i in 0..n {
            v.push(scan.next::<i32>());
        }
        let mut v_sorted = v.clone();
        v_sorted.sort();
        v_sorted.reverse();
        for (i, x) in v.iter().enumerate() {
            if v[i] != v_sorted[0] || v_sorted[0] == v_sorted[1] {
                print!("{} ", x - v_sorted[0]);
            } else {
                print!("{} ", x - v_sorted[1]);
            }
        }
        println!();
    }
}
