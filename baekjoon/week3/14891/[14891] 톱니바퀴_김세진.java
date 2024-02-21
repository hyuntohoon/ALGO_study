package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob14891 {
  static List<Integer>[] gearList = new ArrayList[5];
  static int K;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    for (int i = 1; i <= 4; i++) {
      gearList[i] = new ArrayList<>();

      String s = br.readLine();
      for (int j = 0; j < 8; j++) {
        gearList[i].add(s.charAt(j) - '0');
      }
    }

    K = Integer.parseInt(br.readLine());
    for (int i = 0; i < K; i++) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      int gearNum = Integer.parseInt(st.nextToken());
      int direction = Integer.parseInt(st.nextToken());

      // 왼쪽 사이드 기어 회전 (재귀)
      if (gearNum - 1 > 0) {
        if (gearList[gearNum - 1].get(2) != gearList[gearNum].get(6)) {
          RotateGearLeft(gearNum - 1, direction * (-1));
        }
      }

      // 오른쪽 사이드 기어 회전 (재귀)
      if (gearNum + 1 <= 4) {
        if (gearList[gearNum + 1].get(6) != gearList[gearNum].get(2)) {
          RotateGearRight(gearNum + 1, direction * (-1));
        }
      }

      // 다른 회전이 끝나면 본 기어 회전
      if (direction == 1) {
        int tmp = gearList[gearNum].get(7);
        gearList[gearNum].remove(7);
        gearList[gearNum].add(0, tmp);
      } else {
        int tmp = gearList[gearNum].get(0);
        gearList[gearNum].remove(0);
        gearList[gearNum].add(tmp);
      }
    }

    int score = 0;
    for (int i = 1; i <= 4; i++) {
      score += (gearList[i].get(0)) * Math.pow(2, i - 1);
    }

    System.out.println(score);
  }

  private static void RotateGearRight(int gearNum, int direction) {
    if (gearNum + 1 <= 4) {
      if (gearList[gearNum + 1].get(6) != gearList[gearNum].get(2)) {
        RotateGearRight(gearNum + 1, direction * (-1));
      }
    }

    if (direction == 1) {
      int tmp = gearList[gearNum].get(7);
      gearList[gearNum].remove(7);
      gearList[gearNum].add(0, tmp);
    } else {
      int tmp = gearList[gearNum].get(0);
      gearList[gearNum].remove(0);
      gearList[gearNum].add(tmp);
    }
  }

  private static void RotateGearLeft(int gearNum, int direction) {
    if (gearNum - 1 > 0) {
      if (gearList[gearNum - 1].get(2) != gearList[gearNum].get(6)) {
        RotateGearLeft(gearNum - 1, direction * (-1));
      }
    }

    if (direction == 1) {
      int tmp = gearList[gearNum].get(7);
      gearList[gearNum].remove(7);
      gearList[gearNum].add(0, tmp);
    } else {
      int tmp = gearList[gearNum].get(0);
      gearList[gearNum].remove(0);
      gearList[gearNum].add(tmp);
    }
  }
}
