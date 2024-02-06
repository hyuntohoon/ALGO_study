package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class prob20061 {
  static int N;
  static int score;
  static boolean[][] redSection = new boolean[4][4];
  static boolean[][] blueSection = new boolean[6][4];
  static boolean[][] greenSection = new boolean[6][4];

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    N = Integer.parseInt(br.readLine());
    while (N-- > 0) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      int type = Integer.parseInt(st.nextToken());
      int x = Integer.parseInt(st.nextToken());
      int y = Integer.parseInt(st.nextToken());

      PutBlock(type, x, y);
    }

    System.out.println(score + "\n" + CountRemainBlock());
  }

  // 남은 블럭 카운트
  private static int CountRemainBlock() {
    int ret = 0;

    // 파랑 영역 카운트
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 4; j++) {
        if (blueSection[i][j]) {
          ret++;
        }
      }
    }

    // 초록 영역 카운트
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 4; j++) {
        if (greenSection[i][j]) {
          ret++;
        }
      }
    }

    return ret;
  }

  // 블럭 놓기
  private static void PutBlock(int type, int x, int y) {
    PutBlueSection(type, x, y);
    PutGreenSection(type, x, y);

    ScoreCheck();
    Row01Check();
  }

  // 초록 보드에 놓기
  private static void PutGreenSection(int type, int x, int y) {
    int blockPosX = 0;
    int blockPosY = y;
    switch (type) {
      case 1: // 타입 1
        while (true) {
          int nextX = blockPosX + 1;

          if (nextX == 6 || greenSection[nextX][blockPosY]) { // 끝에 도달하거나 아래에 블럭이 있거나
            greenSection[blockPosX][blockPosY] = true;
            break;
          }

          blockPosX = nextX;
        }
        break;
      case 2: // 타입 2
        while (true) {
          int nextX = blockPosX + 1;

          if (nextX == 6 || greenSection[nextX][blockPosY] || greenSection[nextX][blockPosY + 1]) { // 수평으로 2개이므로 둘다 체크
            greenSection[blockPosX][blockPosY] = true;
            greenSection[blockPosX][blockPosY + 1] = true;
            break;
          }

          blockPosX = nextX;
        }
        break;
      case 3: // 타입 3
        while (true) {
          int nextX = blockPosX + 1;

          if (nextX == 5 || greenSection[nextX + 1][blockPosY]) { // 수직으로 2개이므로 아래 방향 + 1 블럭 체크
            greenSection[blockPosX][blockPosY] = true;
            greenSection[blockPosX + 1][blockPosY] = true;
            break;
          }

          blockPosX = nextX;
        }
        break;
      default:
        break;
    }
  }

  // 파랑 보드에 놓기 // 전체적인 코드는 PutGreenSection과 동일하지만 행, 열이 바뀜 (type2와 type3가 Green과는
  // 반대로 체크해야함)
  private static void PutBlueSection(int type, int x, int y) {
    int blockPosX = 0;
    int blockPosY = x;
    switch (type) {
      case 1:
        while (true) {
          int nextX = blockPosX + 1;

          if (nextX == 6 || blueSection[nextX][blockPosY]) {
            blueSection[blockPosX][blockPosY] = true;
            break;
          }

          blockPosX = nextX;
        }
        break;
      case 2:
        while (true) {
          int nextX = blockPosX + 1;

          if (nextX == 5 || blueSection[nextX + 1][blockPosY]) {
            blueSection[blockPosX][blockPosY] = true;
            blueSection[blockPosX + 1][blockPosY] = true;
            break;
          }

          blockPosX = nextX;
        }

        break;
      case 3:
        while (true) {
          int nextX = blockPosX + 1;

          if (nextX == 6 || blueSection[nextX][blockPosY] || blueSection[nextX][blockPosY + 1]) {
            blueSection[blockPosX][blockPosY] = true;
            blueSection[blockPosX][blockPosY + 1] = true;
            break;
          }

          blockPosX = nextX;
        }
        break;
      default:
        break;
    }
  }

  // 점수 확인
  private static void ScoreCheck() {
    ScoreCheckBlue();
    ScoreCheckGreen();
  }

  // 초록 보드 점수 확인
  private static void ScoreCheckGreen() {
    for (int i = 5; i > 1; i--) {
      if (greenSection[i][0] && greenSection[i][1] &&
          greenSection[i][2] && greenSection[i][3]) {
        score++;

        // 한 줄씩 당기기
        for (int j = i; j > 0; j--) {
          greenSection[j] = greenSection[j - 1];
        }
        greenSection[0] = new boolean[4];
        // 해당 줄 다시 검사
        i++;
      }
    }
  }

  // 파랑 보드 점수 확인
  private static void ScoreCheckBlue() {
    for (int i = 5; i > 1; i--) {
      if (blueSection[i][0] && blueSection[i][1] &&
          blueSection[i][2] && blueSection[i][3]) {
        score++;

        // 한 줄씩 당기기
        for (int j = i; j > 0; j--) {
          blueSection[j] = blueSection[j - 1];
        }
        blueSection[0] = new boolean[4];
        // 해당 줄 다시 검사
        i++;
      }
    }
  }

  // 0, 1행 블럭 확인
  private static void Row01Check() {
    GreenRowCheck();
    BlueRowCheck();
  }

  // 파랑 보드 0, 1행 블럭 확인
  private static void BlueRowCheck() {
    while (true) { // 1행에 블럭이 있으면 1칸씩 당김, flag를 통해 1행 반복 검사
      boolean flag = false;
      for (int i = 0; i < 4; i++) {
        if (blueSection[1][i]) {
          for (int j = 4; j >= 0; j--) {
            blueSection[j + 1] = blueSection[j];
          }
          blueSection[0] = new boolean[4];
          flag = true;
        }
      }
      if (!flag) {
        break;
      }
    }
  }

  // 초록 보드 0, 1행 블럭 확인
  private static void GreenRowCheck() {
    while (true) {
      boolean flag = false;
      for (int i = 0; i < 4; i++) {
        if (greenSection[1][i]) {
          for (int j = 4; j >= 0; j--) {
            greenSection[j + 1] = greenSection[j];
          }
          greenSection[0] = new boolean[4];
          flag = true;
        }
      }
      if (!flag) {
        break;
      }
    }
  }

}
