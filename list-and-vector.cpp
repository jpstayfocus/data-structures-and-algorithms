#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>

template <typename Object>
class Vector{
public:
    explicit Vector(int initSize = 0) :
        theSize(initSize), theCapacity{ initSize + SPARE_CAPACITY },
        objects{ new Object[theCapacity] }
    {}
    Vector(const Vector& rhs) :
        theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k]; 

    }
    Vector& operator=(const Vector& rhs)
    {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this; 
    }
    ~Vector()
    {
        delete[] objects;
    }
    Vector(Vector&& rhs):
        theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    
    }
    Vector& operator=(Vector&& rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(objects, rhs.objects);

        return *this;
    
    }
  
    Object& operator[](int index)
    {
        return objects[index];
    }
    const Object& operator[](int index) const
    {
        return objects[index]; 
    } 
    bool empty()const
    {
        return size() == 0;
    }
    int size()const
    {
        return theSize;
    }
    int capacity()const
    {
        return theCapacity;
    }
    void push_back(const Object& x)
    {
        if (theSize == theCapacity)
        {
            reserve(theCapacity*1.5 + 1);
        } 
        objects[theSize++] = x;
    }
    void push_back(Object&& x)
    {
        if (theSize == theCapacity)
            reserve(1.5 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }   
    void pop_back()
    {
        --theSize;
    }
    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
    }
    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        Object* newArray = new Object[newCapacity];
        for (int k = 0; k < theSize; ++k)
            newArray[k] = std::move(objects[k]); 

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray; 
    }


    typedef Object* iterator;
    typedef const Object* const_iterator;

    iterator begin()
    {
        return &objects[0];
    }
    const_iterator begin()const
    {
        return &objects[0];
    }
    iterator end() 
    {
        return &objects[size()];
    }
    const_iterator end() const
    {
        return &objects[size()];
    }
    
    static const int SPARE_CAPACITY = 16;

private:
    int theSize;
    int theCapacity;
    Object* objects;
};

/*
    list class itself - contains links to both ends, size, and many other methods
    concrete implementation of List ADT. different from vector because it allows
    us to add to middle of list in O(1) time, but does not support O(1) indexing[]
*/ 
template <typename Object>
class List {

private: 
    /*
        private nested Node class. contains data and pointers to prev/next
        along with appropriate constructor methods
        struct is a relic from C, essentially a class where members default to public
        used to signify a type that contains mostly data to be accessed directly rather
        than through methods
        Node is private, so only List will be able to access it's fields/methods
    */
    struct Node {
        Object data;
        Node* prev;
        Node* next;
        Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr) :
            data{ d }, prev{ p }, next{ n } {}
        Node(Object&& d, Node* p = nullptr, Node* n = nullptr) :
            data{ std::move(d) }, prev{ p }, next{ n }
     {}
    };

public:
    /*
        const_iterator class. abstracts notion of position, public nested class
        const_iterator stores pointer to current node and provides implementation of
        basic iterator operations, all in form of overloaded operators like =, ==, !=, ++     
    */
    class const_iterator {
    public:
        const_iterator():current{nullptr}{}
        
        const Object& operator*()const
        {
            return retrieve();
        }

        // returns a reference
        const_iterator& operator++()
        {
            current = current->next;
            return *this;
        }

        // returns a copy
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        /*
        public methods of const_iterator all use operator overloading. operator==,
        operator!=, operator* are straightforward. separate routines are necessary for
        prefix and postfix versions of operator++ due to their different semantics. we 
        distinguish between them by their method signatures (empty parameter for prefix,
        int parameter for postfix). int is only used to distinguish between them. 
        in many cases where there is a choice between using prefix or postfix, prefix
        version is faster.
        
        */
        bool operator==(const const_iterator& rhs)const
        {
            return current == rhs.current;
        }
        bool operator!=(const const_iterator& rhs)const
        {
            return !(*this == rhs); 
        }

        /*
        protected allows classes that inherit from const_iterator to access these fields
        but not other classes
        */
    protected:
        Node* current;

        Object& retrieve()const
        {
            return current->data;
        }
        const_iterator(Node* p) : current{ p }
        {
        }
        /*
        the friend declaration is needed to grant the List class access to const_iterators
            nonpublic members
        */
        friend class List<Object>;
    };
    /*
        iterator class. abstracts notion of position. public nested class
        same functionality as const_iterator, except operator* returns a reference
        to the item being viewed, rather than a const reference
        iterator can be used in any routine that requires a const_iterator, but not
        vice-versa (in other words, iterator IS A const_iterator)
        
        iterator inherits from const_iterator, meaning it inherits all the data and 
        methods from const_iterator. it can then add new methods and override existing
        methods. here we are not adding any new data or changing the behavior of exising
        methods. we do add some new methods (with similar signatures to const_iterator)
     */
    class iterator : public const_iterator 
        //inheritance: iterator has same functionality as const_iterator
        //iterator can be used wherever const_iterator is needed
    {
    public:
        iterator() {}

        /*
         do not have to re-implement operator == and operator != (inherited unchanged)
         provide a new pair of operator++ implementations that override the original
         implementations from const_iterator. 
         provide an accessor/mutator pair for operator*. 
        
        */
        Object& operator*()
        {
            return const_iterator::retrieve();
        }
        const Object& operator*()const
        {
            return const_iterator::operator*();
        }
        iterator& operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }
    protected:
        /*
        protected constructor uses an initialization list to initialize the inherited
        current node.
        */
        iterator(Node* p) :const_iterator{ p } {}
        friend class List<Object>;
    };

