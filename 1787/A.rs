
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
fn main() {
    let mut scan = Scanner::default();
    for _ in 0..scan.next() {
        let n: i32 = scan.next();
        if n % 2 == 0 {
            println!("{} {}", 1, n/2);
        } else {
            println!("-1");
        }
    }
}
