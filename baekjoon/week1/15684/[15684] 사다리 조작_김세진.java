package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class prob15684 {
  static int N, M, H;
  static int[][] map;
  static int ans = Integer.MAX_VALUE;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());
    H = Integer.parseInt(st.nextToken());

    map = new int[H + 2][N + 1];
    for (int i = 0; i < M; i++) {
      st = new StringTokenizer(br.readLine());
      int a = Integer.parseInt(st.nextToken());
      int b = Integer.parseInt(st.nextToken());

      map[a][b] = 1;
      map[a][b + 1] = -1;
    }

    for (int i = 0; i < 4; i++) {
      Combi(0, i);
      if (ans != Integer.MAX_VALUE) {
        break;
      }
    }

    System.out.println(ans == Integer.MAX_VALUE ? -1 : ans);
  }

  private static void Combi(int depth, int target) {
    if (depth == target) {
      if (checkLadder()) {
        ans = Math.min(ans, depth);
      }
      return;
    }

    for (int i = 1; i <= H; i++) {
      for (int j = 1; j <= N - 1; j++) {
        if (PossiblePutLadder(i, j)) {
          map[i][j] = 1;
          map[i][j + 1] = -1;
          Combi(depth + 1, target);
          map[i][j] = 0;
          map[i][j + 1] = 0;
        }
      }
    }
  }

  private static boolean checkLadder() {
    for (int i = 1; i <= N; i++) {
      if (DestinationFrom(i) == i) {
        continue;
      } else {
        return false;
      }
    }
    return true;
  }

  private static int DestinationFrom(int start) {
    int posRow = 0;
    int posCol = start;

    while (posRow < H + 1) {
      if(map[posRow][posCol] == 1){
        posCol++;
      } else if(map[posRow][posCol] == -1){
        posCol--;
      }
      posRow++;
    }

    return posCol;
  }

  private static boolean PossiblePutLadder(int row, int col) {
    return map[row][col] == 0 && map[row][col + 1] == 0;
  }
}