public:
    /*
        constructor and big 5. because zero-parameter constructor and copy constructor
        must both allocate the header and tail nodes, we provide a init routine.
        init creates an empty list.
        the destructor reclaims the header and tail nodes, all other nodes, all other 
        nodes are reclaimed when the destructor invokes clear. similarly, the 
        copy-constructor is implemented by invoking public methods rather than attempting
        low-level pointer manipulations. 
    */
    List()
    {
        init();
    } 
    /*
     sentinel nodes - makes sense to create an extra node at each end of list to
     represent start/end markers. also referred to as header and tail nodes
     advantage of sentinel nodes is that it simplifies code by removing special cases
     example: without sentinels, removing the first node becomes a special case
     because we must reset the list's link to the first node during the remove
     operation, and because the remove algorithm in general needs to access the node
     prior to the node being removed (and without header, first node does not have
     prior)

    */
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }

    // clear works by repeatedly removing items until the List is empty (uses pop-front)
    void clear()
    {
        while (!empty())
            pop_front();
    }


    List(const List& rhs)
    {
        init();
        for (auto& x : rhs)
        {
            push_back(x);
        }
    }
    List& operator=(const List& rhs)
    {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    List(List&& rhs)
        :theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    List& operator=(List&& rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }

    // these methods return iterators
    iterator begin()
    {
        return { head->next };
    }
    const_iterator begin()const
    {
        return{ head->next };
    }
    iterator end()
    {
        return { tail };
    }
    const_iterator end()const
    {
        return{ tail };
    }
    int size()const
    {
        return theSize;
    }
    bool empty()const
    {
        return size() == 0;
    }


    Object& front()
    {
        return *begin();
    }
    const Object& front()const
    {
        return *begin();
    }
    Object& back()
    {
        return *--end();
    }
    const Object& back() const
    {
        return *--end();
    }
    
    /*
    cleverly obtain and use appropriate iterator
    insert inserts prior to a position, so push_back inserts prior to the endmarker
    pop_back line erase(-end()) creates a temporary iterator corresponding to the
    endmarker, retreats the temporary iterator, and uses that iterator to erase. 
    similar behavior occurs in back
    note also that we avoid dealing with node reclamation in pop_front and pop_back
    */
    void push_front(const Object& x)
    {
        insert(begin(), x);
    }
    void push_front(Object&& x)
    {
        insert(begin(), std::move(x));
    }
    void push_back(const Object& x)
    {
        insert(end(), x);
    }
    void push_back(Object&& x)
    {
        insert(end(), std::move(x));
    }
    void pop_front()
    {
        erase(begin());
    }
    void pop_back()
    {
        erase(--end());
    }

    /*
    inserting a new node between p and p->prev. works by getting a new node
    and then changing pointers of p and p-prev in the correct order
    also mention usefulness of the sentinels here.
    */
    iterator insert(iterator itr, const Object& x)
    {
        Node* p = itr.current;
        theSize++;
        Node* newNode = new Node{ x, p->prev,p };
        p->prev->next = newNode;
        p->prev = newNode;
        return newNode;
    }
    iterator insert(iterator itr, Object&& x)
    {
        Node* p = itr.current;
        theSize++;
        p->prev->next = new Node{ std::move(x), p->prev, p };
        p->prev = p->prev->next;
        return p->prev;
    }
    /*
    erase routines. frst version erases p by rearranging pointers of the nodes just 
    before and after p, and then returning an iterator representing the item after the
    erased element. like insert, erase must also update the size.
     
    second version of erase simply uses an iterator to call the first version of erase,
    note - cannot simply use itr++ in 'for' loop and ignore return iterator from erase,
    because the value of itr is stale immediately after the call to erase, which is why
    erase returns an iterator.
    */
    iterator erase(iterator itr)
    {
        Node* p = itr.current;
        iterator retVal{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;

        return retVal;
    }
    iterator erase(iterator from, iterator to)
    {
        for (iterator itr = from; itr != to;)
        {
            itr = erase(itr);
        }
        return to;
    }

    /*
    data members for list - pointers to header and tail nodes. also keeps track of
    size in a data member so that the size method can be implemented in constant time
    */
    private:
        int theSize;
        Node* head;
        Node* tail;

    
};


int main()
{

    List<int> theList{};

    std::clock_t start;
    double duration;

    start = std::clock();

    for (int i = 0; i < 100000; i++)
        theList.push_front(i);

    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "linked list time: " << duration << '\n';

    std::vector<int> theVec{};
    start = std::clock();
    for (int i = 0; i < 100000; i++)
        theVec.insert(theVec.begin(), i);
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "vector time: " << duration << '\n';

}








