/*----Структура "Узел"----*/
struct Node
{
	Node* left;
	Node* right;
	int data;
	Node(Node* left, Node* right, int data) :
		left(left), right(right), data(data) {}
};

/*----Класс "Бинарное дерево поиска"----*/
class set
{
private: 
	Node* root;

	/*----Метод(приватный), осуществляющий вывод элементов по принципу ЛКП----*/
	void _print(const Node* node) const
	{
		if (!node) return;
		_print(node->left);
		std::cout << node->data << " ";
		_print(node->right);
	}

	/*----Метод(приватный), осуществляющий удаление ВСЕХ элементов дерева----*/
	void delete_all(const Node* node)
	{
		if (!node) return;
		if (node->left) delete_all(node->left);
		if (node->right) delete_all(node->right);
		delete node;
	}

	/*----Метод(приватный), осуществляющий удаление ОДНОГО элемента дерева----*/
	Node* delete_node(const int key, Node* node)
	{
		if (!node) return NULL;
		else if (key < node->data) node->left = delete_node(key, node->left);
		else if (key > node->data) node->right = delete_node(key, node->right);

		else
		{
			Node* tmp_node = node;
			if (!node->left || !node->right)
			{
				node = (!node->right) ? node->left : node->right;
				delete tmp_node;
			}
			else
			{
				tmp_node = node->left;
				while (tmp_node->right) tmp_node = tmp_node->right;
				node->data = tmp_node->data;
				node->left = delete_node(node->data, node->left);
			}
		}

		return node;
	}

	/*----Метод(приватный), осуществляющий глубокое копирование узлов----*/
	void copy_set(const Node* node, set& obj)
	{
		if (!node) return;
		obj.insert(node->data);
		copy_set(node->left, obj);
		copy_set(node->right, obj);
	}

public:
	/*----Конструктор копирования----*/
	set(const set& obj) : root(NULL) { if (obj.root) copy_set(obj.root, *this); }

	/*----конструктор по умолчанию----*/
	set(): root(NULL) {}

	/*----Оператор присваивания----*/
	void operator =(const set& obj)
	{
		delete_all(root);
		root = NULL;
		copy_set(obj.root, *this);
	}

	/*----Деструктор, осуществляющий полное зачищение дерева----*/
	~set()
	{
		delete_all(root);
		root = NULL;
	}

	/*----Метод, осуществляющий вывод элементов по принципу ЛКП----*/
	void print() const { _print(root); }

	/*----Метод, осуществляющий проверку наличия элемента----*/
	bool contains(const int key) const
	{
		Node* tmp_node = root;

		while (tmp_node)
		{
			if (key < tmp_node->data) tmp_node = tmp_node->left;
			else if (key > tmp_node->data) tmp_node = tmp_node->right;
			else return true;
		}

		return false;
	}

	/*----Метод, осуществляющий вставку элемента----*/
	bool insert(const int key)
	{
		Node* tmp_node = root;
		while (tmp_node)
		{
			if (key < tmp_node->data)
			{
				if(!tmp_node->left) return tmp_node->left = new Node(NULL, NULL, key);
				tmp_node = tmp_node->left;
			}
			else if (key > tmp_node->data)
			{
				if(!tmp_node->right) return tmp_node->right = new Node(NULL, NULL, key);
				tmp_node = tmp_node->right;
			}
			else return false;
		}
		return root = new Node(NULL, NULL, key);
	}

	/*Метод, осуществляющий удаление элемента KEY----*/
	bool erase(const int key)
	{
		if(!contains(key)) return false;
		root = delete_node(key, root);
		return true;
	}

	/*----Метод, возращающий указатель на корень дерева(НАРУШАЕТСЯ ЗАЩИЩЁННОСТЬ)----*/
	Node* get_root() const { return root; }
};
