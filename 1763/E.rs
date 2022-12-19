#![allow(warnings)]

use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::{BTreeSet, HashMap, HashSet};
use std::collections::vec_deque::VecDeque;
use std::fs::soft_link;
use std::hash::Hash;
use std::io::{self, BufRead};
use std::mem;
use std::process::exit;
use std::ptr::hash;

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

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
    let n: i64 = scan.next();
    if n == 0 {
        println!("0 0");
        exit(0);
    } else if n == 1 {
        println!("2 0");
        exit(0);
    }
    let mut mu: Vec<i64> = vec![0];
    let mut x: Vec<i64> = vec![];
    for j in 1..(n + 1) {
        for i in 2..(n + 1) {
            let ic2 = (i * (i - 1))/2;
            if ic2 <= j {
                x.push(mu[(j - ic2) as usize] + i);
            } else {
                break;
            }
        }
        mu.push(*(x.iter().min().unwrap()));
        x.clear();
    }
    let gamma = *(mu.last().unwrap());
    println!("{} {}", gamma, gamma * (gamma - 1)/2 - n);

}
