package uvas;

import java.util.Scanner;

public class Problem {

    private static final void out(Object o) { System.out.println(o); }
    private static final Input in = new Input();

    private static void solve() {

    } 

    private static void solve(int n) {

    } 

    public static void main(String[] args) {
        in.until(0);
    }

    
    private static class Input {
        private static final Scanner in = new Scanner(System.in);

        protected void numCases() {
            int numCasos = in.nextInt();
    
            for (int i = 0; i < numCasos; i++)
                solve();
        }
    
        protected void until(int ending) {
            int nextCase = in.nextInt();
            while (nextCase != ending) {
                solve(nextCase);
                nextCase = in.nextInt();
            }
        }

        protected void untilEOF() {
            while (in.hasNext()) {
                solve();
            }
        }

        protected BigInteger[] readInts(int n) {
            BigInteger[] numbers = new BigInteger[n];
            for (int i = 0; i < n; i++) {
                numbers[i] = in.nextBigInteger();
            }
            return numbers;
        }

        protected String[] read(int n) {
            String[] numbers = new String[n];
            for (int i = 0; i < n; i++) {
                numbers[i] = in.next();
            }
            return numbers;
        }

    }
}
