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
        let n = scan.next();
        let mut v: Vec<i64> = Vec::new();
        for i in 0..n {
            v.push(scan.next());
        }
        let mut pref: i64 = 0;
        let mut suf: i64 = v.iter().sum();
        let mut inversions: i64 = 0;
        for (i, x) in v.iter().enumerate() {
            suf -= x;
            if *x == 0 {
                inversions += pref;
            } 
            pref += x;
        }
        suf = v.iter().sum();
        pref = 0;
        let mut ans: i64 = inversions;
        for (i, x) in v.iter().enumerate() {
            suf -= x;
            if *x == 0 as i64 {
                ans = max(ans, inversions - pref + n as i64 - i as i64 - 1 - suf);
            } else {
                ans = max(ans, inversions - (n as i64 - i as i64 - 1 - suf) + pref);
            }
            pref += x;
        }
        println!("{} ", ans);
    }
}

