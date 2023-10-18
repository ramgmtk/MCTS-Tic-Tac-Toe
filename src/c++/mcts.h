#ifndef MCTS_H
#define MCTS_H
#include "board.h"

const unsigned int NUM_NODES = 10;
//class used to facilitate monet carlo tree search for the tic tac to bot
class mcts_node {
    private:
        board_state* my_state;
        mcts_node* parent;
        spot parent_action;
        std::vector<spot> untried_actions;
        std::unordered_map<int, mcts_node*> children;
        bool my_identity;
        //update on backpropogation
        int wins;
        int visits;
        //backpropogation function
        static void backpropogate(mcts_node*);
    public:
        mcts_node();
        mcts_node(spot s, bool i, board_state b, mcts_node* p = nullptr);
        mcts_node(const mcts_node&) = delete;
        mcts_node& operator= (const mcts_node&) = delete;
        //facilitates selection, expansion, simulation, backpropogation
        static spot think(board_state*);
        //identity of the bot as a whole
        static bool identity;
        ~mcts_node();  
};
#endif