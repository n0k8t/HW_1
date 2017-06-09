/*#include <iostream>
#include <alloca.h>

template<
        class T
> class TList
{
public:
    class Iterator
    {
    public:
        Iterator();
        Iterator(const Iterator &iterator);

        Iterator& operator=(const Iterator &right);
        bool operator!=(const Iterator &right) const;
        bool operator==(const Iterator &right) const;

        T& operator*() const;
        T* operator->() const;

        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
    };
    class Const_Iterator
    {
    public:
        Const_Iterator();
        Const_Iterator(const Const_Iterator &iterator);

        Const_Iterator& operator=(const Const_Iterator &right);
        bool operator!=(const Const_Iterator &right) const;
        bool operator==(const Const_Iterator &right) const;

        const T& operator*() const;
        const T* operator->() const;

        Const_Iterator& operator++();
        Const_Iterator operator++(int);
        Const_Iterator& operator--();
        Const_Iterator operator--(int);
    };

    using value_type        = T;
    using size_type	        = size_t;
    using difference_type   = std::ptrdiff_t;
    using reference         = value_type&;
    using const_referenc    = const value_type&;
    using pointer           = Allocator::pointer;
    using const_pointer     = Allocator::const_pointer;
    using iterator          = Iterator;
    using const_iterator    = Const_Iterator;
private:

public:
    TList()
    {};

    virtual ~TList()
    {}

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    void swap(TList a);





};*/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <exception>

template <class Value>
struct MyList
{
    struct Node
    {
        Value val;
        Node *pNext, *pPrev;

        Node(Value v)
        {
            val = v;
        }

        Node()
        {}
    };

    struct iterator
    {
        Node *pNode;

        Value &operator*()
        {
            return pNode->val;
        }

        iterator(Node *p)
        {
            pNode = p;
        }

        iterator()
        {
            pNode = 0;
        }

        iterator &operator++()
        {
            pNode = pNode->pNext;
            return (*this);
        }

        /*iterator operator++ (int)
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        } *///постфиксный вариант

        iterator &operator-- ()
        {
            pNode = pNode->pPrev;
            return (*this);
        }    
            
        bool operator!=(iterator &Obj)
        {
            return *pNode != Obj.pNode;
        }

        bool operator==(iterator &Obj)
        {
            return *pNode == Obj.pNode;
        }
    };

    using value_type        = Value;
    using size_type         = size_t;
    using reference         = value_type&;

    // Data
    Node *pFirst;
    int len;;
    // ~

    MyList()
    {
        Node *pNode = new Node;
        pFirst = pNode->pNext = pNode->pPrev = pNode;
        len = 0;
    }

    iterator begin()
    {
        return iterator(pFirst->pNext);
    }

    iterator end()
    {
        return iterator(pFirst);
    }

    int size()
    {
        return len;
    }

    bool empty()
    {
        if (len == 0) {
            return true;
        } else {
            return false;
        }
    }

    void push_back(Value val)
    {
        Node *p = new Node(val);
        len++;
        p->pNext = pFirst;
        p->pPrev = pFirst->pPrev;
        pFirst->pPrev->pNext = p;
        pFirst->pPrev = p;
        delete p;
    }

    void push_front(Value val)
    {
        Node *p = new Node(val);
        p->pNext = pFirst->pNext;
        p->pPrev = pFirst;
        pFirst->pNext->pPrev = p;
        pFirst->pNext = p;
        delete p;
    }

    void pop_front()
    {
        if (len > 0) {
            Node *p = pFirst->pNext;
            p->pPrev->pNext = p->pNext;
            p->pNext->pPrev = p->pPrev;
            len--;
            delete p;
        }
    }

    void pop_back()
    {
        Node *p = pFirst->pPrev;
        p->pPrev->pNext = pFirst;
        pFirst->pPrev = p->pPrev;
        len--;
        delete p;
    }

    void clear()
    {
        while (len != 0)
        {
            pop_back();
        }
    }

    void resize(size_type num, const value_type &val = value_type())
    {
        if (num < 0)
            throw std::exception();

        if (num == len)
            return;

        if (!num)
            clear();

        if (len > num)
            while (len != num) pop_back();

        if (len < num)
            while (len != num) push_back(val);
    }

    reference front()
    {
        Value tmp = begin();
        return *tmp;
    }

    reference back()
    {
        Value tmp = end();
        --tmp;
        return *tmp;
    }

    void assign( size_type count, const Value& value )
    {
        if(!empty())
        {
            clear();
        }

        while(size() < count)
        {
            push_back(value);
        }
    }

    void sort()
    {
        Node *tmp = pFirst;
        while (tmp->pNext)
        {
            if (tmp->val > tmp->pNext->val)
            {
                std::swap(tmp->val, tmp->pNext->val);
                tmp = tmp->pNext;
                sort();
            }
            else
                tmp = tmp->pNext;
        }
    }

    void merge( MyList& other )
    {
        if(!this == &other)
        {
            MyList newList;
            newList.len = size()+other.size();
            if(this->pFirst->val < other.pFirst->val)
            {
                newList = *this;
                newList.push_back(other);
            }
            else
            {
                newList = other;
                newList.push_back(*this);
            }
            newList.sort();
            *this = newList;
        }
    }

    void swap( MyList& other )
    {
        std::swap(pFirst,other.pFirst);
    }
        
    iterator insert( iterator pos, const Value& value )
    {
        Node *tmp = new Node;
        tmp->pNext = pos.pNode->pNext;
        tmp->pPrev = pos.pNode;
        tmp->val = value;
        pos.pNode->pNext = tmp;
    }    
};
























