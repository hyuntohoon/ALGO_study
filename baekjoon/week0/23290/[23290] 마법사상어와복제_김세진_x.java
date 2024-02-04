package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

public class prob23290 {
  static int M;
  static int S;

  static class cdnt {
    int row;
    int col;

    cdnt(int row, int col) {
      this.row = row;
      this.col = col;
    }
  }

  // static class Fish extends cdnt {
  // int direction;

  // Fish(int row, int col, int direction) {
  // super(row, col);
  // this.direction = direction;
  // }
  // }

  static cdnt sharkPos;
  static List<Integer>[][] FishMap = new ArrayList[5][5];
  static List<Integer>[][] FishMapTemp = new ArrayList[5][5];
  static int[][] map = new int[5][5];
  static int ans = 0;
  static int[] d8_row = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
  static int[] d8_col = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
  static int[] d4_row = { -1, 0, 1, 0 };
  static int[] d4_col = { 0, -1, 0, 1 };
  static int[] sharkRoute;
  static int[] routeBuffer;
  static int maxOfEatingFish = 0;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    M = Integer.parseInt(st.nextToken());
    S = Integer.parseInt(st.nextToken());

    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        FishMap[i][j] = new ArrayList<>();
      }
    }

    // 입력
    for (int i = 0; i < M; i++) {
      st = new StringTokenizer(br.readLine());
      int row = Integer.parseInt(st.nextToken());
      int col = Integer.parseInt(st.nextToken());
      int direction = Integer.parseInt(st.nextToken());

      FishMap[row][col].add(direction);
    }
    st = new StringTokenizer(br.readLine());
    int row = Integer.parseInt(st.nextToken());
    int col = Integer.parseInt(st.nextToken());
    sharkPos = new cdnt(row, col);
    map[row][col] = -1;

    while (S-- > 0) {
      Simulation();
    }

    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        ans += FishMap[i][j].size();
      }
    }

    System.out.println(ans);
  }

  private static void Simulation() {
    for(int i=1;i<=4;i++){
      for(int j=1;j<=4;j++){
        FishMapTemp[i][j] = new ArrayList<>();
        FishMapTemp[i][j].addAll(FishMap[i][j]);
      }
    }

    MoveFishes();
    MoveShark();
    UpdateMap();
    DuplicateFishes();
  }

  private static void DuplicateFishes() {
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        int num = FishMapTemp[i][j].size();
        for (int k = 0; k < num; k++) {
          FishMap[i][j].add(FishMapTemp[i][j].get(k));
        }
      }
    }
  }

  private static void UpdateMap() {
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        if (map[i][j] > 0) {
          map[i][j]--;
        }
      }
    }
  }

  private static void MoveShark() {
    map[sharkPos.row][sharkPos.col] = 0;

    sharkRoute = new int[3];
    routeBuffer = new int[3];
    maxOfEatingFish = 0;
    BackTrackingShark(sharkPos.row, sharkPos.col, 0, 0);

    for (int i = 0; i < 3; i++) {
      sharkPos.row += d4_row[sharkRoute[i]];
      sharkPos.col += d4_col[sharkRoute[i]];

      if(FishMap[sharkPos.row][sharkPos.col].size() > 0){
        map[sharkPos.row][sharkPos.col] = 3;
      }
      FishMap[sharkPos.row][sharkPos.col].clear();
    }
    map[sharkPos.row][sharkPos.col] = -1;
  }

  private static void BackTrackingShark(int row, int col, int fishCnt, int depth) {
    if (depth == 3) {
      if (maxOfEatingFish < fishCnt) {
        maxOfEatingFish = fishCnt;
        sharkRoute = routeBuffer.clone();
      }
      return;
    }

    for (int i = 0; i < 4; i++) {
      int new_row = row + d4_row[i];
      int new_col = col + d4_col[i];

      if (IsOutBound(new_row, new_col)) {
        continue;
      }

      routeBuffer[depth] = i;
      List<Integer> FishTempList = new ArrayList<>();
      FishTempList.addAll(FishMap[new_row][new_col]);
      int newPosFishCnt = FishMap[new_row][new_col].size();
      FishMap[new_row][new_col].clear();
      BackTrackingShark(new_row, new_col, fishCnt + newPosFishCnt, depth + 1);
      FishMap[new_row][new_col] = FishTempList;
    }
  }

  private static void MoveFishes() {
    List<Integer>[][] NewMap = new ArrayList[5][5];
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        NewMap[i][j] = new ArrayList<>();
      }
    }

    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        for (Iterator<Integer> iter = FishMap[i][j].iterator(); iter.hasNext();) {
          int fish = iter.next();
          for (int k = 8; k > 0; k--) {
            int direction = (fish + k) % 8 == 0 ? 1 : (fish + k) % 8;
            if (isPossible(i, j, direction)) {
              NewMap[i + d8_row[direction]][j + d8_col[direction]].add(direction);
              iter.remove();
              break;
            }
          }
        }
      }
    }

    FishMap = NewMap;
  }

  private static boolean isPossible(int row, int col, int direction) {
    int new_row = row + d8_row[direction];
    int new_col = col + d8_col[direction];

    return !IsOutBound(new_row, new_col) && map[new_row][new_col] == 0;
  }

  private static boolean IsOutBound(int row, int col) {
    return row < 1 || row > 4 || col < 1 || col > 4;
  }

}
