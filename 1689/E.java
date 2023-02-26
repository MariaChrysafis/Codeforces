import java.util.ArrayList;
import java.io.*;
import java.util.*;
public class Main {
    public static class Graph {
        ArrayList<Integer> adj[];
        boolean vis[];
        void dfs (int x) {
            vis[x] = true;
            for (int i: adj[x]) {
                if (!vis[i]) {
                    dfs(i);
                }
            }
        }
        void add_edge (int u, int v) {
            adj[u].add(v);
            adj[v].add(u);
        }
        public Graph(int n) {
            adj = new ArrayList[n];
            vis = new boolean[n];
            for (int i = 0; i < n; i++) {
                vis[i] = false;
            }
            for (int i = 0; i < n; i++) {
                adj[i] = new ArrayList<>();
            }
        }
    }
    public static boolean okay (int[] a) {
        int bitwise_or = 0;
        for (int i: a) {
            bitwise_or |= i;
        }
        Graph gr = new Graph(32);
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < 32; j++) {
                if ((a[i] & (1 << j)) != 0) {
                    for (int k = 0; k < 32; k++) {
                        if ((a[i] & (1 << k)) != 0) {
                            gr.add_edge(j, k);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 32; i++) {
            if ((bitwise_or & (1 << i)) != 0) {
                gr.dfs(i);
                break;
            }
        }
        for (int i = 0; i < 32; i++) {
            if ((bitwise_or & (1 << i)) != 0 && !gr.vis[i]) {
                return false;
            }
        }
        return true;
    }
    public static void print (int[] a) {
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }
    public static void solve (FastIO scan) {
        int n = scan.nextInt();
        int []a = new int[n];
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            a[i] = scan.nextInt();
            if (a[i] == 0) {
                a[i] = 1;
                cnt++;
            }
        }
        if (okay(a)) {
            System.out.println(cnt);
            print(a);
            return;
        }
        for (int i = 0; i < n; i++) {
            a[i] += 1;
            if (okay(a)) {
                System.out.println(cnt + 1);
                print(a);
                return;
            }
            if (a[i] >= 3) {
                a[i] -= 2;
                if (okay(a)) {
                    System.out.println(cnt + 1);
                    print(a);
                    return;
                }
                a[i] += 2;
            }
            a[i] -= 1;
        }
        ArrayList<Integer> arr = new ArrayList<>();
        ArrayList<Integer> lsb = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 32; j++) {
                if ((a[i] & (1 << j)) != 0) {
                    lsb.add(j);
                    break;
                }
            }
            arr.add(i);
        }
        final ArrayList<Integer> lsb_final = lsb;
        Comparator<Integer> cmp = (x, y) -> {
            if (lsb_final.get(x).equals(lsb_final.get(y))) {
                return Integer.compare(x, y);
            }
            return Integer.compare(lsb_final.get(y), lsb_final.get(x));
        };
        arr.sort(cmp);
        a[arr.get(0)] -= 1;
        a[arr.get(1)] += 1;
        System.out.println(cnt + 2);
        print(a);
    }
    public static void main(String[] args) throws Exception {
        FastIO scan = new FastIO();
        int q = scan.nextInt();
        for (int i = 0; i < q; i++) {
            solve(scan);
        }
        scan.close();
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
