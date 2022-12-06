#![allow(warnings)]
use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::vec_deque::VecDeque;
use std::io::{self, BufRead};
use std::mem;

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
        let a = scan.next::<usize>();
        let s = scan.next::<String>();
        let mut ans: i32 = 0;
        for c in s.chars() {
            ans = max(ans, c as i32 - 'a' as i32);
        }
        println!("{}", ans + 1);
    }
}
