#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <fstream>
#include <string>
using namespace std;

class BST {

	struct node {
		int data; //поле данных
		node* left; //указатель на левый потомок 
		node* right; //указатель на правый потомок 
	};
	node* root;
	int m = 0;
	int flag = 0;
	int result = 0;

	void makeEmpty(node* t)
	{
		if (t->left)
		{
			makeEmpty(t->left);
		}
		if (t->right)
		{
			makeEmpty(t->right);
		}
		delete t;
	}

	//добавление узла в бинарное дерево
	node* insert(int x, node* t)
	{
		if (t == NULL)
		{
			t = new node;
			t->data = x;
			t->left = t->right = NULL;
		}
		else if (x < t->data)
			t->left = insert(x, t->left);
		else if (x > t->data)
			t->right = insert(x, t->right);
		return t;
	}

	//печать бинарного дерева в виде дерева повернутого на -90 градусов
	void print_tree(node* t, int l) {
		if (t == NULL)
			return;
		print_tree(t->right, l + 1);
		for (int i = 0; i < l; ++i)
			cout << "\t";
		cout << t->data << endl;
		print_tree(t->left, l + 1);
	}

	void obhod(node* t, node* tree2, int l) {
		if (t == NULL)
			return;
		if (flag != 1)
		{
			if (tree2->data != t->data)
			{
				m++;
				obhod(t->right, tree2, l + 1);
				obhod(t->left, tree2, l + 1);
			}
			else
			{
				flag = 1;

			}
		}
		if (tree2->data == t->data)
		{
			obhod(t->right, tree2->right, l + 1);
			for (int i = 0; i < l; ++i)
				cout << "\t";
			obhod(t->left, tree2->left, l + 1);
			result++;
		}

	}

public:

	BST() {
		root = NULL;
	}

	~BST() {
		makeEmpty(root);
		root = nullptr;
	}

	//добавление узла в бинарное дерево.
	void insert(int x) {
		root = insert(x, root);
	}

	//печать бинарного дерева в виде дерева повернутого на -90 градусов
	void display_tree() {
		cout << endl << endl;
		print_tree(root, 0);
		cout << endl << endl;
	}

	void search(node* tree2, int* kol, int* level)
	{
		obhod(root, tree2, 0);
		*kol = result;
		*level = m;
		result = 0;
		m = 0;
	}

	node* getter()
	{
		return root;
	}

};

int main()
{
	setlocale(LC_ALL, "rus");

	BST tree;
	BST tree2;

	string line;
	ifstream in("D:\\input.dat"); // окрываем файл для чтения
	int number = 0;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			cout << "\n Содержимое файла input.dat:\n " << line << endl;
		}
	}
	in.close(); // закрываем файл
	int n = line.size() + 1;
	char* str = new char[n];
	strcpy(str, line.c_str());
	char boof[10] = " ";
	char clean[2] = " ";
	int i;
	int count = 0;
	for (i = 0; str[i] != '@'; i++)
	{
		for (int j = 0; str[i] != ' '; i++, j++)
		{
			boof[j] = str[i];
		}
		tree.insert(atoi(boof));
		strcpy(boof, clean);
	}
	i += 2;
	for (i; str[i] != '\0'; i++)
	{
		for (int j = 0; str[i] != ' '; i++, j++)
		{
			boof[j] = str[i];
		}
		tree2.insert(atoi(boof));
		count++;
		strcpy(boof, clean);
	}

	cout << "\n\n\n Первое дерево: " << endl;
	tree.display_tree();
	cout << "\n Второе дерево: " << endl;
	tree2.display_tree();
	int level = 0;
	int kol = 0;
	tree.search(tree2.getter(), &kol, &level);
	cout << "\n Результат записан в output.dat!\n\n\n\n";
	if (count == kol)
	{
		line = "True! Уровень корня второго дерева в первом: ";
		line += to_string(level);
	}
	else {
		line = "False!";
	}
	std::ofstream out;          // поток для записи
	out.open("D:\\output.dat"); // окрываем файл для записи
	if (out.is_open())
	{
		out << line;
	}
	out.close();
	return 0;
}

