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
    let out = &mut BufWriter::new(stdout());
    for _ in 0..scan.next::<i32>() {
        let n: usize = scan.next();
        let mut s1: Vec<char> = scan.next::<String>().chars().collect();
        let mut s2: Vec<char> = scan.next::<String>().chars().collect();
        let mut oc = vec![0; 300];
        for i in 0..s1.len() {
            oc[s1[i] as usize] ^= 1;
            oc[s2[i] as usize] ^= 1;
        }
        let mut fine: bool = (oc.iter().sum::<i32>() == 0);
        let mut oc2d = vec![vec![0; 26]; 26];
        for i in 0..s1.len() {
            let mut c1 = s1[i] as usize - 'a' as usize;
            let mut c2 = s2[s2.len() - i - 1] as usize - 'a' as usize;
            oc2d[min(c1, c2)][max(c1, c2)] ^= 1;
        }
        let mut cntr = 0;
        for i in 0..26 {
            cntr += oc2d[i].iter().sum::<i32>();
        }
        fine &= (cntr < 2);
        println!("{}", match fine {true => "YES", false => "NO"});
    }
}
