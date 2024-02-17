package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob16235 {
  // 토지 클래스
  static class Ground {
    List<Integer> treeList;
    int sumEnergy;
    int deadEnergy; // 죽은 나무 양분 합

    Ground() {
      sumEnergy = 5;
      treeList = new ArrayList<>();
      deadEnergy = 0;
    }

    // 죽은 나무로 인한 양분 획득
    public void commit() {
      this.sumEnergy += this.deadEnergy;
      this.deadEnergy = 0;
    }
  }

  static int N, M, K;
  static int[][] A;
  static Ground[][] map;
  static int[] d_row = { -1, -1, -1, 0, 0, 1, 1, 1 };
  static int[] d_col = { -1, 0, 1, -1, 1, -1, 0, 1 };

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());
    K = Integer.parseInt(st.nextToken());

    map = new Ground[N + 1][N + 1];
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        map[i][j] = new Ground();
      }
    }
    A = new int[N + 1][N + 1];
    for (int i = 1; i <= N; i++) {
      st = new StringTokenizer(br.readLine());
      for (int j = 1; j <= N; j++) {
        A[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    for (int i = 0; i < M; i++) {
      st = new StringTokenizer(br.readLine());
      int row = Integer.parseInt(st.nextToken());
      int col = Integer.parseInt(st.nextToken());
      int old = Integer.parseInt(st.nextToken());

      map[row][col].treeList.add(old);
    }

    while (K-- > 0) {
      Spring();
      Summer();
      Autumn();
      Winter();
    }

    System.out.println(SumOfTree());
  }

  // 겨울 메서드; 양분 더하기
  private static void Winter() {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        map[i][j].sumEnergy += A[i][j];
      }
    }
  }

  // 가을 메서드; 5의 배수인 나무들을 탐색해서 주변에 나무 생성
  private static void Autumn() {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        for (int tree : map[i][j].treeList) {
          if (tree % 5 == 0) {
            for (int d = 0; d < 8; d++) {
              int newRow = i + d_row[d];
              int newCol = j + d_col[d];
              if (IsOutBound(newRow, newCol)) {
                continue;
              }

              map[newRow][newCol].treeList.add(1);
            }
          }
        }
      }
    }
  }

  // 여름 메서드; 봄에 기록한 죽은 나무 양분 더하기
  private static void Summer() {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        map[i][j].commit();
      }
    }
  }

  // 봄 메서드; 토지에 있는 나무들을 나이 순 정렬한 뒤 양분 주기
  // 양분을 주지 못한다면 해당 나무 제거 후 토지의 죽은 나무 양분 합하기
  private static void Spring() {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        map[i][j].treeList.sort(null);

        for (int k = 0; k < map[i][j].treeList.size(); k++) {
          int tree = map[i][j].treeList.get(k);

          if (tree > map[i][j].sumEnergy) {
            map[i][j].deadEnergy += tree / 2;
            map[i][j].treeList.remove(k--);
          } else {
            map[i][j].sumEnergy -= tree;
            map[i][j].treeList.set(k, tree + 1);
          }
        }
      }
    }
  }

  private static int SumOfTree() {
    int ret = 0;

    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        ret += map[i][j].treeList.size();
      }
    }

    return ret;
  }

  private static boolean IsOutBound(int row, int col) {
    return row < 1 || row > N || col < 1 || col > N;
  }
}
