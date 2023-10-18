#include "mcts.h"
//static varaible
bool mcts_node::identity = false;
//constructor
mcts_node::mcts_node(spot s, bool i, board_state b, mcts_node* p) {
    wins = 0;
    visits = 0;
    this->parent= p;
    this->parent_action = s;
    this->my_identity = i;
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
    board_state currB (*b);
    spot best_move;
    int most_visits = 0;
    int win_rate = 0;
    mcts_node* root = new mcts_node(spot(0, 0), mcts_node::identity, currB,nullptr);
    //DO MCTS
    for (int i = 0; i < NUM_NODES; i++) {
        mcts_node* curr = root;
        //traverse
        //expand iff we are on end game board
        //rollout
        //backPropogate
    }
    
    delete root;
    return best_move;
}

//backporpogation
void mcts_node::backpropogate(mcts_node* curr) {
    if  (curr->parent ==  nullptr) return;
    curr->wins += 1;
    curr->visits += 1;
    mcts_node::backpropogate(curr->parent);
}