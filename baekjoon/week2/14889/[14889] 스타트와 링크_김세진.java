package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob14889_2 {
    static int[][] AbilityMap;
    static int N;
    static boolean[] isSelected;
    static int ans = Integer.MAX_VALUE;

    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        N = Integer.parseInt(br.readLine());
        AbilityMap = new int[N + 1][N + 1];
        isSelected = new boolean[N + 1];
        for (int i = 1; i <= N; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int j = 1; j <= N; j++) {
                AbilityMap[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        Combi(0, 0);

        System.out.println(ans);
    }

    private static void Combi(int prev, int depth) {
        if (depth == N / 2) {
            List<Integer> SelectedList = new ArrayList<>();
            int SumSelected = 0;
            List<Integer> NonSelectedList = new ArrayList<>();
            int SumNonSelected = 0;
            for (int i = 1; i <= N; i++) {
                if (isSelected[i]) {
                    SelectedList.add(i);
                } else {
                    NonSelectedList.add(i);
                }
            }

            for (int i = 0; i < SelectedList.size(); i++) {
                for (int j = i + 1; j < SelectedList.size(); j++) {
                    SumSelected += AbilityMap[SelectedList.get(i)][SelectedList.get(j)];
                    SumSelected += AbilityMap[SelectedList.get(j)][SelectedList.get(i)];
                }
            }
            for (int i = 0; i < NonSelectedList.size(); i++) {
                for (int j = i + 1; j < NonSelectedList.size(); j++) {
                    SumNonSelected += AbilityMap[NonSelectedList.get(i)][NonSelectedList.get(j)];
                    SumNonSelected += AbilityMap[NonSelectedList.get(j)][NonSelectedList.get(i)];
                }
            }

            ans = Math.min(ans, Math.abs(SumSelected - SumNonSelected));
            return;
        }

        for (int i = prev + 1; i <= N; i++) {
            isSelected[i] = true;
            Combi(i, depth + 1);
            isSelected[i] = false;
        }
    }
}
