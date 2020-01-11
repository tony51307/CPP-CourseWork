// Develop the C++ class TwoThreeTree, which implements a 2-3 tree. You must include function to search, insert and delete.
// Input command :
// 1. insert <number> : Insert number to tree.
// 2. print : Print tree.
// Note: all numbers are bigger than 0.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
private:
	Node * parent = NULL;
	int number[2] = { 0 };
	Node * child[3] = { NULL };
public:
	Node();
	Node(int insertNumber);
	Node(Node* p, int insertNumber);

	void SetParent(Node* p);
	Node* GetParent();

	void SetChild(int child_index, Node* c);
	Node* GetChild(int child_index);

	void SetNumber(int number_index, int n);
	int GetNumber(int number_index);

	bool IsEmpty();
	bool IsLeaf();
	int GetSibNumber();
};

Node::Node() {}

Node::Node(int insertNumber) {
	number[0] = insertNumber;
}

Node::Node(Node* p, int insertNumber) {
	parent = p;
	number[0] = insertNumber;
}

void Node::SetParent(Node* p) {
	parent = p;
}
Node* Node::GetParent() {
	return parent;
}

void Node::SetChild(int child_index, Node* c) {
	child[child_index] = c;
	if (c != NULL) {
		c->parent = this;
	}
}
Node* Node::GetChild(int child_index) {
	if (child[child_index] == NULL) {
		child[child_index] = new Node();
		child[child_index]->SetParent(this);
	}
	return child[child_index];
}

void Node::SetNumber(int number_index, int n) {
	number[number_index] = n;
}
int Node::GetNumber(int number_index) {
	return number[number_index];
}

bool Node::IsEmpty() {
	return number[0] == 0 && number[1] == 0;
}
bool Node::IsLeaf() {
	return child[0] == NULL && child[1] == NULL && child[2] == NULL;
}

int Node::GetSibNumber() {
	for (int i = 0; i < 3; i++) {
		if (this->GetParent() != NULL) {
			if (this == this->GetParent()->GetChild(i)) return i;
		}
	}
	return -1;
}

class TwoThreeTree {
private:
	Node * root;
public:
	TwoThreeTree();
	void Insert(int insertNumber);
	void Print();
};

TwoThreeTree::TwoThreeTree() {
	root = new Node();
}

