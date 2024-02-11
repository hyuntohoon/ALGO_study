package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class prob23288 {
    static int N, M, K;
    static int[][] map;
    static int scoreSum = 0;
    static int[] d_row = { 0, 1, 0, -1 };
    static int[] d_col = { 1, 0, -1, 0 };

    static class Cdnt {
        int row;
        int col;

        Cdnt(int row, int col) {
            this.row = row;
            this.col = col;
        }
    }

    // 주사위 클래스
    static class Dice {
        int[][] diagram;
        int row, col;
        int direction = 0;

        // 초기화 (1,1)에 배치
        Dice() {
            this.diagram = new int[4][3];
            this.diagram[1][1] = 1; // 위
            this.diagram[3][1] = 6; // 아래
            this.diagram[0][1] = 2; // 북
            this.diagram[1][0] = 4; // 서
            this.diagram[2][1] = 5; // 남
            this.diagram[1][2] = 3; // 동

            this.row = 1;
            this.col = 1;
        }

        // 주사위 굴리기
        public void Roll() {
            int nextRow = this.row + d_row[direction];
            int nextCol = this.col + d_col[direction];

            // 맵 밖이라면 반대로 굴리기
            if (IsOutBound(nextRow, nextCol)) {
                direction += 2;
                direction %= 4;
                Roll();
                return;
            }

            this.row = nextRow;
            this.col = nextCol;

            switch (this.direction) {
                case 0:
                    RollEast();
                    break;

                case 1:
                    RollSouth();
                    break;

                case 2:
                    RollWest();
                    break;

                case 3:
                    RollNorth();
                    break;
                default:
                    break;
            }
        }

        // 남쪽으로 굴리기
        public void RollSouth() {
            int[][] tmp = new int[4][3];
            tmp[1][1] = this.diagram[0][1]; // 위
            tmp[3][1] = this.diagram[2][1]; // 아래
            tmp[0][1] = this.diagram[3][1]; // 북
            tmp[1][0] = this.diagram[1][0]; // 서
            tmp[2][1] = this.diagram[1][1]; // 남
            tmp[1][2] = this.diagram[1][2]; // 동

            this.diagram = tmp;
        }

        // 북쪽으로 굴리기
        public void RollNorth() {
            int[][] tmp = new int[4][3];
            tmp[1][1] = this.diagram[2][1]; // 위
            tmp[3][1] = this.diagram[0][1]; // 아래
            tmp[0][1] = this.diagram[1][1]; // 북
            tmp[1][0] = this.diagram[1][0]; // 서
            tmp[2][1] = this.diagram[3][1]; // 남
            tmp[1][2] = this.diagram[1][2]; // 동

            this.diagram = tmp;
        }

        // 서쪽으로 굴리기
        public void RollWest() {
            int[][] tmp = new int[4][3];
            tmp[1][1] = this.diagram[1][2]; // 위
            tmp[3][1] = this.diagram[1][0]; // 아래
            tmp[0][1] = this.diagram[0][1]; // 북
            tmp[1][0] = this.diagram[1][1]; // 서
            tmp[2][1] = this.diagram[2][1]; // 남
            tmp[1][2] = this.diagram[3][1]; // 동

            this.diagram = tmp;
        }

        // 동쪽으로 굴리기
        public void RollEast() {
            int[][] tmp = new int[4][3];
            tmp[1][1] = this.diagram[1][0]; // 위
            tmp[3][1] = this.diagram[1][2]; // 아래
            tmp[0][1] = this.diagram[0][1]; // 북
            tmp[1][0] = this.diagram[3][1]; // 서
            tmp[2][1] = this.diagram[2][1]; // 남
            tmp[1][2] = this.diagram[1][1]; // 동

            this.diagram = tmp;
        }

        // 디버깅 메서드
        // public void printDice(){
        //     for(int i=0;i<4;i++){
        //         for(int j=0;j<3;j++){
        //             System.out.print(this.diagram[i][j] + " ");
        //         }
        //         System.out.println();
        //     }
        //     System.out.println();
        // }
    }

    static Dice dice = new Dice();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        map = new int[N + 1][M + 1];
        for (int i = 1; i <= N; i++) {
            st = new StringTokenizer(br.readLine());
            for (int j = 1; j <= M; j++) {
                map[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        while (K-- > 0) {
            dice.Roll();

            getScore();

            getNewDirection();
        }

        System.out.println(scoreSum);
    }

    // 방향 수정
    private static void getNewDirection() {
        int bottomValue = dice.diagram[3][1];

        // 크다면 시계방향
        if (bottomValue > map[dice.row][dice.col]) {
            dice.direction++;
            dice.direction %= 4;
        } else if (bottomValue < map[dice.row][dice.col]) { // 작다면 반시계
            dice.direction += 4;
            dice.direction--;
            dice.direction %= 4;
        }
    }

    // 점수 계산 (BFS)
    private static void getScore() {
        boolean[][] visited = new boolean[N + 1][M + 1];
        Queue<Cdnt> q = new LinkedList<>();
        int value = map[dice.row][dice.col];
        int cnt = 1;
        q.add(new Cdnt(dice.row, dice.col));
        visited[dice.row][dice.col] = true;

        while (!q.isEmpty()) {
            Cdnt now = q.poll();

            for (int i = 0; i < 4; i++) {
                int newRow = now.row + d_row[i];
                int newCol = now.col + d_col[i];

                if (IsOutBound(newRow, newCol) || visited[newRow][newCol] || map[newRow][newCol] != value) {
                    continue;
                }

                cnt++;
                q.add(new Cdnt(newRow, newCol));
                visited[newRow][newCol] = true;
            }
        }

        scoreSum += cnt * value;
    }

    private static boolean IsOutBound(int row, int col) {
        return row < 1 || row > N || col < 1 || col > M;
    }
}
