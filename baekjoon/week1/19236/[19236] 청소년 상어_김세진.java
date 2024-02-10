package baekjoon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.StringTokenizer;

public class prob19236 {
    // 좌표 클래스
    static class xy {
        int x;
        int y;

        xy(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    // 물고기 클래스
    static class Fish extends xy {
        boolean alive;
        int num;
        int direction;

        public Fish(int x, int y, boolean alive, int num, int direction) {
            super(x, y);
            this.alive = alive;
            this.num = num;
            this.direction = direction;
        }

        // 물고기 복사 메서드 (deep copy)
        public Fish FishCopy() {
            return new Fish(this.x, this.y, this.alive, this.num, this.direction);
        }
    }

    static int[] d_row = { -1, -1, 0, 1, 1, 1, 0, -1 };
    static int[] d_col = { 0, -1, -1, -1, 0, 1, 1, 1 };
    static ArrayList<Fish> fishList = new ArrayList<>();
    static int ans = 0;
    static Fish initFish;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        for (int i = 0; i < 4; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            for (int j = 0; j < 4; j++) {
                int num = Integer.parseInt(st.nextToken());
                int direction = Integer.parseInt(st.nextToken());
                Fish fish = new Fish(i, j, true, num, direction - 1);

                // 초기 위치 물고기
                if (i == 0 && j == 0) {
                    initFish = fish;
                }

                fishList.add(fish);
            }
        }
        // 물고기 번호 순 정렬
        fishList.sort(new Comparator<Fish>() {
            @Override
            public int compare(Fish o1, Fish o2) {
                return o1.num - o2.num;
            }
        });

        initFish.alive = false;
        // 백트래킹
        BackTracking(new xy(0, 0), initFish.direction, initFish.num, fishList);
        // 출력
        System.out.println(ans);
    }

    private static void BackTracking(xy sharkPos, int sharkDirection, int eatenFishCnt, List<Fish> nowFishList) {
        // 물고기 리스트 복사
        List<Fish> CopyFishList = MoveFishes(sharkPos, nowFishList);

        // 먹을 수 있는 물고기 탐색 
        Queue<Fish> TargetFishQueue = SearchPossibleEatFish(sharkPos, sharkDirection, CopyFishList);

        // 먹을 수 있는 물고기가 없다면 분기 종료 (기저조건)
        if (TargetFishQueue.isEmpty()) {
            ans = Math.max(ans, eatenFishCnt);
            return;
        }

        // 백트래킹 (유도부분)
        while (!TargetFishQueue.isEmpty()) {
            Fish targetFish = TargetFishQueue.poll();

            targetFish.alive = false;
            BackTracking(new xy(targetFish.x, targetFish.y), targetFish.direction, targetFish.num + eatenFishCnt,
                    CopyFishList);
            targetFish.alive = true;
        }
    }

    // 먹을 수 있는 물고기 탐색 메서드
    private static Queue<Fish> SearchPossibleEatFish(xy sharkPos, int sharkDirection, List<Fish> copyFishList) {
        Queue<Fish> ret = new LinkedList<>();
        int newSharkX = sharkPos.x + d_row[sharkDirection];
        int newSharkY = sharkPos.y + d_col[sharkDirection];

        while (!IsOutBound(newSharkX, newSharkY)) {
            for (Fish fish : copyFishList) {
                if (newSharkX == fish.x && newSharkY == fish.y && fish.alive) {
                    ret.add(fish);
                    break;
                }
            }
            newSharkX += d_row[sharkDirection];
            newSharkY += d_col[sharkDirection];
        }

        return ret;
    }

    // 물고기 이동 메서드 (이동된 결과를 반환)
    private static List<Fish> MoveFishes(xy sharkPos, List<Fish> nowFishList) {
        // 물고기 리스트 복사
        List<Fish> CopyFishList = new ArrayList<>();
        for (Fish fish : nowFishList) {
            CopyFishList.add(fish.FishCopy());
        }

        for (Fish fish : CopyFishList) {
            if (!fish.alive) {
                continue;
            }

            // 살아있다면 이동
            for (int j = 0; j < 8; j++) {
                int direction = (fish.direction + j) % 8;
                int newFishX = fish.x + d_row[direction];
                int newFishY = fish.y + d_col[direction];

                // 해당 방향이 이동 가능하다면 이동
                if (IsPossibleFishMove(newFishX, newFishY, sharkPos)) {
                    fish.direction = direction;
                    for (Fish newFish : CopyFishList) {
                        if (newFish.x == newFishX && newFish.y == newFishY) {
                            int tmpX = fish.x;
                            int tmpY = fish.y;
                            fish.x = newFishX;
                            fish.y = newFishY;
                            newFish.x = tmpX;
                            newFish.y = tmpY;
                            break;
                        }
                    }

                    break;
                }
            }
        }

        return CopyFishList;
    }

    // 물고기 이동가능 여부
    private static boolean IsPossibleFishMove(int newFishX, int newFishY, xy sharkPos) {
        return !IsOutBound(newFishX, newFishY) && (newFishX != sharkPos.x || newFishY != sharkPos.y);
    }

    private static boolean IsOutBound(int x, int y) {
        return x < 0 || x >= 4 || y < 0 || y >= 4;
    }
}
