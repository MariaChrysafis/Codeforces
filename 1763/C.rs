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
    for _ in 0..scan.next() {
        let n: i64 = scan.next();
        let mut arr: Vec<i64> = Vec::new();
        for i in 0..n {
            arr.push(scan.next::<i64>());
        }
        match n {
            1 => println!("{}", arr[0]),
            2 => println!("{}", max(arr[0] + arr[1], 2 * (arr[0] - arr[1]).abs())),
            3 => {
                if arr[0] > max(arr[1], arr[2]) {
                    println!("{}", n * arr[0]);
                } else if arr[2] > max(arr[1], arr[0]) {
                    println!("{}", n * arr[2]);
                } else {
                    let mut mx: i64 = 0;
                    mx = max(mx, (arr[0] - arr[2]).abs() * 3);
                    mx = max(mx, arr[0] + arr[1] + arr[2]);
                    mx = max(mx, 3 * (arr[0] - arr[1]).abs());
                    mx = max(mx, 3 * (arr[1] - arr[2]).abs());
                    mx = max(mx, 3 * max(arr[0], arr[2]));
                    println!("{}", mx);
                }
            }
            _ => {
                println!("{}", n * *arr.iter().max().unwrap());
            }
        }
    }
}
