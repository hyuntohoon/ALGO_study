package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class prob14499 {
  static class Dice {
    int[][] Diagram;
    int row;
    int col;

    Dice(int row, int col) {
      this.Diagram = new int[4][3];
      this.row = row;
      this.col = col;
    }

    public boolean Roll(int direction) {
      int newRow = this.row + d_row[direction];
      int newCol = this.col + d_col[direction];

      if (IsOutBound(newRow, newCol)) {
        return false;
      }

      switch (direction) {
        case 1:
          RollEast(direction);
          break;
        case 2:
          RollWest(direction);
          break;
        case 3:
          RollNorth(direction);
          break;
        case 4:
          RollSouth(direction);
          break;
        default:
          break;
      }

      this.row = newRow;
      this.col = newCol;

      // 주사위, 맵 초기화
      if (map[this.row][this.col] == 0) {
        map[this.row][this.col] = this.Diagram[3][1];
      } else {
        this.Diagram[3][1] = map[this.row][this.col];
        map[this.row][this.col] = 0;
      }

      return true;
    }

    private void RollSouth(int direction) {
      int tmp = this.Diagram[0][1];
      for (int i = 0; i < 3; i++) {
        this.Diagram[i][1] = this.Diagram[i + 1][1];
      }
      this.Diagram[3][1] = tmp;
    }

    private void RollNorth(int direction) {
      int tmp = this.Diagram[3][1];
      for (int i = 2; i >= 0; i--) {
        this.Diagram[i + 1][1] = this.Diagram[i][1];
      }
      this.Diagram[0][1] = tmp;
    }

    private void RollWest(int direction) {
      int buf = this.Diagram[3][1];
      int tmp = 0;
      for (int i = 2; i >= 0; i--) {
        tmp = this.Diagram[1][i];
        this.Diagram[1][i] = buf;
        buf = tmp;
      }

      this.Diagram[3][1] = buf;
    }

    private void RollEast(int direction) {
      int buf = this.Diagram[3][1];
      int tmp = 0;
      for (int i = 0; i < 3; i++) {
        tmp = this.Diagram[1][i];
        this.Diagram[1][i] = buf;
        buf = tmp;
      }

      this.Diagram[3][1] = buf;
    }

    private boolean IsOutBound(int row, int col) {
      return row < 0 || row >= N || col < 0 || col >= M;
    }

  }

  static StringBuilder result = new StringBuilder();
  static int[][] map;
  static int[] d_row = { 0, 0, 0, -1, 1 };
  static int[] d_col = { 0, 1, -1, 0, 0 };
  static int N, M, K;
  static Dice dice;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());
    map = new int[N][M];

    dice = new Dice(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));

    K = Integer.parseInt(st.nextToken());

    for (int i = 0; i < N; i++) {
      st = new StringTokenizer(br.readLine());
      for (int j = 0; j < M; j++) {
        map[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    st = new StringTokenizer(br.readLine());
    while (K-- > 0) {
      int direction = Integer.parseInt(st.nextToken());

      if (dice.Roll(direction)) {
        result.append(dice.Diagram[1][1]).append("\n");
      }
    }

    System.out.println(result);
  }
}
