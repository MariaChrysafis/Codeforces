import java.util.Comparator;
import java.util.List;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.StringTokenizer;
import java.io.*;
import java.util.*;
public class Main {
    static ArrayList<Integer>[] adj;
    static ArrayList<Integer>[] adj_rev;
    static long INF = (long) 1e15;
    static int n;
    public static void add_edge(int u, int v) {
        adj[u].add(v);
        adj_rev[v].add(u);
    }
    public static class SpecialGraph {

        public long[] distance1(int src) {
            long[] dist = new long[n * 18];
            for (int i = 0; i < n * 18; i++) {
                dist[i] = INF;
            }
            dist[src] = 0L;
            PriorityQueue<Pair<Integer, Long>> pq = new PriorityQueue<Pair<Integer, Long>>((x,y) -> {
                return Long.compare(x.y, y.y);
            });
            pq.add(new Pair(src, dist[src]));
            while (!pq.isEmpty()) {
                Pair<Integer, Long> p = pq.poll();
                int node = p.x;
                long d = p.y;
                if ((node / n) % 2 == 0) {
                    for (int nxt : adj[node % n]) {
                        int nxt_node = nxt + node / n * n;
                        if (dist[nxt_node] > d + 1) {
                            dist[nxt_node] = d + 1;
                            pq.add(new Pair<>(nxt_node, d + 1));
                        }
                    }
                } else {
                    for (int nxt : adj_rev[node % n]) {
                        int nxt_node = nxt + node / n * n;
                        if (dist[nxt_node] > d + 1) {
                            dist[nxt_node] = d + 1;
                            pq.add(new Pair<>(nxt_node, d + 1));
                        }
                    }
                }
                int weight = (1 << (node / n));
                if (node + n < 18 * n && dist[node + n] > d + weight) {
                    dist[node + n] = d + weight;
                    pq.add(new Pair<>(node + n, d + weight));
                }
            }
            return dist;
        }

        public long[] distance2(int src) {
            long[] dist = new long[2 * n];
            for (int i = 0; i < 2 * n; i++) {
                dist[i] = INF;
            }
            dist[src] = 0L;
            PriorityQueue<Pair<Integer, Long>> pq = new PriorityQueue<Pair<Integer, Long>>((x,y) -> {
                return Long.compare(x.y, y.y);
            });
            pq.add(new Pair(src, dist[src]));
            while (!pq.isEmpty()) {
                Pair<Integer, Long> p = pq.poll();
                int node = p.x;
                long d = p.y;
                if ((node / n) % 2 == 0) {
                    for (int nxt : adj[node % n]) {
                        int nxt_node = nxt + node / n * n;
                        if (dist[nxt_node] > d + 1) {
                            dist[nxt_node] = d + 1;
                            pq.add(new Pair(nxt_node, d + 1));
                        }
                    }
                } else {
                    for (int nxt : adj_rev[node % n]) {
                        int nxt_node = nxt + node / n * n;
                        if (dist[nxt_node] > d + 1) {
                            dist[nxt_node] = d + 1;
                            pq.add(new Pair(nxt_node, d + 1));
                        }
                    }
                }
                int nxt_node = node;
                if (nxt_node >= n) nxt_node -= n;
                else nxt_node += n;
                if (dist[nxt_node] > dist[node] + (long) 1e9) {
                    dist[nxt_node] = dist[node] + (long) 1e9;
                    pq.add(new Pair(nxt_node, dist[nxt_node]));
                }
            }
            return dist;
        }

        SpecialGraph(int n) {
        }
    }

    public static long MOD = 998244353;

    public static long binPow(long x, long y) {
        long ans = 1;
        long res = x;
        while (y > 0) {
            if (y % 2 == 1) {
                ans *= res;
                ans %= MOD;
            }
            res *= res;
            res %= MOD;
            y /= 2;
        }
        return ans;
    }

    public static void main(String[] args) throws Exception {
        FastIO scan = new FastIO();
        n = scan.nextInt();
        int m = scan.nextInt();
        Pair<Integer, Integer>[] vec = new Pair[m];
        SpecialGraph specialGraph = new SpecialGraph(n);
        int GAMMA = 18;
        adj = new ArrayList[n];
        adj_rev = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
            adj_rev[i] = new ArrayList<>();
        }
        Arrays.fill(vec, new Pair<>(0, 0));
        for (int i = 0; i < m; i++) {
            int u = scan.nextInt() - 1;
            int v = scan.nextInt() - 1;
            add_edge(u, v);
            vec[i] = new Pair<>(u, v);
        }
        long[] dist = specialGraph.distance1(0);
        long myMin = INF;
        for (int i = 0; i < GAMMA; i++) {
            myMin = Math.min(myMin, dist[n * i + n - 1]);
        }
        if (myMin != INF) {
            System.out.println(myMin);
            return;
        }
        dist = specialGraph.distance2(0);
        myMin = INF;
        for (int i = 0; i < 2; i++) {
            myMin = Math.min(myMin, dist[n * i + n - 1]);
        }
        long act = myMin / (long) 1e9;
        long dum = myMin % (long) 1e9;
        System.out.println((binPow(2, act) - 1 + dum) % MOD);

    }

    public static class Pair<T1, T2> {
        T1 x;
        T2 y;

        public Pair(T1 x, T2 y) {
            this.x = x;
            this.y = y;
        }
    }

    static class FastIO extends PrintWriter {
        private InputStream stream;
        private byte[] buf = new byte[1 << 16];
        private int curChar;
        private int numChars;

        // standard input
        public FastIO() { this(System.in, System.out); }

        public FastIO(InputStream i, OutputStream o) {
            super(o);
            stream = i;
        }

        // file input
        public FastIO(String i, String o) throws IOException {
            super(new FileWriter(o));
            stream = new FileInputStream(i);
        }

        // throws InputMismatchException() if previously detected end of file
        private int nextByte() {
            if (numChars == -1) {
                throw new InputMismatchException();
            }
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars == -1) {
                    return -1;  // end of file
                }
            }
            return buf[curChar++];
        }

        // to read in entire lines, replace c <= ' '
        // with a function that checks whether c is a line break
        public String next() {
            int c;
            do {
                c = nextByte();
            } while (c <= ' ');

            StringBuilder res = new StringBuilder();
            do {
                res.appendCodePoint(c);
                c = nextByte();
            } while (c > ' ');
            return res.toString();
        }

        public int nextInt() {  // nextLong() would be implemented similarly
            int c;
            do {
                c = nextByte();
            } while (c <= ' ');

            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = nextByte();
            }

            int res = 0;
            do {
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res = 10 * res + c - '0';
                c = nextByte();
            } while (c > ' ');
            return res * sgn;
        }

        public double nextDouble() { return Double.parseDouble(next()); }
    }
}
