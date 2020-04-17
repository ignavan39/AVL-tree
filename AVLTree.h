#include <utility>

//
// Created by necrobuther on 14.04.2020.
//

#ifndef TASK6_AVLTREE_H
#define TASK6_AVLTREE_H


struct Node {
    std::string word;
    unsigned frequency;
    int balance;
    Node *right, *left;

    explicit Node (
            std::string word,
            unsigned frequency = 1,
            int balance = 0,
            Node *right = nullptr,
            Node *left = nullptr):
    word{std::move(word)},
    frequency{frequency},
    balance{balance},
    right{right},
    left{left}{};
};

class dictionary
{
public:
    dictionary();
    dictionary(dictionary && other) noexcept ;
    dictionary(dictionary& other);
    dictionary&operator=(const dictionary& other);
    dictionary&operator=(dictionary&& other)noexcept ;
    ~dictionary();
    int find(const std::string& findWord);
    void insert(const std::string& word);
    void remove(const std::string& word);
    int size();

    friend std::ostream&operator<<(std::ostream& os,const dictionary& rhs);


private:
    Node* root{};
    int __size{};
    void deleteTree(Node* pNode);
    void copy(Node *&pNode, Node *pNode1);
    int find(const std::string& findWord , Node * pNode);
    bool insert(const std::string&, Node*& pNode);

    bool remove(const std::string& word,Node*& pNode);
    bool _del(Node*& left,Node*& del);

    bool balanceAddLeft(Node *&pNode);
    bool balanceAddRight(Node *&pNode);
    void RRotation(Node *&pNode, Node *&pNode1);
    void LRRotation(Node *&pNode, Node *&pNode1);
    void RLRotation(Node *&pNode, Node *&Node1);
    void LRotation(Node *&pNode, Node *&pNode1);

    void print(std::ostream& , Node* pN , int level) const;

    bool balanceDelLeft(Node *&pNode);

    bool balanceDelRight(Node *&pNode);
};

#endif //TASK6_AVLTREE_H
