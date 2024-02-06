package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class prob23290_2 {
  static int M, S;
  static int[][][] FishMap = new int[5][5][9];
  static int[][][] FishMapCopy;
  static int[][][] tmpMap;
  static int sharkPosX;
  static int sharkPosY;
  static int[] d_row_fish = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
  static int[] d_col_fish = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
  static int[] d_row_shark = { -1, 0, 1, 0 };
  static int[] d_col_shark = { 0, -1, 0, 1 };
  static int[][] ScentMap = new int[5][5];
  static int[] sharkRoute;
  static int[] RouteBuffer;
  static int EatenFishMax;
  static boolean[][] visited;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    M = Integer.parseInt(st.nextToken());
    S = Integer.parseInt(st.nextToken());

    for (int i = 0; i < M; i++) {
      st = new StringTokenizer(br.readLine());
      int row = Integer.parseInt(st.nextToken());
      int col = Integer.parseInt(st.nextToken());
      int direction = Integer.parseInt(st.nextToken());

      FishMap[row][col][direction]++;
    }

    st = new StringTokenizer(br.readLine());
    sharkPosX = Integer.parseInt(st.nextToken());
    sharkPosY = Integer.parseInt(st.nextToken());

    while (S-- > 0) {
      Simulation();
    }

    int sum = 0;
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        for (int k = 1; k <= 8; k++) {
          sum += FishMap[i][j][k];
        }
      }
    }

    System.out.println(sum);
  }

  private static void Simulation() {
    FishMapCopy = new int[5][5][9];
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        for (int k = 1; k <= 8; k++) {
          FishMapCopy[i][j][k] = FishMap[i][j][k];
        }
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
        for (int k = 1; k <= 8; k++) {
          FishMap[i][j][k] += FishMapCopy[i][j][k];
        }
      }
    }
  }

  private static void UpdateMap() {
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        if (ScentMap[i][j] > 0) {
          ScentMap[i][j]--;
        }
      }
    }
  }

  private static void MoveShark() {
    visited = new boolean[5][5];
    sharkRoute = new int[3];
    RouteBuffer = new int[3];
    EatenFishMax = -1;

    visited[sharkPosX][sharkPosY] = true;
    SharkBackTracking(sharkPosX, sharkPosY, 0, 0);

    for (int i = 0; i < 3; i++) {
      sharkPosX += d_row_shark[sharkRoute[i]];
      sharkPosY += d_col_shark[sharkRoute[i]];

      for (int j = 1; j <= 8; j++) {
        if (FishMap[sharkPosX][sharkPosY][j] > 0) {
          FishMap[sharkPosX][sharkPosY][j] = 0;
          ScentMap[sharkPosX][sharkPosY] = 3;
        }
      }
    }
  }

  private static void SharkBackTracking(int row, int col, int EatenFishCnt, int depth) {
    if (depth == 3) {
      if (EatenFishCnt > EatenFishMax) {
        EatenFishMax = EatenFishCnt;
        sharkRoute = RouteBuffer.clone();
      }
      return;
    }

    for (int i = 0; i < 4; i++) {
      int new_row = row + d_row_shark[i];
      int new_col = col + d_col_shark[i];

      if (IsOutBound(new_row, new_col)) {
        continue;
      }

      RouteBuffer[depth] = i;
      int FishesOnSpace = 0;
      int[] arrBuf = FishMap[new_row][new_col].clone();
      for (int j = 1; j <= 8; j++) {
        FishesOnSpace += FishMap[new_row][new_col][j];
        FishMap[new_row][new_col][j] = 0;
      }
      SharkBackTracking(new_row, new_col, EatenFishCnt + FishesOnSpace, depth + 1);
      FishMap[new_row][new_col] = arrBuf;
    }
  }

  private static void MoveFishes() {
    tmpMap = new int[5][5][9];

    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 4; j++) {
        for (int k = 1; k <= 8; k++) {
          if (FishMap[i][j][k] > 0) {
            MoveFish(i, j, k);
          }
        }
      }
    }

    FishMap = tmpMap;
  }

  private static void MoveFish(int row, int col, int direction) {
    for (int i = 8; i > 0; i--) {
      int newDirection = ((direction + i) % 8 == 0) ? 8 : (direction + i) % 8;
      int new_row = row + d_row_fish[newDirection];
      int new_col = col + d_col_fish[newDirection];

      if (IsPossibleMove(new_row, new_col)) {
        tmpMap[new_row][new_col][newDirection] += FishMap[row][col][direction];
        FishMap[row][col][direction] = 0;
        break;
      }
    }

    tmpMap[row][col][direction] += FishMap[row][col][direction];
  }

  private static boolean IsPossibleMove(int row, int col) {
    if (IsOutBound(row, col)) {
      return false;
    }
    if (ScentMap[row][col] > 0) {
      return false;
    }
    if (sharkPosX == row && sharkPosY == col) {
      return false;
    }

    return true;
  }

  private static boolean IsOutBound(int row, int col) {
    return row < 1 || row > 4 || col < 1 || col > 4;
  }
}
