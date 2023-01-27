
#![allow(warnings)]

use std::io::{BufWriter, stdin, stdout, Write};
use std::{usize, vec};
use std::cmp::max;
use std::cmp::min;
use std::collections::{BTreeSet, HashMap, HashSet};
use std::collections::vec_deque::VecDeque;
use std::fs::soft_link;
use std::hash::Hash;
use std::io::{self, BufRead};
use std::mem;
use std::process::exit;
#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
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
fn gcd (x: i64, y: i64) -> i64 {
    if x == 0 || y == 0 {
        return max(x, y);
    }
    return gcd(max(x, y) % min(x, y), min(x, y));
}
fn main() {
    let mut scan = Scanner::default();
    for _ in 0..scan.next() {
        let mut sum: i64 = 0;
        let n = scan.next();
        let mut arr: Vec<i64> = vec![0; n];
        for i in 0..n {
            arr[i] = scan.next();
            sum += arr[i];
        }
        let mut pref: i64 = 0;
        let mut myMax: i64 = 1;
        for i in 0..n - 1 {
            pref += arr[i];
            myMax = max(myMax, gcd(pref, sum))
        }
        println!("{}", myMax);
    }
}
