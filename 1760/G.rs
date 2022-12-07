#![allow(warnings)]
use std::io::{BufWriter, stdin, stdout, Write};
use std::vec;
use std::cmp::max;
use std::cmp::min;
use std::collections::{HashMap, HashSet};
use std::collections::vec_deque::VecDeque;
use std::hash::Hash;
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


fn rec (adj: &Vec<Vec<(usize, i32)>>, in_subtree: &mut Vec<bool>, cur: usize, prev: usize, node1: usize, dist_xor: &mut Vec<i32>) {
    for (i, next) in adj[cur as usize].iter().enumerate() {
        if next.0 != prev {
            dist_xor[next.0] = dist_xor[cur] ^ next.1;
            in_subtree[next.0] = in_subtree[cur];
            if cur == node1 {
                in_subtree[next.0] = true;
            }
            rec(adj, in_subtree, next.0, cur, node1, dist_xor);
        }
    }
}

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>())
}

fn main() {
    let mut scan = Scanner::default();
    let out = &mut BufWriter::new(stdout());

    for _ in 0..(scan.next::<usize>()) {
        let n = scan.next();
        let node1 = scan.next::<usize>() - 1;
        let node2 = scan.next::<usize>() - 1;
        let mut adj: Vec<Vec<(usize, i32)>> = vec![Vec::new(); n];
        let mut dist_xor: Vec<i32> = vec![0; n];
        let mut in_subtree: Vec<bool> = vec![false; n];
        for i in 0..n - 1 {
            let a = scan.next::<usize>() - 1;
            let b = scan.next::<usize>() - 1;
            let w = scan.next::<i32>();
            adj[a].push((b, w));
            adj[b].push((a, w));
        }
        rec(& adj, &mut in_subtree, node1, node1, node2, &mut dist_xor);
        let mut okay: bool = false;
        let mut hashset: HashSet<i32> = HashSet::new();
        for x in 0..n {
            if x != node2 && !in_subtree[x] {
                hashset.insert(dist_xor[x]);
            }
        }
        for x in 0..n {
            okay |= (x != node2 && hashset.contains(&(dist_xor[x] ^ dist_xor[node2])));
        }
        println!("{}", match okay {true => "YES", false => "NO"} );
    }
}
