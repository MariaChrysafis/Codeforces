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

fn gcd (x: i64, y: i64) -> i64 {
    if x == 0 || y == 0 {
        return max(x, y);
    }
    return gcd(max(x, y) % min(x, y), min(x, y));
}

fn f (factors: &Vec<Vec<i64>>, rp: &Vec<i64>, n: i64, modulo: i64) -> i64 { //sum_{a, b, c; a + b + c = n; gcd(a, b, c) = 1}
    let mut ans = 0;
    for c in 1..n {
        for g in factors[n as usize - c as usize].iter() {
            if gcd(*g, c) == 1 && (n - c)/g != 1 {
                ans += ((rp[(n as usize - c as usize) / (*g as usize)] * c) % modulo * g) % modulo;
                ans %= modulo;
            }
        }
    }
    return ans;
}

fn main() {
    let mut scan = Scanner::default();
    let n: usize = scan.next();
    let modulo: i64 = 1e9 as i64 + 7;
    let mut ans = 0;
    let mut factors: Vec<Vec<i64>> = vec![vec![1 as i64]; (n + 1) as usize];
    let mut lpf: Vec<i64> = vec![0; (n + 1) as usize];
    for i in 2..(n + 1) {
        for j in (i..(n + 1)).step_by(i) {
            factors[j].push(i as i64);
            if lpf[j] == 0 {
                lpf[j] = i as i64;
            }
        }
    }
    let mut mu = vec![0; (n + 1) as usize];
    let mut rp = vec![0; (n + 1) as usize];
    mu[1] = 1;
    for i in 2..(n + 1) {
        if lpf[i/lpf[i] as usize] == lpf[i] {
            mu[i] = 0;
        } else {
            mu[i] = -mu[i/lpf[i] as usize];
        }
        for j in factors[i].iter() {
            rp[i] += (i as i64) / j * mu[*j as usize];
        }
    }
    for i in factors[n].iter() {
        ans += (f(&factors, &rp, *i, modulo) * ((n as i64)/i)) % modulo;
        ans %= modulo;
    }
    println!("{}", ans);
}
