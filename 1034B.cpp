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
    let n = scan.next::<i64>();
    let m = scan.next::<i64>();
    if min(n, m) == 1 {
        println!("{}", n * m - min(6 - (n * m) % 6, (n * m) % 6));
    } else if min(n, m) == 2 && max(n, m) == 2 {
        println!("{}", 0);
    } else if min(n, m) == 2 && max(n, m) == 3 {
       println!("{}", n * m - 2);
    }  else if min(n, m) == 2 && max(n, m) == 7 {
        println!("{}", n * m - 2);
    } else {
        println!("{}", n * m - (n * m) % 2);
    } 
}
