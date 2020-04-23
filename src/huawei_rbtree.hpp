namespace huawei {
    enum RBTColor{RED, BLACK};

    template <class T>
    class RBTNode {
    public:
        T key; // key
        RBTColor color; // color
        RBTNode *left; // left child
        RBTNode *right; // right child
        RBTNode *parent; // parent
        RBTNode(
            T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r
        ): key(value),color(c),parent(),left(l),right(r) {}
    };
    
    template <class T>
    class RBTree {
    private:
        RBTNode<T> *mRoot; // root node
    public:
        RBTree();
        ~RBTree();
        
        // pre-order traversal
        void preOrder();
        // in-order traversal
        void inOrder();
        // post-order traversal
        void postOrder();
        
        // search for key
        RBTNode<T>* search(T key);
        
        // search for min key
        T minimum();
        // search for max key
        T maximum();

        // find successor of node x
        RBTNode<T>* successor(RBTNode<T> *x);
        // find predecessor of node x
        RBTNode<T>* predecessor(RBTNode<T> *x);

        // insert node
        void insert(T key);

        // remove node
        void remove(T key);

        // destory rbtree
        void destroy();
        
        // print rbtree
        void print();
    
    private:
        // pre-order traversal
        void preOrder(RBTNode<T>* tree) const;
        // in-order traversal
        void inOrder(RBTNode<T>* tree) const;
        // post-order traversal
        void postOrder(RBTNode<T>* tree) const;

        // search for key
        RBTNode<T>* search(RBTNode<T>* x, T key) const;

        // search for min key
        RBTNode<T>* minimum(RBTNode<T>* tree);
        // search for max key
        RBTNode<T>* maximum(RBTNode<T>* tree);

        // left rotate
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
        // right rotate
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
        // insert node
        void insert(RBTNode<T>* &root, RBTNode<T>* node);
        // final adjust after insert
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
        // remove node
        void remove(RBTNode<T>* &root, RBTNode<T> *node);
        // final adjust after remove
        void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

        // destory rbtree
        void destroy(RBTNode<T>* &tree);

        // print rbtree
        void print(RBTNode<T>* tree, T key, int direction);

    #define rb_parent(r) ((r)->parent)
    #define rb_color(r) ((r)->color)
    #define rb_is_red(r) ((r)->color==RED)
    #define rb_is_black(r) ((r)->color==BLACK)
    #define rb_set_black(r) do { (r)->color = BLACK; } while (0)
    #define rb_set_red(r) do { (r)->color = RED; } while (0)
    #define rb_set_parent(r,p) do { (r)->parent = (p); } while (0)
    #define rb_set_color(r,c) do { (r)->color = (c); } while (0)
    };
}
