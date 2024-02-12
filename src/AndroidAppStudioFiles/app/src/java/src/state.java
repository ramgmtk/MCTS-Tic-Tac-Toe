package src;

import java.util.*;

class state {
    public static final int dimension;
    public static ArrayList<ArrayList<Integer>> neighbors;
    public static Map<Boolean, Character> turn_player_symbol;
    public static final char empty_symbol = '#';
    char[][] board;
    boolean turn_player;
    int remaining_spots;
    int[] remaining_spots_array;
    //initialize the neighbors
    static {
        dimension = 3;
        turn_player_symbol = new HashMap<Boolean, Character>();
        turn_player_symbol.put(true, 'O');
        turn_player_symbol.put(false, 'X');
        neighbors = new ArrayList<ArrayList<Integer>>(9);
        for (int i = 0; i < 9; i++) {
            neighbors.add(new ArrayList<Integer>());
        }
        neighbors.set(0, new ArrayList<>(Arrays.asList(4, 1, 3)));
        neighbors.set(1, new ArrayList<>(Arrays.asList(4, 0, 2)));
        neighbors.set(2, new ArrayList<>(Arrays.asList(4, 1, 5)));
        neighbors.set(3, new ArrayList<>(Arrays.asList(4, 0, 6)));
        neighbors.set(4, new ArrayList<>(Arrays.asList(0, 1, 2, 3, 4, 5, 6, 7, 8)));
        neighbors.set(5, new ArrayList<>(Arrays.asList(4, 2, 8)));
        neighbors.set(6, new ArrayList<>(Arrays.asList(4, 3, 7)));
        neighbors.set(7, new ArrayList<>(Arrays.asList(4, 6, 8)));
        neighbors.set(8, new ArrayList<>(Arrays.asList(4, 5, 7)));
        //System.out.println(Arrays.toString(neighbors.get(0).toArray()));
    }
    //constructors
    public state() {
        this(false);
    }

    public state(boolean b) {
        this.board = new char[state.dimension][state.dimension];
        this.turn_player = b;
        this.remaining_spots = state.dimension * state.dimension;
        this.remaining_spots_array = new int[state.dimension * state.dimension];
        for (int i = 0; i < state.dimension; i++) {
            for (int j = 0; j < state.dimension; j++) {
                this.board[i][j] = state.empty_symbol;
                this.remaining_spots_array[i * state.dimension + j] = i * state.dimension + j;
            }
        }
    }

    public state(state s) {
        this.board = new char[state.dimension][state.dimension];
        this.turn_player = s.turn_player;
        this.remaining_spots = s.remaining_spots;
        this.remaining_spots_array = new int[state.dimension * state.dimension];
        for (int i = 0; i < state.dimension; i++) {
            for (int j = 0; j < state.dimension; j++) {
                this.board[i][j] = s.board[i][j];
                this.remaining_spots_array[i * state.dimension + j] = s.remaining_spots_array[i * state.dimension + j];
            }
        }

    }
    
    //check if spot is okay for placement
    public boolean checkSpot(spot s) {
        if (s.row >= state.dimension | s.col >= state.dimension) {
            return false;
        } else if (this.board[s.row][s.col] != state.empty_symbol) {
            return false;
        } else {
            return true;
        }
    }

    //places an element in this spot and updates the turn player
    //assumed good input
    public void setSpace(spot s) {
        this.board[s.row][s.col] = state.turn_player_symbol.get(turn_player);
        int si = spot.spotToInt(s);
        for (int i = 0; i < remaining_spots; i++) {
            if (si == this.remaining_spots_array[i]) {
                this.remaining_spots_array[i] = this.remaining_spots_array[this.remaining_spots - 1];
                break;
            }
        }
        this.remaining_spots -= 1;
        this.turn_player = !this.turn_player;
    }

    //check the winner brute force
    //would be more efficient to see the last move and check along the lines of that last move.
    public boolean checkWinner() {
        char c = this.board[1][1];
        if (c != '#') {
            if (c == this.board[1][2] && c == this.board[1][0]) return true;
            if (c == this.board[0][1] && c == this.board[2][1]) return true;
            if (c == this.board[0][0] && c == this.board[2][2]) return true;
            if (c == this.board[0][2] && c == this.board[2][0]) return true;
        }
        c = this.board[0][0];
        if (c != '#') {
            if (c == this.board[0][1] && c == this.board[0][2]) return true;
            if (c == this.board[1][0] && c == this.board[2][0]) return true;
        }
        c = this.board[2][2];
        if (c != '#') {
            if (c == this.board[2][1] && c == this.board[2][0]) return true;
            if (c == this.board[1][2] && c == this.board[0][2]) return true;
        }
        return false;
    }

    //return a list of the available spots on the board
    public ArrayList<Integer> availableMoves() {
        ArrayList<Integer> moves = new ArrayList<Integer>(this.remaining_spots);
        if (!this.checkWinner()) {
            for (int i = 0; i < remaining_spots; i++) {
                moves.add(-1);
            }
            for (int i = 0; i < remaining_spots; i++) {
                moves.set(i, this.remaining_spots_array[i]);
            }
        }
        return moves;
    }

    //check if game over
    public boolean isOver() {
        if (this.remaining_spots == 0 || this.checkWinner()) return true;
        return false;
    }

    //output state for debugging
    public void print() {
        System.out.println("Turn Player:" + state.turn_player_symbol.get(this.turn_player));
        for (int i = 0; i < state.dimension; i++) {
            for (int j = 0; j < state.dimension; j++) {
                System.out.print(this.board[i][j]);
            }
            System.out.println();
        }
    }

    //operator==
    public static boolean compareStates(state lhs, state rhs) {
        if (lhs.turn_player != rhs.turn_player) return false;
        for (int i = 0; i < state.dimension; i++) {
            for (int j = 0; j < state.dimension; j++) {
                if (lhs.board[i][j] != rhs.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }


}

//class to denote integer pair
class spot {
    int row;
    int col;
    public spot(int r, int c) {
        row = r;
        col = c;
    }

    public static int spotToInt(spot s) {
        return s.row * state.dimension + s.col;
    }
    public static spot intToSpot(int i) {
        int r = i / state.dimension;
        int c = i % state.dimension;
        return new spot(r, c);
    }
}
