package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class prob14501_3 {
  static int N;
  static int[] profit; // 상담날에 따른 이익
  static int[] needDay; // 상담날에 따른 필요 일 수
  static int[] dp;

  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    N = Integer.parseInt(br.readLine());
    profit = new int[N + 1];
    needDay = new int[N + 1];
    dp = new int[N + 1];

    for (int i = 1; i <= N; i++) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      needDay[i] = Integer.parseInt(st.nextToken());
      profit[i] = Integer.parseInt(st.nextToken());
    }

    if (needDay[N] == 1) {
      dp[N] = profit[N];
    }

    for (int i = N - 1; i > 0; i--) {
      if (i + needDay[i] - 1 < N) { // i날에 상담 후 다음번 상담도 가능한 경우
        dp[i] = Math.max(dp[i + 1], profit[i] + dp[i + needDay[i]]);
      } else if (i + needDay[i] - 1 == N) { // i날에 상담이 끝인 경우
        dp[i] = Math.max(dp[i + 1], profit[i]);
      } else { // i날에 상담을 못하는 경우
        dp[i] = dp[i + 1];
      }
    }

    System.out.println(dp[1]);
  }
}
