package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;

public class prob21608 {
    static class Cdnt{
        int row;
        int col;
        Cdnt(int row, int col){
            this.row = row;
            this.col = col;
        }
    }
    static int[][] map;
    static int[][] studentInfo;
    static int N;
    static int score = 0;
    static Queue<Integer> studentQ = new LinkedList<>();
    static int[] d_row = { -1, 0, 1, 0 };
    static int[] d_col = { 0, 1, 0, -1 };

    public static void main(String[] args) throws NumberFormatException, IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());

        map = new int[N + 1][N + 1];
        studentInfo = new int[N * N + 1][4];

        for (int i = 0; i < N * N; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int num = Integer.parseInt(st.nextToken());
            studentQ.add(num);
            for (int j = 0; j < 4; j++) {
                studentInfo[num][j] = Integer.parseInt(st.nextToken());
            }
        }

        // 자리 배치
        while (!studentQ.isEmpty()) {
            int studentNum = studentQ.poll();

            Cdnt cdnt = SetSeat(studentNum);

            try {
                map[cdnt.row][cdnt.col] = studentNum;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

        // 점수 계산
        System.out.println(CalculateTotalScores());
    }

    private static Cdnt SetSeat(int studentNum) {
        Queue<Cdnt> targetQ1 = new LinkedList<>();

        // 조건 1 
        int maxNearLikeCnt = 0;
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                int cnt = 0;
                if(map[i][j] != 0){
                    continue;
                }

                for(int d=0;d<4;d++){
                    int checkRow = i +d_row[d];
                    int checkCol = j + d_col[d];

                    if(IsOutBound(checkRow, checkCol)){
                        continue;
                    }

                    for (int k = 0; k < 4; k++) {
                        if (map[checkRow][checkCol] == studentInfo[studentNum][k]) {
                            cnt++;
                            break;
                        }
                    }
                }

                if(cnt > maxNearLikeCnt){
                    maxNearLikeCnt = cnt;
                    targetQ1 = new LinkedList<>();
                    targetQ1.add(new Cdnt(i, j));
                } else if(cnt == maxNearLikeCnt){
                    targetQ1.add(new Cdnt(i, j));
                }
            }
        }

        if(targetQ1.size() == 1){
            return targetQ1.poll();
        }

        // 조건 2
        Queue<Cdnt> targetQ2 = new LinkedList<>();
        int maxEmptySpaceCnt = 0;
        while(!targetQ1.isEmpty()){
            Cdnt now = targetQ1.poll();
            int cnt = 0;
            for(int d=0;d<4;d++){
                int checkRow = now.row +d_row[d];
                int checkCol = now.col + d_col[d];

                if(IsOutBound(checkRow, checkCol)){
                    continue;
                }

                if(map[checkRow][checkCol] == 0){
                    cnt++;
                }
            }
            if(cnt > maxEmptySpaceCnt){
                maxEmptySpaceCnt = cnt;
                targetQ2 = new LinkedList<>();
                targetQ2.add(now);
            } else if(cnt == maxEmptySpaceCnt){
                targetQ2.add(now);
            }
        }

        if(targetQ2.size() == 1){
            return targetQ2.poll();
        }

        // 조건 3
        PriorityQueue<Cdnt> targetQ3 = new PriorityQueue<>(new Comparator<Cdnt>() {
            @Override
            public int compare(Cdnt o1, Cdnt o2) {
                if(o1.row == o2.row){
                    return o1.col - o2.col;
                }
                return o1.row - o2.row;
            }
        });

        targetQ2.forEach(cdnt -> targetQ3.add(cdnt));

        return targetQ3.poll();
    }

    private static int CalculateTotalScores() {
        int ret = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                int cnt = 0;

                for (int d = 0; d < 4; d++) {
                    int checkRow = i + d_row[d];
                    int checkCol = j + d_col[d];

                    if (IsOutBound(checkRow, checkCol)) {
                        continue;
                    }

                    for (int k = 0; k < 4; k++) {
                        if (map[checkRow][checkCol] == studentInfo[map[i][j]][k]) {
                            cnt++;
                            break;
                        }
                    }
                }

                switch (cnt) {
                    case 0:
                        ret += 0;
                        break;
                    case 1:
                        ret += 1;
                        break;
                    case 2:
                        ret += 10;
                        break;
                    case 3:
                        ret += 100;
                        break;
                    case 4:
                        ret += 1000;
                        break;
                    default:
                        break;
                }
            }
        }

        return ret;
    }

    private static boolean IsOutBound(int row, int col) {
        return row < 1 || row > N || col < 1 || col > N;
    }
}
