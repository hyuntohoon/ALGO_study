package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob15683 {
  static int N;
  static int M;
  static int[][] map;
  static List<CCTV> cctvList = new ArrayList<>(); // CCTV 리스트
  static int min = Integer.MAX_VALUE;
  static int spaceCounter = 0;
  static int[] d_row = { 0, 1, 0, -1 };
  static int[] d_col = { 1, 0, -1, 0 };

  // 좌표 클래스
  static class cdnt {
    int row;
    int col;

    cdnt(int row, int col) {
      this.row = row;
      this.col = col;
    }
  }

  // CCTV 클래스
  static class CCTV extends cdnt {
    int type;
    int direction;

    CCTV(int type, int direction, int row, int col) {
      super(row, col);
      this.type = type;
      this.direction = direction;
    }

    // 방향 변경
    public void UpdateDirection(int direction) {
      if (this.direction != -1) { // 최초 설정이 아닐때
        UpdateMap(this.direction, -10);
      }
      UpdateMap(direction, 10);

      this.direction = direction;
    }

    // 맵 업데이트 (value: 가중치 (방향 해제 = -10, 방향 설정 = 10))
    public void UpdateMap(int direction, int value) {
      switch (type) { // 타입별로 방향 탐색
        case 1:
          CheckSpace(new cdnt(this.row, this.col), direction, value);
          break;
        case 2:
          CheckSpace(new cdnt(this.row, this.col), direction, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 2) % 4, value);
          break;
        case 3:
          CheckSpace(new cdnt(this.row, this.col), direction, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 1) % 4, value);
          break;
        case 4:
          CheckSpace(new cdnt(this.row, this.col), direction, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 1) % 4, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 2) % 4, value);
          break;
        case 5:
          CheckSpace(new cdnt(this.row, this.col), direction, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 1) % 4, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 2) % 4, value);
          CheckSpace(new cdnt(this.row, this.col), (direction + 3) % 4, value);
          break;
        default:
          break;
      }
    }
  }

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());
    map = new int[N][M];

    // 입력
    for (int i = 0; i < N; i++) {
      st = new StringTokenizer(br.readLine());
      for (int j = 0; j < M; j++) {
        map[i][j] = Integer.parseInt(st.nextToken());
        if (map[i][j] != 0 && map[i][j] != 6) {
          cctvList.add(new CCTV(map[i][j], -1, i, j));
        }
      }
    }

    // 백트래킹
    CCTV_DirectionSetting(0);

    // 출력
    System.out.println(min);
  }

  // CCTV 방향 완전탐색
  private static void CCTV_DirectionSetting(int depth) {
    if (depth == cctvList.size()) {
      min = Math.min(min, SpaceCounter());
      return;
    }

    for (int i = 0; i < 4; i++) {
      cctvList.get(depth).UpdateDirection(i);
      CCTV_DirectionSetting(depth + 1);
    }
  }

  // 맵 상의 빈 공간 카운터
  private static int SpaceCounter() {
    int ret = 0;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (map[i][j] == 0) {
          ret++;
        }
      }
    }

    return ret;
  }

  private static boolean IsOutBound(int row, int col) {
    return row < 0 || row >= N || col < 0 || col >= M;
  }

  // 방향에 따른 맵 탐색
  private static void CheckSpace(cdnt now, int direction, int value) {
    while (!IsOutBound(now.row, now.col) && map[now.row][now.col] != 6) {
      map[now.row][now.col] += value;
      now.row += d_row[direction];
      now.col += d_col[direction];
    }
  }
}
