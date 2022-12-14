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

struct Graph {
    adj: Vec<Vec<usize>>,
}

impl Graph {
    fn new (n: usize) -> Graph {
        Graph {
            adj: vec![Vec::new(); n],
        }
    }
    fn add_edge (&mut self, u: usize, v: usize) {
        self.adj[u].push(v);
        self.adj[v].push(u);
    }
    fn min_distance (&mut self, src: usize) -> Vec<usize> {
        let mut vertices: VecDeque<usize> = VecDeque::from(vec![src]);
        let mut dist: Vec<usize> = vec![0; self.adj.len()];
        let mut visited: Vec<bool> = vec![false; self.adj.len()];
        visited[src] = true;
        while !vertices.is_empty() {
            let gamma = vertices[0];
            vertices.pop_front();
            for i in self.adj[gamma].iter() {
                if !visited[*i] {
                    dist[*i] = dist[gamma] + 1;
                    vertices.push_back(*i);
                    visited[*i] = true;
                }
            }
        }
        return dist;
    }
}

fn main() {
    let mut scan = Scanner::default();
    for _ in 0..scan.next() {
        let n: usize = scan.next();
        let m: usize = scan.next();
        let mut graph: Graph = Graph::new(n);
        for _ in 0..m {
            graph.add_edge(scan.next::<usize>().clone() - 1, scan.next::<usize>().clone() - 1);
        }
        let f: usize = scan.next();
        let mut h: Vec<usize> = Vec::new();
        for _ in 0..f {
            h.push(scan.next::<usize>().clone() - 1);
        }
        let k: usize = scan.next();
        let mut p: HashSet<usize> = HashSet::new();
        for _ in 0..k {
            p.insert(scan.next::<usize>().clone() - 1);
        }
        let mut car: Vec<usize> = Vec::new();
        let mut no_car: Vec<usize> = Vec::new();
        for i in 0..f {
            match p.contains(&i) {
                true => no_car.push(h[i]),
                false => car.push(h[i]),
            }
        }
        let mut prev: Vec<Vec<bool>> = vec![vec![false; no_car.len() + 1]; (1 << no_car.len())];
        prev[0][0] = true;
        let mut cur: Vec<Vec<bool>> = prev.clone();
        let mut distance: Vec<Vec<usize>> = vec![Vec::new(); n];
        for i in 0..no_car.len() {
            distance[no_car[i]] = graph.min_distance(no_car[i]);
        }
        distance[0] = graph.min_distance(0);
        for i in 0..car.len() {
            prev = cur.clone();
            let mut vis: Vec<bool> = vec![false; (1 << no_car.len())];
            vis[0] = true;
            for mask in 1..(1 << no_car.len()) as usize {
                let mut guys: Vec<usize> = Vec::new();
                for j in 0..no_car.len() {
                    if mask & (1 << j) != 0 {
                        guys.push(j);
                    }
                }
                guys.sort_by(|a, b| distance[no_car[*a]].cmp(&distance[no_car[*b]]));
                let x = guys.len() - 1;
                let mut tot = distance[0][no_car[guys[0]]] + distance[no_car[guys[x]]][car[i]];
                for x in 1..guys.len() {
                    tot += distance[no_car[guys[x]]][no_car[guys[x - 1]]];
                }
                vis[mask] = (tot == distance[0][car[i]]);
            }
            for mask in 0..(1 << no_car.len()) {
                for guys in 1..(no_car.len() + 1) {
                    for prev_mask in 0..(1 << no_car.len()) {
                        if prev_mask & mask == prev_mask && vis[mask ^ prev_mask] {
                            cur[mask][guys] |= prev[prev_mask][guys - 1];
                        }
                    }
                }
            }
        }
        let mut ans: i32 = 0;
        for x in 0..1 << no_car.len() {
            for y in 0..(no_car.len() + 1) {
                if cur[x][y] {
                    ans = max(ans, x.count_ones() as i32);
                }
            }
        }
        println!("{:?}", no_car.len() as i32 - ans);
    }
}
