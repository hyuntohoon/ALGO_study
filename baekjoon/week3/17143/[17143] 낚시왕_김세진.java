package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob17143 {
  // 상어 클래스
  static class Shark {
    int row;
    int col;
    int size;
    int direction;
    int speed;
    boolean alive;

    public Shark(int row, int col, int size, int direction, int speed) {
      this.row = row;
      this.col = col;
      this.size = size;
      this.direction = direction;
      this.speed = speed;
      this.alive = true;
    }
  }

  static int R, C, M;
  static int[][] map;
  static int UserPos; // 낚시왕 위치
  static int sum;
  static List<Shark> sharkList = new ArrayList<>();
  static int[] d_row = { -1, 0, 1, 0 };
  static int[] d_col = { 0, 1, 0, -1 };

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    StringTokenizer st = new StringTokenizer(br.readLine());
    R = Integer.parseInt(st.nextToken());
    C = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());

    map = new int[R + 1][C + 1];

    // 최초에 null을 삽입하여 1부터 인덱싱하도록
    sharkList.add(null);
    for (int i = 1; i <= M; i++) {
      st = new StringTokenizer(br.readLine());
      int row = Integer.parseInt(st.nextToken());
      int col = Integer.parseInt(st.nextToken());
      int speed = Integer.parseInt(st.nextToken());
      int direction = Integer.parseInt(st.nextToken());
      // 방향 수정
      switch (direction) {
        case 1:
          direction = 0;
          break;
        case 2:
          direction = 2;
          break;
        case 3:
          direction = 1;
          break;
        case 4:
          direction = 3;
          break;
        default:
          break;
      }
      int size = Integer.parseInt(st.nextToken());

      map[row][col] = i;
      sharkList.add(new Shark(row, col, size, direction, speed));
    }

    UserPos = 0;
    while (true) {
      UserPos++;
      if (UserPos > C) {
        break;
      }
      Fishing();
      map = MoveSharks();
    }

    System.out.println(sum);
  }

  // 상어 이동 메서드
  private static int[][] MoveSharks() {
    int[][] ret = new int[R + 1][C + 1];

    for (int i = 1; i < sharkList.size(); i++) {
      Shark cur = sharkList.get(i);
      if (!cur.alive) {
        continue;
      }

      // 나머지 연산
      int distance = 0;
      if (cur.direction % 2 == 1) {
        distance = cur.speed % (2 * C - 2);
      } else {
        distance = cur.speed % (2 * R - 2);
      }

      // 상어 움직임
      while (distance-- > 0) {
        int newRow = cur.row + d_row[cur.direction];
        int newCol = cur.col + d_col[cur.direction];

        if (IsOutBound(newRow, newCol)) {
          cur.direction += 2;
          cur.direction %= 4;
          newRow = cur.row + d_row[cur.direction];
          newCol = cur.col + d_col[cur.direction];
        }
        cur.row = newRow;
        cur.col = newCol;
      }

      // 잡아먹기
      if (ret[cur.row][cur.col] > 0) {
        if (cur.size < sharkList.get(ret[cur.row][cur.col]).size) {
          cur.alive = false;
        } else {
          sharkList.get(ret[cur.row][cur.col]).alive = false;
          ret[cur.row][cur.col] = i;
        }
      } else {
        ret[cur.row][cur.col] = i;
      }
    }

    return ret;
  }

  // 낚시
  private static void Fishing() {
    for (int i = 1; i <= R; i++) {
      if (map[i][UserPos] == 0) {
        continue;
      }

      // 잡을 수 있다면 상어 죽임
      Shark target = sharkList.get(map[i][UserPos]);
      target.alive = false;
      map[i][UserPos] = 0;

      sum += target.size;
      break;
    }
  }

  private static boolean IsOutBound(int row, int col) {
    return row < 1 || row > R || col < 1 || col > C;
  }
}
