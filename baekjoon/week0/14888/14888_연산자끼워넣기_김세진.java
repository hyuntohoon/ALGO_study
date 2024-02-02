package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob14888_2 {
  static StringBuilder result = new StringBuilder();
  static int N;
  static int[] operandArr;
  static List<Character> operatorList = new ArrayList<>();
  static boolean[] isSelected;
  static int min = Integer.MAX_VALUE;
  static int max = Integer.MIN_VALUE;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    N = Integer.parseInt(br.readLine());
    operandArr = new int[N];
    isSelected = new boolean[N - 1];

    StringTokenizer st = new StringTokenizer(br.readLine());
    for (int i = 0; i < N; i++) {
      operandArr[i] = Integer.parseInt(st.nextToken());
    }

    st = new StringTokenizer(br.readLine());
    for (int i = Integer.parseInt(st.nextToken()); i > 0; i--) {
      operatorList.add('+');
    }
    for (int i = Integer.parseInt(st.nextToken()); i > 0; i--) {
      operatorList.add('-');
    }
    for (int i = Integer.parseInt(st.nextToken()); i > 0; i--) {
      operatorList.add('*');
    }
    for (int i = Integer.parseInt(st.nextToken()); i > 0; i--) {
      operatorList.add('/');
    }

    BackTracking(operandArr[0], 1);

    System.out.println(max + "\n" + min);
  }

  private static void BackTracking(int prev, int depth) {
    if (depth == N) {
      min = Math.min(min, prev);
      max = Math.max(max, prev);
      return;
    }

    for (int i = 0; i < N - 1; i++) {
      if (isSelected[i]) {
        continue;
      }
      char operator = operatorList.get(i);
      isSelected[i] = true;
      BackTracking(Cal(prev, operandArr[depth], operator), depth + 1);
      isSelected[i] = false;
    }
  }

  private static int Cal(int op1, int op2, char operator) {
    switch (operator) {
      case '+':
        return op1 + op2;
      case '-':
        return op1 - op2;
      case '*':
        return op1 * op2;
      case '/':
        if (op1 < 0 || op2 < 0) {
          return -1 * (Math.abs(op1) / Math.abs(op2));
        } else {
          return op1 / op2;
        }
    }
    return 0;
  }
}
