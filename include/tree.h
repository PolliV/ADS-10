// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <iostream>
#include <vector>
#include <algorithm>

class Tree {
 private:
  struct Node {
    char value;
    std::vector<Node*> child;
  };
  Node* root = nullptr;
  std::vector<std::vector<char>> permutations;
  Node* Create(Node* root, std::vector<char> permutations) {
        if (!root) {
            root = new Node;
        }
        if (permutations.empty()) {
            return root;
        }
        for (int i = 0; i < permutations.size(); i++) {
            std::vector<char> v = permutations;
            Node* copy = new Node;
            copy->value = permutations[i];
            root->child.push_back(copy);
            v.erase(v.begin() + i);
            Create(root->child[i], v);
        }
        return root;
  }
  std::vector<char> PermutationsTree(Node* root, std::vector<char>* symbl) {
      for (int i = 0; i < root->child.size(); i++) {
          symbl->push_back(root->child[i]->value);
          if (root->child[i]->child.empty()) {
            return *symbl;
          }
          PermutationsTree(root->child[i], symbl);
          if (symbl->size() != 1) {
            permutations.push_back(*symbl);
          }
          for (int j = 0; j< symbl->size(); j++) {
            symbl->pop_back();
          }
      }
      return *symbl;
  }

 public:
    std::vector<char> func(int i) const {
        if (permutations.size() < i) return std::vector<char>();
        return permutations[i];
    }
    explicit Tree(std::vector<char> child): root(nullptr) {
        root = Create(root, child);
        std::vector<char> symbl;
        PermutationsTree(root, &symbl);
    }
};

#endif  // INCLUDE_TREE_H_
