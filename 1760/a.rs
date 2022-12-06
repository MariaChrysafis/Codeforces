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
        let b = scan.next::<usize>();
        let c = scan.next::<usize>();
        if b >= min(a, c) && b <= max(a, c) {
            println!("{}", b);
            continue;
        }
        if c >= min(b, a) && c <= max(b, a) {
            println!("{}", c);
            continue;
        }
        println!("{}", a);
    }
}
