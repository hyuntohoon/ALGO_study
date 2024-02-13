package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob21610 {
  static int N, M;
  static int[][] map;
  static int[][] cloudMap;
  static List<Cdnt> cloudList = new ArrayList<>();
  static int[] d_row = { 0, -1, -1, -1, 0, 1, 1, 1 };
  static int[] d_col = { -1, -1, 0, 1, 1, 1, 0, -1 };

  static class Cdnt {
    int row;
    int col;

    Cdnt(int row, int col) {
      this.row = row;
      this.col = col;
    }
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());

    map = new int[N + 1][N + 1];
    cloudMap = new int[N + 1][N + 1];
    for (int i = 1; i <= N; i++) {
      st = new StringTokenizer(br.readLine());
      for (int j = 1; j <= N; j++) {
        map[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    cloudList.add(new Cdnt(N, 1));
    cloudList.add(new Cdnt(N, 2));
    cloudList.add(new Cdnt(N - 1, 1));
    cloudList.add(new Cdnt(N - 1, 2));

    while (M-- > 0) {
      st = new StringTokenizer(br.readLine());
      int d = Integer.parseInt(st.nextToken());
      int s = Integer.parseInt(st.nextToken());

      MoveClouds(--d, s);
      Rain();
      RemoveClouds();
      CopyWater();
      GenerateClouds();
    }

    System.out.println(SumOfWater());
  }

  private static void MoveClouds(int d, int s) {
    for (Cdnt cloud : cloudList) {
      s %= N;
      cloud.row += (d_row[d] * s + N);
      cloud.col += (d_col[d] * s + N);

      cloud.row = cloud.row % N == 0 ? N : cloud.row % N;
      cloud.col = cloud.col % N == 0 ? N : cloud.col % N;
    }
  }

  private static void Rain() {
    for (Cdnt cloud : cloudList) {
      map[cloud.row][cloud.col]++;
    }
  }

  private static void RemoveClouds() {
    for (Cdnt cloud : cloudList) {
      cloudMap[cloud.row][cloud.col] = 1;
    }
  }

  private static void CopyWater() {
    for (Cdnt cloud : cloudList) {
      int cnt = 0;
      for (int i = 1; i < 8; i += 2) {
        int newRow = cloud.row + d_row[i];
        int newCol = cloud.col + d_col[i];

        if (IsOutBound(newRow, newCol)) {
          continue;
        }

        if (map[newRow][newCol] > 0) {
          cnt++;
        }
      }

      map[cloud.row][cloud.col] += cnt;
    }

    cloudList.clear();
  }

  private static boolean IsOutBound(int newRow, int newCol) {
    return newRow < 1 || newRow > N || newCol < 1 || newCol > N;
  }

  private static void GenerateClouds() {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (cloudMap[i][j] == 1) {
          cloudMap[i][j] = 0;
          continue;
        }

        if (map[i][j] < 2) {
          continue;
        }

        map[i][j] -= 2;
        cloudList.add(new Cdnt(i, j));
      }
    }
  }

  private static int SumOfWater() {
    int ret = 0;
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        ret += map[i][j];
      }
    }

    return ret;
  }
}
