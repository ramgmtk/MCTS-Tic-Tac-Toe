import java.util.Scanner;

public class game {
    boolean player_choice;
    state my_board;
    public game() {
        my_board = new state();
        player_choice = true;
    }

    public void startGame(boolean player, Scanner sc) {
        while (this.my_board.remaining_spots > 0) {
            this.display();
            System.out.println("You are: " + state.turn_player_symbol.get(player));
            if (this.my_board.turn_player ==  player) { //player move
                this.playerTurn(sc);
                if (this.my_board.checkWinner()) break;
            } else { //cpu move
                this.cpuTurn();
                if (this.my_board.checkWinner()) break;
            }
        }
    }

    private void playerTurn(Scanner sc) {
        //code to get inpit
        boolean valid = false;
        System.out.println("Enter a number from [0-8]: ");
        while (!valid) {
            String line = sc.nextLine();
            int c = Integer.parseInt(line);
            spot choice = spot.intToSpot(c);
            if (this.my_board.checkSpot(choice)) {
                this.my_board.setSpace(choice);
                valid = true;
            }
            
        }
    }

    private void cpuTurn() {
        //spot choice = spot.intToSpot(this.my_board.remaining_spots_array[0]);
        //this.my_board.setSpace(choice);
        this.my_board.setSpace(montecarlo.think(this.my_board));
    }

    public void display() {
        this.my_board.print();
    }
}
