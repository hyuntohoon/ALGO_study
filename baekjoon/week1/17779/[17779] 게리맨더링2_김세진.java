package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class prob17779 {
  static int N;
  static int[][] PeopleMap;
  static int[][] SectionMap;
  static int min = Integer.MAX_VALUE;
  static int[] d_row = { 1, 1, -1, -1 };
  static int[] d_col = { 1, -1, -1, 1 };

  public static void main(String[] args) throws NumberFormatException, IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    N = Integer.parseInt(br.readLine());
    PeopleMap = new int[N + 1][N + 1];
    for (int i = 1; i <= N; i++) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      for (int j = 1; j <= N; j++) {
        PeopleMap[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    // 가능한 d1, d2, x, y에 대해서 완전 탐색
    for (int d1 = 1; d1 <= N - 2; d1++) {
      for (int d2 = 1; d1 + d2 < N; d2++) {
        for (int x = 1; x <= N - d1 - d2; x++) {
          for (int y = d1 + 1; y <= N - d2; y++) {
            min = Math.min(min, MinDifSections(d1, d2, x, y));
          }
        }
      }
    }

    System.out.println(min);
  }

  // 최소 인구 수 차이 메소드
  private static int MinDifSections(int d1, int d2, int x, int y) {
    SectionMap = SettingMap(d1, d2, x, y);
    int[] peopleCnt = new int[6]; // 사람 수 저장할 배열
    int maxPeople = Integer.MIN_VALUE;
    int minPeople = Integer.MAX_VALUE;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        peopleCnt[SectionMap[i][j]] += PeopleMap[i][j];
      }
    }

    // 최대, 최소 구하기
    for (int i = 1; i <= 5; i++) {
      maxPeople = Math.max(maxPeople, peopleCnt[i]);
      minPeople = Math.min(minPeople, peopleCnt[i]);
    }

    return maxPeople - minPeople;
  }

  // 변수에 따른 구역 세팅
  private static int[][] SettingMap(int d1, int d2, int x, int y) {
    int[][] ret = new int[N + 1][N + 1];

    // 1구역
    for (int i = 1; i < x + d1; i++) {
      for (int j = 1; j <= y; j++) {
        ret[i][j] = 1;
      }
    }
    // 2구역
    for (int i = 1; i <= x + d2; i++) {
      for (int j = y + 1; j <= N; j++) {
        ret[i][j] = 2;
      }
    }
    // 3구역
    for (int i = x + d1; i <= N; i++) {
      for (int j = 1; j < y - d1 + d2; j++) {
        ret[i][j] = 3;
      }
    }
    // 4구역
    for (int i = x + d2 + 1; i <= N; i++) {
      for (int j = y - d1 + d2; j <= N; j++) {
        ret[i][j] = 4;
      }
    }

    // 5구역 경계선 긋기 (기준점을 시작으로 시계방향으로 긋기)
    ret[x][y] = 5;
    int next_x = x;
    int next_y = y;

    for (int i = 1; i <= d2; i++) {
      next_x += d_row[0];
      next_y += d_col[0];

      ret[next_x][next_y] = 5;
    }
    for (int i = 1; i <= d1; i++) {
      next_x += d_row[1];
      next_y += d_col[1];

      ret[next_x][next_y] = 5;
    }
    for (int i = 1; i <= d2; i++) {
      next_x += d_row[2];
      next_y += d_col[2];

      ret[next_x][next_y] = 5;
    }
    for (int i = 1; i <= d1; i++) {
      next_x += d_row[3];
      next_y += d_col[3];

      ret[next_x][next_y] = 5;
    }

    // 5구역 내부 공간
    for (int i = x; i <= x + d1 + d2; i++) {
      int[] p = new int[2];
      int cnt = 0;

      for (int j = 1; j <= N; j++) {
        if (ret[i][j] == 5) {
          p[cnt++] = j;
        }
      }

      if (cnt == 2) {
        for (int j = p[0]; j <= p[1]; j++) {
          ret[i][j] = 5;
        }
      }
    }

    return ret;
  }
}
