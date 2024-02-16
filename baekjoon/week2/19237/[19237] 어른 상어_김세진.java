package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.StringTokenizer;

public class prob19237 {
  // 공간 클래스 (냄새 수치와 냄새를 남긴 상어를 기록)
  static class Space {
    int scent;
    int scentSharkNum;

    public Space(int scent, int scentSharkNum) {
      this.scent = scent;
      this.scentSharkNum = scentSharkNum;
    }
  }

  // 상어 클래스
  static class Shark implements Comparable<Shark> {
    int num;
    int row;
    int col;
    int direction;

    public Shark(int num, int row, int col) {
      this.num = num;
      this.row = row;
      this.col = col;
    }

    // 상어 객체는 리스트에 오름차순 정렬 (우선순위)
    @Override
    public int compareTo(Shark o) {
      return this.num - o.num;
    }
  }

  static int[] d_row = { 0, -1, 1, 0, 0 };
  static int[] d_col = { 0, 0, 0, -1, 1 };
  static int[][][] sharkDirectionInfo;
  static List<Shark> sharkList = new ArrayList<>();
  static int N, M, k;
  static Space[][] map;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());
    k = Integer.parseInt(st.nextToken());

    map = new Space[N + 1][N + 1];
    sharkDirectionInfo = new int[M + 1][5][4];
    for (int i = 1; i <= N; i++) {
      st = new StringTokenizer(br.readLine());
      for (int j = 1; j <= N; j++) {
        int v = Integer.parseInt(st.nextToken());
        if (v > 0) {
          sharkList.add(new Shark(v, i, j));
        }
        map[i][j] = new Space(0, 0);
      }
    }

    Collections.sort(sharkList);
    st = new StringTokenizer(br.readLine());
    for (Shark shark : sharkList) {
      shark.direction = Integer.parseInt(st.nextToken());
    }

    for (int i = 1; i <= M; i++) {
      for (int j = 1; j <= 4; j++) {
        st = new StringTokenizer(br.readLine());
        for (int k = 0; k < 4; k++) {
          sharkDirectionInfo[i][j][k] = Integer.parseInt(st.nextToken());
        }
      }
    }

    // 상어 최초 냄새 남기기
    int cnt = 0;
    sharkList.forEach(s -> {
      map[s.row][s.col].scent = k;
      map[s.row][s.col].scentSharkNum = s.num;
    });

    // 시뮬레이션
    while (sharkList.size() > 1) {
      if (cnt > 1000) { // 1000이 넘어가면 break
        break;
      }
      cnt++;
      for (Shark shark : sharkList) {
        Move(shark);
      }
      UpdateMap();
    }

    System.out.println(cnt > 1000 ? -1 : cnt);
  }

  // 맵 업데이트 메서드
  private static void UpdateMap() {
    // 상어 냄새 지우기 (1씩)
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        if (map[i][j].scent > 0) {
          map[i][j].scent--;
        }
      }
    }

    // 현재 위치가 겹친 상어 중에서 번호가 낮은 상어 제거
    List<Integer> removeList = new ArrayList<>();
    for (int i = 0; i < sharkList.size() - 1; i++) {
      for (int j = i + 1; j < sharkList.size(); j++) {
        if (sharkList.get(i).row == sharkList.get(j).row && sharkList.get(i).col == sharkList.get(j).col) {
          removeList.add(sharkList.get(j).num);
        }
      }
    }

    for (int i = 0; i < sharkList.size(); i++) {
      for (int j : removeList) {
        if (sharkList.get(i).num == j) {
          sharkList.remove(i);
          i--;
        }
      }
    }

    // 남은 상어 위치에 냄새 남기기
    sharkList.forEach(s -> {
      map[s.row][s.col].scent = k;
      map[s.row][s.col].scentSharkNum = s.num;
    });

  }

  // 상어 움직임 메서드
  private static void Move(Shark shark) {
    // 빈 칸 찾기
    for (int i = 0; i < 4; i++) {
      int nextRow = shark.row + d_row[sharkDirectionInfo[shark.num][shark.direction][i]];
      int nextCol = shark.col + d_col[sharkDirectionInfo[shark.num][shark.direction][i]];
      if (IsOutBound(nextRow, nextCol)) {
        continue;
      }

      if (map[nextRow][nextCol].scent == 0) {
        shark.row = nextRow;
        shark.col = nextCol;
        shark.direction = sharkDirectionInfo[shark.num][shark.direction][i];
        return;
      }
    }

    // 자신의 냄새 찾기
    for (int i = 0; i < 4; i++) {
      int nextRow = shark.row + d_row[sharkDirectionInfo[shark.num][shark.direction][i]];
      int nextCol = shark.col + d_col[sharkDirectionInfo[shark.num][shark.direction][i]];
      if (IsOutBound(nextRow, nextCol)) {
        continue;
      }

      if (map[nextRow][nextCol].scentSharkNum == shark.num) {
        shark.row = nextRow;
        shark.col = nextCol;
        shark.direction = sharkDirectionInfo[shark.num][shark.direction][i];
        return;
      }
    }
  }

  private static boolean IsOutBound(int row, int col) {
    return row < 1 || row > N || col < 1 || col > N;
  }
}