void TwoThreeTree::Insert(int insertNumber) {
	Node *tempNode = root;

while (!tempNode->IsLeaf()) {
		if (insertNumber < tempNode->GetNumber(0)) {
			tempNode = tempNode->GetChild(0);
		}
		else if (insertNumber > tempNode->GetNumber(0) && insertNumber < tempNode->GetNumber(1)) {
			tempNode = tempNode->GetChild(1);
		}
		else if ((insertNumber > tempNode->GetNumber(0) && tempNode->GetNumber(1) == 0) || (insertNumber > tempNode->GetNumber(1) && tempNode->GetNumber(1) != 0)) {
			tempNode = tempNode->GetChild(2);
		}
	}

	if (tempNode->GetNumber(0) == 0) {
		tempNode->SetNumber(0, insertNumber);
	}
	else if (tempNode->GetNumber(0) != 0 && tempNode->GetNumber(1) == 0) {
		if (insertNumber > tempNode->GetNumber(0)) {
			tempNode->SetNumber(1, insertNumber);
		}
		else {
			tempNode->SetNumber(1, tempNode->GetNumber(0));
			tempNode->SetNumber(0, insertNumber);
		}
	}
	else if (tempNode->GetNumber(0) != 0 && tempNode->GetNumber(1) != 0) {
		if (tempNode->GetParent() == NULL || tempNode->GetParent()->GetNumber(0) != 0 && tempNode->GetParent()->GetNumber(1) == 0) {
			int sortNumber[3] = { tempNode->GetNumber(0), insertNumber, tempNode->GetNumber(1) };
			if (tempNode->GetNumber(0) > insertNumber) {
				sortNumber[0] = insertNumber;
				sortNumber[1] = tempNode->GetNumber(0);
			}
			else if (tempNode->GetNumber(1) < insertNumber) {
				sortNumber[1] = tempNode->GetNumber(1);
				sortNumber[2] = insertNumber;
			}

			Node* leftNode = new Node(sortNumber[0]);
			Node* rightNode = new Node(sortNumber[2]);
			
			tempNode->SetChild(0, leftNode);
			tempNode->SetChild(2, rightNode);
			tempNode->SetNumber(1, 0);
			tempNode->SetNumber(0, sortNumber[1]);
		}
		else {
			while (tempNode->GetParent() != NULL && tempNode->GetParent()->GetNumber(0) != 0 && tempNode->GetParent()->GetNumber(1) != 0) {
				int sibNumber = tempNode->GetSibNumber();
				int sortNumber[3] = { tempNode->GetNumber(0), insertNumber, tempNode->GetNumber(1) };
				if (tempNode->GetNumber(0) > insertNumber) {
					sortNumber[0] = insertNumber;
					sortNumber[1] = tempNode->GetNumber(0);
				}
				else if (tempNode->GetNumber(1) < insertNumber) {
					sortNumber[1] = tempNode->GetNumber(1);
					sortNumber[2] = insertNumber;
				}
				
				if (sibNumber == 0) {
					Node* leftNode = new Node(sortNumber[1]);
					leftNode->GetChild(0)->SetNumber(0, sortNumber[0]);
					leftNode->GetChild(2)->SetNumber(0, sortNumber[2]);

					Node* rightNode = new Node(tempNode->GetParent()->GetNumber(1));
					rightNode->SetChild(0, tempNode->GetParent()->GetChild(1));
					rightNode->SetChild(2, tempNode->GetParent()->GetChild(2));

					tempNode = tempNode->GetParent();
					tempNode->SetChild(0, leftNode);
					tempNode->SetChild(1, NULL);
					tempNode->SetChild(2, rightNode);

					tempNode->SetNumber(1, 0);
				}
				else if (sibNumber == 1) {
					Node* leftNode = new Node(tempNode->GetParent()->GetNumber(0));
					leftNode->SetChild(0, tempNode->GetParent()->GetChild(0));
					leftNode->GetChild(2)->SetNumber(0, sortNumber[0]);

					Node* rightNode = new Node(tempNode->GetParent()->GetNumber(1));
					rightNode->GetChild(0)->SetNumber(0, sortNumber[2]);
					rightNode->SetChild(2, tempNode->GetParent()->GetChild(2));

					tempNode = tempNode->GetParent();
					tempNode->SetChild(0, leftNode);
					tempNode->SetChild(2, rightNode);
					tempNode->SetChild(1, NULL);
					tempNode->SetNumber(0, sortNumber[1]);
					tempNode->SetNumber(1, 0);
				}
				else if (sibNumber == 2) {
					Node* leftNode = new Node(tempNode->GetParent()->GetNumber(0));
					leftNode->SetChild(0, tempNode->GetParent()->GetChild(0));
					leftNode->SetChild(2, tempNode->GetParent()->GetChild(1));

					Node* rightNode = new Node(sortNumber[1]);
					rightNode->GetChild(0)->SetNumber(0, sortNumber[0]);
					rightNode->GetChild(2)->SetNumber(0, sortNumber[2]);

					tempNode = tempNode->GetParent();
					tempNode->SetChild(0, leftNode);
					tempNode->SetChild(1, NULL);
					tempNode->SetChild(2, rightNode);

					tempNode->SetNumber(0, tempNode->GetNumber(1));
					tempNode->SetNumber(1, 0);
				}
			}
		}
		// 看現在是左分支還是右分支(代表parent != NULL)，將現在的Node合併上去
		int sibNumber = tempNode->GetSibNumber();
		if (sibNumber == 0) {
			tempNode->GetParent()->SetNumber(1, tempNode->GetParent()->GetNumber(0));
			tempNode->GetParent()->SetNumber(0, tempNode->GetNumber(0));
			tempNode->GetParent()->SetChild(1, tempNode->GetChild(2));
			tempNode->GetParent()->SetChild(0, tempNode->GetChild(0));
		}
		else if (sibNumber == 2) {
			tempNode->GetParent()->SetNumber(1, tempNode->GetNumber(0));
			tempNode->GetParent()->SetChild(1, tempNode->GetChild(0));
			tempNode->GetParent()->SetChild(2, tempNode->GetChild(2));
		}
	}
}

void TwoThreeTree::Print() {
	vector<vector<int>> tempNumber = vector<vector<int>>();
	vector<vector<Node>> tempNodes = vector<vector<Node>>();
	tempNodes.push_back(vector<Node>());
	tempNodes[0].push_back(*this->root);
	int depth = 0;
	while (true) {
		tempNodes.push_back(vector<Node>());
		int emptyAmount = 0;

		for (int i = 0; i < tempNodes[depth].size(); i++) {
			for (int j = 0; j < 3; j++) {
				Node tempChild = *tempNodes[depth][i].GetChild(j);
				if (!tempChild.IsEmpty()) {
					tempNodes[int(depth + 1)].push_back(tempChild);
				}
				else {
					emptyAmount++;
				}
			}
		}
		if (emptyAmount == tempNodes[depth].size() * 3) {
			break;
		}

		depth += 1;
	}
	for (int i = 0; i < tempNodes.size(); i++) {
		for (int j = 0; j < tempNodes[i].size(); j++) {
			if (tempNodes[i][j].GetNumber(0) != 0) {
				cout << tempNodes[i][j].GetNumber(0);
			}
			if (tempNodes[i][j].GetNumber(1) != 0) {
				cout << " " << tempNodes[i][j].GetNumber(1);
			}
			if (j != tempNodes[i].size() - 1) {
				cout << " / ";
			}
		}
		if (i != tempNodes.size() - 1) {
			cout << endl;
		}
	}
}

int main(void) {
	TwoThreeTree tree;
	string cmd;
	while (cin >> cmd) {
		if (cmd == "insert") {
			int number = 0;
			cin >> number;
			tree.Insert(number);
		}
		else if (cmd == "delete") {
			int number = 0;
			cin >> number;
			tree.Insert(number);
		}
		else if (cmd == "print") {
			tree.Print();
		}
		else {
			cout << cmd << " not system cmd" << endl;
		}
	}
	return 0;
}
