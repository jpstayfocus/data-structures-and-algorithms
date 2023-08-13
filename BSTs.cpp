#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };


template <typename Comparable>
class AvlTree
{
public:
    AvlTree() : root(NULL)
    { }
    AvlTree(const AvlTree& rhs) : root(NULL)
    {
        *this = rhs;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable& findMin() const
    {
        if (isEmpty())
            throw UnderflowException();
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable& findMax() const
    {
        if (isEmpty())
            throw UnderflowException();
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable& x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            std::cout << "Empty tree" << std::endl;
        else
            printTree(root);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable& x)
    {
        insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable& x)
    {
        std::cout << "Sorry, remove unimplemented; " << x <<
            " still present" << std::endl;
    }

    /**
     * Deep copy.
     */
    const AvlTree& operator=(const AvlTree& rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

private:
    struct AvlNode
    {
        Comparable element;
        AvlNode* left;
        AvlNode* right;
        int       height;

        AvlNode(const Comparable& theElement, AvlNode* lt,
            AvlNode* rt, int h = 0)
            : element(theElement), left(lt), right(rt), height(h) { }
    };

    AvlNode* root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable& x, AvlNode*& t)
    {
        if (t == NULL)
            t = new AvlNode(x, NULL, NULL);
        else if (x < t->element)
        {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
                if (x < t->left->element)
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
        }
        else if (t->element < x)
        {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
                if (t->right->element < x)
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
        }
        else
            ;  // Duplicate; do nothing
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode* findMin(AvlNode* t) const
    {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode* findMax(AvlNode* t) const
    {
        if (t != NULL)
            while (t->right != NULL)
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable& x, AvlNode* t) const
    {
        if (t == NULL)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true;    // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, AvlNode *t ) const
        {
            while( t != NULL )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match

            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode*& t)
    {
        if (t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(AvlNode* t) const
    {
        if (t != NULL)
        {
            printTree(t->left);
            std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode* clone(AvlNode* t) const
    {
        if (t == NULL)
            return NULL;
        else
            return new AvlNode(t->element, clone(t->left), clone(t->right), t->height);
    }
    // Avl manipulations
/**
 * Return the height of node t or -1 if NULL.
 */
    int height(AvlNode* t) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode*& k2)
    {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode*& k1)
    {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode*& k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode*& k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};











template<typename Comparable>
class BinarySearchTree
{

public:
    BinarySearchTree() 
        : root{nullptr}
    {
       
    }
    
    BinarySearchTree(const BinarySearchTree& rhs)
    {
        root = clone(rhs.root); 
    }

    ~BinarySearchTree()
    {
        makeEmpty(root); 
    }

    const Comparable& findMin()const
    {
        return findMin(root)->element;
    }

    const Comparable& findMax()const
    {
        return findMax(root)->element;
    }

    bool contains(const Comparable& x)const
    {
        return contains(x, root);
    }

    void insert(const Comparable& x)
    {
        insert(x, root);
    }

    void remove(const Comparable& x)
    {
        remove(x, root); 
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{theElement}, left{lt}, right{rt}{}
        BinaryNode(const Comparable&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } {}
    };

    BinaryNode* root; 

    BinaryNode* clone(BinaryNode* t)const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{ t->element, clone(t->left), clone(t->right) }; 
    }

    bool contains(const Comparable& x, BinaryNode* t)const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else return true; //found
    }

    BinaryNode* findMin(BinaryNode* t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    BinaryNode* findMax(BinaryNode* t)const
    {
        if (t == nullptr)
            return nullptr;
        if (t->right == nullptr)
            return t;
        return findMin(t->right);
    }

    void insert(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
            t = new BinaryNode(x, nullptr, nullptr);
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else; // duplicate, do nothing
    }

    void insert(Comparable&& x, BinaryNode*& t)
    {
        if (t == nullptr)
            t = new BinaryNode{ std::move(x),nullptr, nullptr };
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else //duplicate, do nothing
            ;
    }

    void remove(const Comparable& x, BinaryNode*& t)
    {
        if (t == nullptr)
            return;
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right; 
            delete oldNode; 
        }
    }

    void makeEmpty(BinaryNode*& t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

};


int main()
{


    BinarySearchTree<int> bst;
    AvlTree<int> avl;
    std::map<int, int> map;
    
    std::clock_t start;
    double duration;
    int n = 1000000;
    start = std::clock();
    for (int i = 0; i < n; ++i)
        avl.insert(rand()%100);
        //map[i] = i; 
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "time: " << duration << '\n';
     
}
