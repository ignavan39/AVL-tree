//
// Created by necrobuther on 14.04.2020.
//

#include "AVLTree.h"

dictionary::dictionary() {
    root = nullptr;
    __size = 0;
}

dictionary::dictionary(dictionary &&other) noexcept {
    __size = other.__size;
    std::swap(root, other.root);

}

dictionary::dictionary( dictionary &other) {
    copy(root, other.root);
    __size = other.__size;
}

void dictionary::copy(Node *pNode, Node *__copy) {
    if (!__copy) {
        return;
    }
    pNode = new Node(__copy->word, __copy->balance, __copy->frequency);
    copy(pNode->left, __copy->left);
    copy(pNode->right, __copy->right);
}

dictionary &dictionary::operator=(const dictionary &other) {
    if (this == &other) {
        return *this;
    }
    deleteTree(root);
    root = nullptr;
    __size = other.__size;
    copy(root, other.root);
}

dictionary &dictionary::operator=(dictionary &&other) noexcept {
    __size = other.__size;
    std::swap(root, other.root);
    other.deleteTree(other.root);
    return *this;
}

void dictionary::deleteTree(Node *pNode) {
    if (!pNode) {
        return;
    }
    deleteTree(pNode->left);
    deleteTree(pNode->right);
    delete pNode;
}

int dictionary::find(const std::string& findWord, Node *pNode) {
    if (!pNode) { return 0; }
    if (pNode->word == findWord) {
        return pNode->frequency;
    }
    if (pNode->word.compare(findWord) > 0) {
        return find(findWord,pNode->left);
    }
    if (pNode->word.compare(findWord) < 0) {
        return find(findWord,pNode->right);
    }
}

int dictionary::find(const std::string& findWord) {
    return find(findWord,root);
}

void dictionary::insert(const std::string& word) {
    insert(word,root);
    __size++;
}

bool dictionary::insert(const std::string& _word, Node *&pNode) {
    if (!pNode) {
        pNode = new Node(_word);
        return true;
    }
    if (pNode->word == _word) {
        pNode->frequency++;
        return false;
    }
    if (pNode->word.compare(_word) > 0) {
        if (insert( _word,pNode->left)) {
            return balanceAddLeft(pNode);
        }
        return false;
    }
    if (pNode->word.compare(_word) < 0) {
        if (insert(_word,pNode->right)) {
            return balanceAddRight(pNode);
        }
        return false;
    }
    return false;
}

bool dictionary::balanceAddLeft(Node *&pNode) {
    switch (pNode->balance)
    {
        case 1:
            pNode->balance = 0;
            return false;
        case 0:
            pNode->balance = -1;
            return true;
        case -1:
            Node *__pNode = pNode->left;
            if (__pNode->balance < 0) {
                RRotation(pNode, __pNode);
                return false;
            }
            else {
                LRRotation(pNode, __pNode);
                return false;
            }
    }
}

bool dictionary::balanceAddRight(Node *&pNode) {
    switch (pNode->balance)
    {
        case 0:
            pNode->balance = 1;
            return true;
        case -1:
            pNode->balance = 0;
            return false;
        case 1:
            Node *__pNode = pNode->right;
            if (__pNode->balance < 0) {
                RLRotation(pNode, __pNode);
                return false;
            }
            else {
                LRotation(pNode,__pNode);
                return false;
            }
    }
}

void dictionary::RRotation(Node *&pNode, Node *&pNode1) {
    if (!pNode->right || pNode1->right) {
        pNode->balance = pNode1->balance = 0;
    }
    else {
        pNode1->balance = 1;
        pNode->balance = -1;
    }
    pNode->left = pNode1->right;
    pNode1->right = pNode;
    pNode = pNode1;
}

