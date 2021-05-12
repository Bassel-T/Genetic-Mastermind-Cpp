#include <vector>
#include <stdlib.h> // rand()

using namespace std;

// Contains the guesses
class Node {
    public:

    // The guess and its resulting score
    vector<int> Data;
    int Score;

    // Default constructor
    Node() {
        for (int i = 0; i < 4; i++) {
            Data.push_back(rand() % 10);
        }
    }

    // Detailed constructor
    Node(vector<int> _data) {
        Data = _data;
    }

    // Generate child with other node
    Node* Recombination(Node* other){
        // Random place to splice each
        int splice = rand() % (Data.size() - 2) + 1;

        vector<int> newData;

        // Bring front part of this
        for (int i = 0; i < splice; i++) {
            newData.push_back(Data[i]);
        }

        // Bring back half of other
        for (int i = splice; i < 4; i++) {
            newData.push_back(other->Data[i]);
        }

        return new Node(newData);
    }

    // Randomly mutate a single digit in the guess
    void Mutate() {
        int location = rand() % Data.size();
        Data[location] = (rand() % 10);
    }

    // Calculate the score compared to the goal
    void SetScore(Node* goal) {
        // Prevents double counting
        vector<bool> used1;
        vector<bool> used2;

        Score = 0;

        // Check for right digit, right place
        for (int i = 0; i < 4; i++) {
            if (Data[i] == goal->Data[i]) {
                Score += 5;
                used1.push_back(true);
                used2.push_back(true);
            } else {
                used1.push_back(false);
                used2.push_back(false);
            }
        }

        // Check for right digit, wrong place
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                // Already matched somewhere else
                if (used1[i]) {break;}

                // RDWP can't come from the same place
                if (i == j) {
                    continue;
                }

                // Already matched some where else
                if (used2[j]) {
                    continue;
                }

                // Increment if match
                if (Data[i] == goal->Data[j]) {
                    Score++;
                    used1[i] = true;
                    used2[j] = true;
                }
            }
        }
    }

    // Combine digits into one number
    int Hash() {
        int hash = 0;
        for (int i = 0; i < 4; i++) {
            hash *= 10;
            hash += Data[i];
        }

        return hash;
    }

    // Check if two nodes are equal based on Hash
    bool Eq(Node* other) {
        return Hash() == other->Hash();
    }

};