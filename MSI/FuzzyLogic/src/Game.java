import java.util.Random;

import static java.lang.Math.abs;

public class Game {
    public static final int EMPTY = 0;
    public static final int BLOCK = 1;
    public static final int CAR = 2;

    private final int x;
    private final int y;

    private int carX;

    private boolean gameLost;

    private Random random;
    private final int blockProbability;

    private int[][] board;

    public Game(int x, int y, int blockProbability, int carX) {
        this.x = x;
        this.y = y;
        this.board = new int[x][y];
        this.blockProbability = blockProbability;
        this.carX = carX;
        this.board[carX][0] = CAR;
        this.gameLost = false;
        this.random = new Random();
    }

    public void draw() {
        // Clear screen
        System.out.print("\033[H\033[2J");
        System.out.flush();

        //Draw board
        for(int j = x + 1; j > 0; --j) {
            System.out.print('-');
        }
        System.out.println();
        for(int j = y - 1; j >= 0; --j) {
            System.out.print('|');
            for(int i = 0; i < x; ++i) {
                switch(board[i][j]) {
                    case EMPTY:
                        System.out.print(' ');
                        break;
                    case CAR:
                        System.out.print('^');
                        break;
                    case BLOCK:
                        System.out.print('#');
                        break;
                }
            }
            System.out.println('|');
        }
        for(int j = x + 1; j > 0; --j) {
            System.out.print('-');
        }
        System.out.println();
    }

    public void update(int move) {
        if(move == 1) {
            if(carX != y - 1) {
                if(board[carX + 1][0] == BLOCK) {
                    gameLost = true;
                } else {
                    board[carX][0] = EMPTY;
                    board[carX + 1][0] = CAR;
                    carX++;
                }
            }
        } else if(move == -1) {
            if(carX != 0) {
                if(board[carX - 1][0] == BLOCK) {
                    gameLost = true;
                } else {
                    board[carX][0] = EMPTY;
                    board[carX - 1][0] = CAR;
                    carX--;
                }
            }
        }

        for(int i = 0; i < x; ++i) {
            for(int j = 1; j < y; ++j) {
                if(board[i][j-1] == CAR) {
                    if(board[i][j] == BLOCK) {
                        gameLost = true;
                    }
                } else {
                    board[i][j-1] = board[i][j];
                }
            }
        }

        for(int i = 0; i < x; ++i) {
            if((abs(random.nextInt()) % 100) < blockProbability)
                board[i][y-1] = BLOCK;
            else
                board[i][y-1] = EMPTY;
        }
    }

    public boolean isLost() {
        return gameLost;
    }

    public int getFrontDistance() {
        int i;
        for(i = 1; i < y; ++i) {
            if(board[carX][i] == BLOCK) break;
        }
        return i;
    }
    public int getLeftDistance() {
        if(carX == 0) return 0;
        int i;
        for(i = 0; i < y; ++i) {
            if(board[carX - 1][i] == BLOCK) break;
        }
        return i;
    }
    public int getRightDistance() {
        if(carX == y - 1) return 0;
        int i;
        for(i = 0; i < y; ++i) {
            if(board[carX + 1][i] == BLOCK) break;
        }
        return i;
    }
    public int getFarLeftDistance() {
        if(carX < 2) return 0;
        int i;
        for(i = 0; i < y; ++i) {
            if(board[carX - 2][i] == BLOCK) break;
        }
        return i;
    }
    public int getFarRightDistance() {
        if(carX > y - 3) return 0;
        int i;
        for(i = 0; i < y; ++i) {
            if(board[carX + 2][i] == BLOCK) break;
        }
        return i;
    }
}
