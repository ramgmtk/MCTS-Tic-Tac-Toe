import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
//credit from user Greg Case https://stackoverflow.com/questions/363681/how-do-i-generate-random-integers-within-a-specific-range-in-java
import java.util.concurrent.ThreadLocalRandom;

public class montecarlo {
    public static final int num_nodes = 100;
    public static boolean identity;
    public static spot think(state s) {
        montecarlo.identity = s.turn_player;
        spot best_move = new spot(state.dimension, state.dimension);
        int most_visits = 0;
        state currS = new state(s);
        double win_rate = 0;
        mcts_node root = new mcts_node(new spot(0, 0), currS, null);
        //do mcts
        for (int i = 0; i < montecarlo.num_nodes; i++) {
            mcts_node curr_node = root;
            //traverse
            mcts_node leaf = montecarlo.traverse(curr_node);
            mcts_node new_node = null;
            //expand
            if (leaf != null) new_node = montecarlo.expandLeaf(leaf);
            if (new_node != null) {
                int result = montecarlo.rollout(new_node.my_state);
                montecarlo.backpropogate(new_node, result);
            }

        }
        for (Map.Entry<Integer, mcts_node> entry : root.children.entrySet()) {
            double c_win_rate = (double)entry.getValue().wins / entry.getValue().visits;
            if (c_win_rate > win_rate) {
                win_rate = c_win_rate;
                best_move = spot.intToSpot(entry.getKey());
            }
            if (most_visits < entry.getValue().visits) {
                if (best_move.row == state.dimension && best_move.col == state.dimension) {
                    best_move = spot.intToSpot(entry.getKey());
                }
                most_visits = entry.getValue().visits;
            }
        }
        return best_move;
    }

    private static void backpropogate(mcts_node curr, int result) {
        if (curr == null) return;
        curr.wins += result;
        curr.visits += 1;
        montecarlo.backpropogate(curr.parent, result);
    }

    private static mcts_node traverse(mcts_node node) {
        //credd to user peter Lawrey https://stackoverflow.com/questions/12952024/how-to-implement-infinity-in-java
        double current_ucbt = Double.NEGATIVE_INFINITY;
        boolean opponents_turn = false;
        if (node.untried_actions.size() == 0) {
            mcts_node best_child = null;
            if (node.children.isEmpty()) return best_child;
            if (node.my_state.turn_player != montecarlo.identity) opponents_turn = true;
            //credit to user scarcher2 https://stackoverflow.com/questions/46898/how-do-i-efficiently-iterate-over-each-entry-in-a-java-map
            for (Map.Entry<Integer, mcts_node> entry : node.children.entrySet()) {
                double child_ucbt = montecarlo.upperConfidenceBound(entry.getValue(), node, opponents_turn);
                if (current_ucbt < child_ucbt) {
                    current_ucbt = child_ucbt;
                    best_child = entry.getValue();
                }
            }
            node = montecarlo.traverse(best_child);
        }
        return node;
    }

    private static mcts_node expandLeaf(mcts_node parent) {
        int index = ThreadLocalRandom.current().nextInt(0, parent.untried_actions.size());
        spot move = spot.intToSpot(parent.untried_actions.get(index));
        parent.untried_actions.remove(index);
        state s = new state(parent.my_state);
        s.setSpace(move);
        mcts_node child = new mcts_node(move, s, parent);
        parent.children.put(spot.spotToInt(move), child);
        return child;
    }

    private static int rollout(state s) {
        state new_state = new state(s);
        while (!new_state.isOver()) {
            int index = ThreadLocalRandom.current().nextInt(0, new_state.remaining_spots);
            spot move = spot.intToSpot(new_state.remaining_spots_array[index]);
            new_state.setSpace(move);
        }
        if (new_state.checkWinner() && !new_state.turn_player == montecarlo.identity) return 1;
        return 0;
    }

    private static double upperConfidenceBound(mcts_node child, mcts_node parent, boolean opponents_turn) {
        int w = child.wins;
        int si = child.visits;
        int sp = parent.visits;
        double win_rate = (double)w / si;
        if (opponents_turn) win_rate = 1.0 - win_rate;
        double ucbt = win_rate + (2.0 * Math.sqrt(Math.log(sp)/si));
        return ucbt;
    }
}

class mcts_node {
    state my_state;
    mcts_node parent;
    spot parent_action;
    ArrayList<Integer> untried_actions;
    Map<Integer, mcts_node> children;
    //
    int wins;
    int visits;

    public mcts_node(spot sp, state s, mcts_node p) {
        this.my_state = new state(s);
        this.parent = p;
        this.parent_action = sp;
        this.untried_actions = this.my_state.availableMoves();
        this.children = new HashMap<Integer, mcts_node>();
        this.wins = 0; 
        this.visits = 0;
    }
}
