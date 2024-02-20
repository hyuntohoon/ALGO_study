package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.Iterator;

public class prob21611 {
  static int N, M;
  static int[][] map;
  static int[] explodedMarbleCnt = new int[4];
  static int[] d_row = { 0, 1, 0, -1 };
  static int[] d_col = { -1, 0, 1, 0 };

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    M = Integer.parseInt(st.nextToken());

    map = new int[N][N];
    for (int i = 0; i < N; i++) {
      st = new StringTokenizer(br.readLine());
      for (int j = 0; j < N; j++) {
        map[i][j] = Integer.parseInt(st.nextToken());
      }
    }

    for (int i = 0; i < M; i++) {
      st = new StringTokenizer(br.readLine());
      int d = Integer.parseInt(st.nextToken());

      // 방향 정정
      if (d == 1) {
        d = 3;
      } else if (d == 2) {
        d = 1;
      } else if (d == 3) {
        d = 0;
      } else {
        d = 2;
      }
      int s = Integer.parseInt(st.nextToken());

      // 블리자드 수행
      Blizzard(d, s);

      // 구슬 리스트
      List<Integer> marbleList = getMarbleList();

      // 블리자드로 없어진 구슬 리스트 정리
      ArrangeMarbleList(marbleList);

      // 폭발이 멈출때까지 진행
      while (true) {
        if (!ExplodeMarble(marbleList)) {
          break;
        }
      }

      // 새로운 그룹 구슬 리스트 생성
      List<Integer> newMarbleList = GroupingMarbleList(marbleList);

      // 맵에 덧씌우기
      map = SetNewMarbleMap(newMarbleList);
    }

    int score = 0;
    for (int i = 1; i <= 3; i++) {
      score += (explodedMarbleCnt[i] * i);
    }

    System.out.println(score);
  }

  // 새로운 구슬 리스트 맵에 덧씌우기
  private static int[][] SetNewMarbleMap(List<Integer> newMarbleList) {
    int[][] ret = new int[N][N];
    int row = N / 2;
    int col = N / 2;
    int d = 0;
    Iterator<Integer> iter = newMarbleList.iterator();

    for (int i = 1; i < N; i++) {
      for (int j = i; j > 0; j--) {
        row += d_row[d];
        col += d_col[d];
        if (!iter.hasNext()) {
          return ret;
        }
        ret[row][col] = iter.next();
      }

      d++;
      d %= 4;

      for (int j = i; j > 0; j--) {
        row += d_row[d];
        col += d_col[d];
        if (!iter.hasNext()) {
          return ret;
        }
        ret[row][col] = iter.next();
      }

      d++;
      d %= 4;
    }

    for (int j = N - 1; j > 0; j--) {
      row += d_row[d];
      col += d_col[d];
      if (!iter.hasNext()) {
        return ret;
      }
      ret[row][col] = iter.next();
    }

    return ret;
  }

  // 그룹 구슬 리스트 생성
  private static List<Integer> GroupingMarbleList(List<Integer> marbleList) {
    List<Integer> ret = new ArrayList<>();
    for (int i = 0; i < marbleList.size();) {
      int marbleNum = marbleList.get(i);
      int marbleCnt = 1;
      for (int j = i + 1; j < marbleList.size(); j++) {
        if (marbleNum == marbleList.get(j)) {
          marbleCnt++;
        } else {
          break;
        }
      }

      ret.add(marbleCnt);
      ret.add(marbleNum);

      i += marbleCnt;
    }

    return ret;
  }

  // 구슬 폭발
  private static boolean ExplodeMarble(List<Integer> marbleList) {
    boolean flag = false;

    for (int i = marbleList.size() - 1; i >= 0;) {
      int marbleCnt = 1;
      for (int j = i - 1; j >= 0; j--) {
        if (marbleList.get(i) == marbleList.get(j)) {
          marbleCnt++;
        } else {
          break;
        }
      }

      // 4개 이상이라면 폭발
      if (marbleCnt >= 4) {
        flag = true;

        explodedMarbleCnt[marbleList.get(i)] += marbleCnt;
        while (marbleCnt-- > 0) {
          marbleList.remove(i--);
        }
      } else {
        i -= marbleCnt;
      }
    }

    return flag;
  }

  // 구슬 정리
  private static void ArrangeMarbleList(List<Integer> marbleList) {
    for (int i = marbleList.size() - 1; i >= 0; i--) {
      if (marbleList.get(i) == 0) {
        marbleList.remove(i);
      }
    }
  }

  // 맵에서 구슬 리스트 생성
  private static List<Integer> getMarbleList() {
    List<Integer> ret = new ArrayList<>();
    int row = N / 2;
    int col = N / 2;
    int d = 0;
    for (int i = 1; i < N; i++) {
      for (int j = i; j > 0; j--) {
        row += d_row[d];
        col += d_col[d];
        ret.add(map[row][col]);
      }

      d++;
      d %= 4;

      for (int j = i; j > 0; j--) {
        row += d_row[d];
        col += d_col[d];
        ret.add(map[row][col]);
      }

      d++;
      d %= 4;
    }

    for (int j = N - 1; j > 0; j--) {
      row += d_row[d];
      col += d_col[d];
      ret.add(map[row][col]);
    }

    return ret;
  }

  private static void Blizzard(int d, int s) {
    int SharkPosRow = N / 2;
    int SharkPosCol = N / 2;
    for (int i = 1; i <= s; i++) {
      int newRow = SharkPosRow + d_row[d] * i;
      int newCol = SharkPosCol + d_col[d] * i;

      map[newRow][newCol] = 0;
    }
  }
}
