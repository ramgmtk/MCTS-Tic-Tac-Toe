import java.util.Scanner;

class MCTS {
    public static void main(String[] args) {
        /*state s1 = new state();
        state s2 = new state();
        System.out.println("Hello World.");
        System.out.println(state.compareStates(s1, s2));
        s2.turn_player = false;
        System.out.println(state.compareStates(s1, s2));
        s1.print();
        s1.setSpace(new spot(1, 1));
        s1.print();
        state s3 = new state(s1);
        s3.print();*/
        game g = new game();
        Scanner sc = new Scanner(System.in);
        System.out.println("X or O? (0 or non-zero): ");
        String line = sc.nextLine();
        int choice = Integer.parseInt(line);
        boolean pChoice;
        if (choice == 0) pChoice = false;
        else pChoice = true;
        g.startGame(pChoice, sc);
        sc.close();
        
    }
}
