#![allow(warnings)]

use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::{BTreeSet, HashMap, HashSet};
use std::collections::vec_deque::VecDeque;
use std::hash::Hash;
use std::io::{self, BufRead};
use std::mem;
//use multiset::HashMultiSet;


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

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn next (seed: &mut usize) {
    let mut x = seed.clone();
    x = x ^ (x << 13);
    x = x ^ (x >> 7);
    x = x ^ (x << 17);
    *seed = x;
}

fn get_random_permutation (n: i32, seed: &mut usize) -> Vec<i32> {
    next(seed);
    let mut vec: Vec<i32> = vec![0; n as usize];
    for i in 0..n {
        vec[i as usize] = i;
    }
    for i in (1..n).rev() {
        next(seed);
        vec.swap((*seed % (i + 1) as usize) as usize, i as usize);
    }
    return vec;
}

fn solve (vector: Vec<i32>) {
    let n: i32 = vector.len() as i32;
    let mut seed: usize = 1000;
    let mut t = 0;
    loop {
        t += 1;
        let mut q = get_random_permutation(n, &mut seed);
        let mut p = vec![0; n as usize];
        for i in 0..n {
            p[q[i as usize] as usize] = vector[i as usize];
        }
        let mut okay: bool = true;
        for i in 0..n {
            if q[i as usize] == i || p[i as usize] == i {
                okay = false;
            }
        }
        if okay {
            for i in 0..n {
                p[i as usize] += 1;
                q[i as usize] += 1;
            }
            println!("Possible");
            p.iter().for_each(|val| print!("{} ", val));
            println!();
            q.iter().for_each(|val| print!("{} ", val));
            println!();
            return;
        }
    }
}

fn main() {
    let mut scan = Scanner::default();
    let out = &mut BufWriter::new(stdout());
    for _ in 0..scan.next::<i32>() {
        let n = scan.next::<i32>();
        let mut vec: Vec<i32> = vec![];
        let mut vec_inv: Vec<i32> = vec![0; n as usize];
        for i in 0..n {
            vec.push(scan.next::<i32>());
        }
        if vec == vec![1] || vec == vec![2, 1] || vec == vec![1, 3, 2] || vec == vec![2, 1, 3] || vec == vec![3, 2, 1] {
            println!("Impossible");
            continue;
        }
        for i in 0..n {
            vec_inv[vec[i as usize] as usize - 1] = i ;
        }
        solve(vec_inv.clone())
    }
}
