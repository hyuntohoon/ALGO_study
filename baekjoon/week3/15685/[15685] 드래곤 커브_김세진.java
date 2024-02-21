package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class prob15685 {
    static int N;
    static boolean[][] map = new boolean[101][101];
    static int[] d_y = { 0, -1, 0, 1 };
    static int[] d_x = { 1, 0, -1, 0 };
    static int cnt = 0;

    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int startX = Integer.parseInt(st.nextToken());
            int startY = Integer.parseInt(st.nextToken());
            int d = Integer.parseInt(st.nextToken());
            int g = Integer.parseInt(st.nextToken());

            List<Integer> routeList = new ArrayList<>(); // 드래곤 커브의 전체 동선을 저장할 리스트
            routeList.add(d); // 0세대 동선 저장
            int endX = startX + d_x[d];
            int endY = startY + d_y[d];
            map[endY][endX] = true;
            map[startY][startX] = true;

            // 1세대부터 커브 그리기
            for (int j = 1; j <= g; j++) {
                // 새로운 끝점 (시계 방향 회전)
                int dX = startX - endX;
                int dY = startY - endY;
                int tmpX = endX -= dY;
                int tmpY = endY += dX;
                map[tmpY][tmpX] = true;

                List<Integer> tmpList = new ArrayList<>(); // 새롭게 그릴 커브 동선
                for (int direction : routeList) {
                    int newDirection = (direction + 3) % 4; // 방향 벡터가 반시계이기 때문에 반대로 (시계)
                    tmpList.add(newDirection);
                    tmpX += d_x[newDirection];
                    tmpY += d_y[newDirection];

                    map[tmpY][tmpX] = true;
                }

                // 새롭게 그린 커브 동선을 뒤에서부터, 방향은 반대로, 전체 동선 리스트에 저장
                for (int k = tmpList.size() - 1; k >= 0; k--) {
                    routeList.add((tmpList.get(k) + 2) % 4);
                }
            }
        }

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                if (!map[i][j]) {
                    continue;
                }
                if (!map[i + 1][j]) {
                    continue;
                }
                if (!map[i][j + 1]) {
                    continue;
                }
                if (!map[i + 1][j + 1]) {
                    continue;
                }
                cnt++;
            }
        }

        System.out.println(cnt);
    }
}
