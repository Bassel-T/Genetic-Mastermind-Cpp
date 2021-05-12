#include <iostream>
#include <vector>
#include <queue>

#include "Node.h"

using namespace std;

// Compare the scores of two states
struct CompareCost {
    bool operator() (Node const *n1, Node const *n2) {
        return n1->Score < n2->Score;
    }
};

int main(int argc, char* argv[]) {

    // Invalid entry
    if (argc < 5) {
        cout << "Proper Usage: " << endl;
        cout << argv[0] << " [first digit] [second digit] [third digit] [fourth digit]" << endl;
        return 1;
    }

    // Set seed
    srand(time(NULL));

    // Generate Initial Node
    vector<int> targetData;

    for (int i = 1; i < 5; i++) {
        targetData.push_back(argv[i][0] - 48);
    }

    Node* target = new Node(targetData);

    // Parameters for the model
    int STATES = 100;
    int MUTATE_CHANCE = 3;
    int MAX_ITERS = 100000;
    int REPRODUCE_COUNT = 40;

    // Collections for nodes
    priority_queue<Node*, vector<Node*>, CompareCost> *states = new priority_queue<Node*, vector<Node*>, CompareCost>();
    queue<Node*> *newStates = new queue<Node*>();

    // Generate first generation
    for (int i = 0; i < STATES; i++) {
        Node* newState = new Node();
        newState->SetScore(target);
        states->push(newState);
    }

    int iter = 0;

    cout << "Generation " << iter << endl;
    cout << "Best State in Generation: " << states->top()->Hash() << endl << endl;

    while (!states->top()->Eq(target) && iter < MAX_ITERS) {
        
        // Generational information
        iter++;

        for (int i = 0; i <= REPRODUCE_COUNT; i += 2) {

            // Get top parents
            Node* first = states->top();
            states->pop();
            Node* second = states->top();
            states->pop();

            // Generate children with random mutate chance
            Node* child1 = first->Recombination(second);
            child1->SetScore(target);

            int value = rand() % 100;
            if (value < MUTATE_CHANCE) {
                child1->Mutate();
            }

            Node* child2 = second->Recombination(first);
            child2->SetScore(target);

            value = rand() % 100;
            if (value < MUTATE_CHANCE) {
                child2->Mutate();
            }

            // Add to temp storage
            newStates->push(child1);
            newStates->push(child2);

            delete first;
            delete second;
        }

        while (!states->empty()) {
            // Randomly mutate remaining "parents"

            int value = rand() % 100;
            if (value < MUTATE_CHANCE) {
                Node* top = states->top();
                top->Mutate();
                newStates->push(top);
            } else {
                newStates->push(states->top());
            }

            states->pop();
        }

        // Move new states from temporary storage to algo's storage
        while (!newStates->empty()) {
            states->push(newStates->front());
            newStates->pop();
        }

        cout << "Generation " << iter << endl;
        cout << "Best State in Generation: " << states->top()->Hash() << endl << endl;

    }

    // Output final
    if (states->top()->Eq(target)) {
        cout << "Success!" << endl;
    } else {
        cout << "Couldn't generated solution in " << MAX_ITERS << " steps." << endl;
    }

    // Prevent memory leaks
    while (!states->empty()) {
        delete states->top();
        states->pop();
    }

    delete states;
    delete newStates;

    return 0;
}