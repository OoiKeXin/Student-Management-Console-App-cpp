#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}


bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


//function (a): input validation
bool BST::searching(type item)
{
	if (root == NULL) return false;
	return searching2(root, item);
}


bool BST::searching2(BTNode* cur, type item)
{
	if (cur == NULL) return false;	// Base case: reached leaf node (not found)

	if (cur->item.compare2(item))	// Check if current node matches the item
		return true;

	if (cur->item.compare1(item))	// If item is less than current node, search left
		return searching2(cur->left, item);
	else
		return searching2(cur->right, item);	// Else, search right
}


//function (b): print Deepest Nodes
int BST::height(BTNode* root)
{
	if (root == NULL) return 0;

	int leftHeight = height(root->left);		// Calculate height of the leftsubtree and rightsubtree
	int rightHeight = height(root->right);

	return max(leftHeight, rightHeight) + 1;	// Fine max height between LR subtree and +1 for the current itself
}


void BST::printDeepestNodes(BTNode* cur, int level)
{
	if (cur == NULL) return;

	if (level == 1)
	{
		cout << cur->item.id << " ";	// Print ID of the node when reached the desired level
	}

	else if (level > 1)		// Recursive call fucntion
	{
		printDeepestNodes(cur->left, level - 1);
		printDeepestNodes(cur->right, level - 1);
	}
}


bool BST::deepestNodes()
{
	if (root == NULL) return false;

	int h = height(root);	// Cal height
	cout << endl;
	printDeepestNodes(root, h);	// print deepest node
	cout << endl;
	return true;
}


//function (c): display student's information
void BST::descendingOrderPrint(BTNode* cur) // print to screen DESC
{ 
	if (cur == NULL) return;

	descendingOrderPrint(cur->right);
	cur->item.print(cout);
	descendingOrderPrint(cur->left);
}


void BST::inOrderFile(BTNode* cur, ostream& outFile) // print to file ASC
{
	if (cur == NULL) return;

	inOrderFile(cur->left, outFile);
	cur->item.print(outFile);
	inOrderFile(cur->right, outFile);
	cout << endl;
}

void BST::descendingOrderFile(BTNode* cur, ostream& outFile) // print to file DESC
{
	if (cur == NULL) return;

	inOrderFile(cur->right, outFile);
	cur->item.print(outFile);
	inOrderFile(cur->left, outFile);
	cout << endl;
}


bool BST::display(int order, int source) 
{
	ofstream outFile;
	BTNode* cur = root;

	if (root == NULL)
		return false; // Return false for empty tree

	if (order == 1) // Ascending order
	{ 
		if (source == 1) 
		{
			inOrderPrint2(cur);
			return true;

		}
		else if (source == 2) 
		{
			if (!cur) return false;
			outFile.open("studentInfo.txt");

			if (!outFile.is_open()) 
			{
				cout << "Unable to print output to studentInfo.txt" << endl << endl;
				return false;
			}

			// Print to file
			inOrderFile(cur, outFile);

			cout << "Successfully print output to studentInfo.txt" << endl << endl;
			return true;
			outFile.close();
		}
	}
	else if (order == 2) // Descending order
	{ 
		if (source == 1) 
		{
			// Print to screen
			descendingOrderPrint(cur);
			return true;
		}
		else if (source == 2) 
		{
			if (!cur) return false;

			ofstream outFile;
			outFile.open("studentInfo.txt");

			if (!outFile.is_open()) 
			{
				cout << "Unable to print output to studentInfo.txt" << endl << endl;
				return false;
			}

			// Print to file
			descendingOrderFile(cur, outFile);

			cout << "Successfully print output to studentInfo.txt" << endl << endl;
			return true;
			outFile.close();
		}
	}
	return true;
}


//function (d): Clone Subtree
bool BST::CloneSubtree(BST t1, type item)
{
	if (t1.root == NULL) return false;		// special case

	BST t2;

	if (CloneSubTree2(t1.root, item, t2))
	{
		t2.preOrderPrint();
		return true;
	}

	else
		return false;
}

// Searching node
bool BST::CloneSubTree2(BTNode* cur, type item, BST& t2)
{
	if (cur == NULL) return false;	// special case

	if (cur->item.compare2(item))	// return cur node, if id match
	{
		CloneSubTree3(cur, t2);
		return true;
	}

	if (cur->item.compare1(item))
		return (CloneSubTree2(cur->left, item, t2));	// Search in left subtree
	else
		return(CloneSubTree2(cur->right, item, t2));	// Search in right subtree
}

// Clone the current node into t2
void BST::CloneSubTree3(BTNode* cur, BST& t2)
{
	if (cur == NULL) return;

	t2.insert(cur->item);	// insert node into t2

	// Recursively clone the left and right subtree
	CloneSubTree3(cur->left, t2);
	CloneSubTree3(cur->right, t2);
}


//function (e): print Level Nodes
bool BST::printLevelNodes()
{
	Queue q;
	int count = 1;
	if (root == NULL) return false;
	q.enqueue(root);
	printLevelNodes2(q);
	return true;
}


void BST::printLevelNodes2(Queue q)
{
	Queue w;
	BTNode* tmp;
	int counter = count = 1;
	while (counter > 0)
	{
		cout << endl;
		cout << "Level " << count++ << " : ";
		while (!q.empty())
		{
			q.dequeue(tmp);
			cout << tmp->item.id << "\t";
			counter--;
			w.enqueue(tmp);
		}

		while (!w.empty())
		{
			w.dequeue(tmp);
			if (tmp->left != NULL)
			{
				q.enqueue(tmp->left);
				counter++;
			}
			if (tmp->right != NULL)
			{
				q.enqueue(tmp->right);
				counter++;
			}
		}
		cout << endl;
	}
	return;
}


//function (f): print Path
bool BST::printPath()
{
	if (root == NULL)
		return false;
	printPath2(root);
	return true;
}


void BST::printPath2(BTNode* cur)
{
	if (cur == NULL) return;
	if (cur->left == NULL && cur->right == NULL)
	{
		cout << endl;
		printPath3(root, cur->item);
		cout << endl;
	}
	printPath2(cur->left);
	printPath2(cur->right);
}


void BST::printPath3(BTNode* cur, type item)
{
	if (cur == NULL) return;

	cout << cur->item.id << "\t";

	if (cur->item.compare2(item))
		return;

	if (cur->item.compare1(item))
		printPath3(cur->left, item);
	else
		printPath3(cur->right, item);
}