void dictionary::LRRotation(Node *&pNode, Node *&pNode1) {
    Node* p = pNode1->right;
    if (p->balance > 0) {
        pNode->balance = p->balance = 0;
        pNode1->balance = -1;
    }
    else {
        if (p->balance == 0) {
            pNode->balance = p->balance = pNode1->balance = 0;
        }
        else {
            pNode->balance = 1;
            pNode1->balance = p->balance = 0;
        }
    }
    pNode->left = p->right;
    pNode1->right = p->left;
    p->left = pNode1;
    p->right = pNode;
    pNode = p;
}

void dictionary::RLRotation(Node *&pNode, Node *&pNode1) {
    Node* p = pNode1->left;
    if (p->balance > 0) {
        pNode1->balance = p->balance = 0;
        pNode->balance = -1;
    }
    else {
        if (p->balance == 0) {
            pNode->balance = p->balance = pNode1->balance = 0;
        }
        else {
            pNode1->balance = 1;
            pNode->balance = p->balance = 0;
        }
    }
    pNode->right = p->left;
    pNode1->left = p->right;
    p->left = pNode;
    p->right = pNode1;
    pNode = p;
}

void dictionary::LRotation(Node *&pNode, Node *&pNode1) {
    if (!pNode1->left || pNode->left) {
        pNode1->balance = pNode->balance = 0;
    }
    else {
        pNode->balance = 1;
        pNode1->balance = -1;
    }
    pNode->right = pNode1->left;
    pNode1->left = pNode;
    pNode = pNode1;
}

int dictionary::size() {
    return __size;
}

void dictionary::print(std::ostream & os, Node *pN, int level) const {
    if (!pN) {
        return;
    }
    for (int i = 0; i < level*2; i++) {
        os <<"   ";
    }
    os << pN->word <<"  "<< std::endl;
    print(os, pN->left, level + 1);
    print(os, pN->right, level + 1);
}

std::ostream &operator<<(std::ostream &os, const dictionary &rhs) {

    rhs.print(os , rhs.root ,1);
    return os;
}

void dictionary::remove(const std::string& word) {
    __size--;
    remove(word,root);

}

bool dictionary::remove(const std::string& word, Node *&pNode) {
    if (!pNode) {
        return false;
    }
    if (pNode->word.compare(word) > 0) {
        if (remove(word,pNode->left)) {
            return balanceDelLeft(pNode);
        }
        return false;
    }
    if (pNode->word.compare(word) < 0) {
        if (remove(word,pNode->right)) {
            return balanceDelRight(pNode);
        }
        return false;
    }
    Node* pDel = pNode;
    if (pNode->frequency > 1) {
        pNode->frequency--;
    }
    else {
        if (!pNode->right) {
            pNode = pNode->left;
            delete pDel;
            return true;
        }
        if (!pNode->left) {
            pNode = pNode->right;
            delete pDel;
            return true;
        }
        if (_del(pNode->left, pDel)) {
            delete pDel;
            return balanceDelLeft(pNode);
        }
        return false;
    }
}

bool dictionary::_del(Node *&left, Node *&del) {
    if (left->right) {
        if (_del(left->right,del)) {
            return balanceDelRight(left);
        }
        return false;
    }
    del->word = left->word;
    del = left;
    left = left->left;
    return true;
}

bool dictionary::balanceDelLeft(Node *&p) {
    switch (p->balance)
    {
        case 0:
            p->balance = 1;
            return false;
        case -1:
            p->balance = 0;
            return true;
        case 1:
            Node *pB = p->right;
            if (pB->balance < 0) {
                RLRotation(p, pB);
                return true;
            }
            else {
                LRotation(p, pB);
                return p->left->right == nullptr;
            }
    }
}

bool dictionary::balanceDelRight(Node *&p) {
    switch (p->balance)
    {
        case 0:
            p->balance = -1;
            return false;
        case 1:
            p->balance = 0;
            return true;
        case -1:
            Node *pB = p->left;
            if (pB->balance <= 0) {
                RRotation(p, pB);
                return p->right->left == nullptr;
            }
            else {
                LRRotation(p, pB);
                return true;
            }
    }
}

dictionary::~dictionary() {
    deleteTree(root);
    __size = 0;
}




