#include "mcts.h"
#include <math.h>
#include <time.h>
//static varaible
bool mcts_node::identity = false;
//constructor
mcts_node::mcts_node(spot s, board_state b, mcts_node* p) {
    wins = 0;
    visits = 0;
    this->parent= p;
    this->parent_action = s;
    this->my_state = new board_state(b);
    this->untried_actions = board_state::available_moves(b);
}

//destructor
mcts_node::~mcts_node() {
    delete my_state;
    for (auto kv : children) {
        delete kv.second;
    }
}

//how the mcts happens
spot mcts_node::think(board_state* b) {
    mcts_node::identity = b->get_turn_player();
    srand(time(NULL));
    board_state currB (*b);
    spot best_move;
    int most_visits = 0;
    int win_rate = 0;
    mcts_node* root = new mcts_node(spot(0, 0), currB,nullptr);
    //DO MCTS
    for (int i = 0; i < NUM_NODES; i++) {
        mcts_node* curr = root;
        //traverse
        mcts_node* leaf = mcts_node::traverse(curr);
        mcts_node* new_node = nullptr;
        //expand iff we are not on end game board
        if (leaf != nullptr) new_node = mcts_node::expand_leaf(leaf);
        int result = mcts_node::rollout(*new_node->my_state);

        //rollout
        //backPropogate
    }
    
    delete root;
    return best_move;
}

//traverse out mcts tree to find the best child to expand at
mcts_node* mcts_node::traverse(mcts_node* parent) {
    mcts_node* node = parent;
    float current_ucbt = -1 * INFINITY;
    bool opponents_turn = false;
    if (node->untried_actions.empty()) {
        mcts_node* best_child = nullptr;
        if (node->children.empty()) return best_child;
        if (node->my_state->get_turn_player() != mcts_node::identity) opponents_turn = true;
        for (auto kv : node->children) {
            float child_ucbt = mcts_node::upper_confidence_bound(kv.second, node, opponents_turn);
            if (current_ucbt < child_ucbt) {
                current_ucbt = child_ucbt;
                best_child = kv.second;
            }
        }
        node = mcts_node::traverse(best_child);
    }
    return node;
} 
//expand a leaf node
mcts_node* mcts_node::expand_leaf(mcts_node* parent) {
    int index = rand() % parent->untried_actions.size();
    spot move = parent->untried_actions[index];
    parent->untried_actions.erase(parent->untried_actions.begin() + index);
    board_state b = *parent->my_state;
    b.set_space(move);
    mcts_node* child = new mcts_node(move, b, parent);
    parent->children.insert(std::make_pair(board_state::spot_to_uint(move), child));
    return child;
}

//rollouts strategy for finding end game state
int mcts_node::rollout(board_state b) {
    board_state new_state = b;
    while (board_state::is_over(new_state)) {
        int index = rand() % new_state.remaining_spots - 1;
        spot move = board_state::uint_to_spot(b.remaining_spots_array[index]);
        new_state.set_space(move);
    }
    if (new_state.check_winner && !new_state.get_turn_player() == mcts_node::identity) return 1;
    return 0;
}
//backporpogation
void mcts_node::backpropogate(mcts_node* curr, int result) {
    if  (curr->parent ==  nullptr) return;
    curr->wins += result;
    curr->visits += 1;
    mcts_node::backpropogate(curr->parent, result);
}

float mcts_node::upper_confidence_bound(mcts_node* child, mcts_node* parent, bool opponents_turn) {
    int w = child->wins;
    int si = child->visits;
    int sp = parent->visits;
    float win_rate = w / si;
    if (opponents_turn) win_rate = 1 - win_rate;
    float ucbt = win_rate + (2 * sqrt(log(sp) / si));
    return ucbt;
}