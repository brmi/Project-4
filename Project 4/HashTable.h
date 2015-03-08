//
//  HashTable.h
//  Project 4
//
//  Created by desiree on 3/5/15.
//  Copyright (c) 2015 desiree. All rights reserved.
//

#ifndef Project_4_HashTable_h
#define Project_4_HashTable_h

template <typename KeyType, typename ValueType>
class HashTable
{
public:
    HashTable(unsigned int numBuckets, unsigned int capacity);
    ~HashTable();
    bool isFull() const;
    bool set(const KeyType& key, const ValueType& value, bool permanent= false);
    bool get(const KeyType& key, ValueType& value) const;
    bool touch(const KeyType& key);
    bool discard(KeyType& key, ValueType& value);

private:
    
    struct Node
    {
        
//        ~Node()
//        {
//            std::cout<<"call's node destruct"<<std::endl;
//        }
        ValueType m_value;
        KeyType m_key;
        bool m_permanent;
        
        Node* next;
        Node* prev;
        
        Node* prevRecent;
        Node* nextRecent;

    };
    
    Node** m_bucket; //pointer to a pointer to a linked list
    unsigned int m_numBuckets;
    unsigned int m_maxcapacity;
    unsigned int currentCapacity;
    
    Node* tailRecent; //this will point to the most recent item added
    Node* headRecent;
    
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
};


template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int numBuckets, unsigned int capacity): m_numBuckets(numBuckets), m_maxcapacity(capacity), currentCapacity(0)
{
    tailRecent=nullptr;
    headRecent=nullptr;
    m_bucket=new Node *[numBuckets];
    
    for (int i=0; i<numBuckets; ++i)
        m_bucket[i]=nullptr;
    
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
    
//    for(int i=0; i<m_numBuckets; i++)
//    {
//        if(m_bucket[i]!=nullptr)
//        {
//            Node* current=m_bucket[i];
//            
//            if(current->next==nullptr)
//            {
//                delete current;
//                continue;
//            }else
//            while(current!=nullptr)
//            {
//                Node* nextNode=current -> next;
//                delete current;
//                current=nextNode;
//            }
//        }
//        m_bucket[i]=nullptr;
//    }
//    tailRecent=nullptr;
//    headRecent=nullptr;
//    delete [] m_bucket;
//    m_bucket=nullptr;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::isFull() const
{
    if(currentCapacity>=m_maxcapacity)
        return true;
    return false;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::set(const KeyType& key, const ValueType& value, bool permanent)
{
    
    unsigned int computeHash(KeyType);
    unsigned int index= computeHash(key);
    
    index= index%m_numBuckets;
    ValueType newValue= value;
    
    if(!get(key, newValue)) //if key is not in table
    {
        if(isFull())
            return false;
        
            if(m_bucket[index]!=nullptr) //if there is already a linked list in the bucket
            {
                Node* ptr=m_bucket[index]; //points to head of linked list
                while(ptr->next!=nullptr)
                {
                    ptr=ptr->next; //move to next node
                }

                currentCapacity++;
                Node* insertNode=new Node;
                ptr->next= insertNode;
                insertNode->prev=ptr;
                insertNode->next=nullptr;
                insertNode->m_key= key;
                insertNode->m_value=value;
                insertNode->m_permanent=permanent;
                if(insertNode->m_permanent==false)
                {
                    if(headRecent==nullptr) //this means that the one you are going to make most recent is the head!
                    {
                        headRecent= insertNode;
                        tailRecent=headRecent;
                        headRecent->prevRecent=nullptr;
                        headRecent->nextRecent=nullptr;
                        return true;
                    }else
                    {
                        Node* currentRecent=tailRecent;
                        tailRecent->nextRecent=insertNode;
                        tailRecent=insertNode;
                        tailRecent->nextRecent=nullptr;
                        tailRecent->prevRecent=currentRecent;
                    }
                }
                return true;
            }
        
            //if there is nothing in the bucket
            currentCapacity++;
            m_bucket[index]= new Node;
            m_bucket[index]->m_key=key;
            m_bucket[index]->m_value=value;
            m_bucket[index]->m_permanent=permanent;
            m_bucket[index]->next=nullptr;
            m_bucket[index]->prev=nullptr;
        
            if(m_bucket[index]->m_permanent==false)
            {
                if(headRecent==nullptr)
                {
                headRecent= m_bucket[index];
                tailRecent=headRecent;
                headRecent->prevRecent=nullptr;
                headRecent->nextRecent=nullptr;
                return true;
                }
                else
                {
                    Node* currentRecent=tailRecent;
                    tailRecent->nextRecent=m_bucket[index];
                    tailRecent=m_bucket[index];
                    tailRecent->nextRecent=nullptr;
                    tailRecent->prevRecent=currentRecent;
                    return true;
                }
            }
            return true;

    }else //if key is in table
    {
        Node* ptr=m_bucket[index]; //points to head of linked list
        while(ptr!=nullptr)
        {
            if(ptr->m_key==key)
            {
                ptr->m_value=value;
                if(ptr->m_permanent==false)
                {
                Node* currentRecent=tailRecent;
                tailRecent=ptr;
                tailRecent->nextRecent=nullptr;
                tailRecent->prevRecent=currentRecent;
                }
                return true;
            }
            ptr=ptr->next;
        }
    }
    return false;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::get(const KeyType& key, ValueType& value) const
{
    unsigned int computeHash(KeyType);
    unsigned int index=computeHash(key);
    index= index%m_numBuckets;
    
    if(m_bucket[index]==nullptr)
        return false;
    
    Node* ptr=m_bucket[index]; //points to head of linked list
    
    if(ptr->m_key==key) 
    {
        value=ptr->m_value;
        return true;
    }
    
    while(ptr->next!=nullptr)
    {
        if(ptr->m_key==key)
        {
            value=ptr->m_value;
            return true;
        }
        ptr=ptr->next;
    }

    return false;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::touch(const KeyType& key)
{
    unsigned int computeHash(KeyType);
    unsigned int index=computeHash(key);
    index= index%m_numBuckets;
    
    Node* ptr=m_bucket[index];
    while(ptr!=nullptr)
    {
        if(ptr->m_key==key && ptr->m_permanent==false)
        {
            //want to move that value to end of linked list and reconnect the other values
            if(ptr==headRecent) //if the item that has been touched is the head
            {
                Node* oldHead=headRecent;
                Node* newHead=headRecent->nextRecent;
                newHead->prevRecent=nullptr;
                headRecent=newHead;
                tailRecent->nextRecent=oldHead;
                oldHead->prevRecent= tailRecent;
                oldHead->nextRecent=nullptr;
                tailRecent=oldHead;
                return true;
            }
            
            Node* oldRecent=tailRecent;
            tailRecent->next=ptr;
            tailRecent=ptr;
            tailRecent->prevRecent=oldRecent;
            tailRecent->nextRecent=nullptr;
            return true;
        }
         ptr=ptr->next;
    }
     return false;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::discard(KeyType& key, ValueType& value)
{
  if(headRecent==nullptr) //recent list compromised of only permanent items
      return false;
    
    key=headRecent->m_key;
    value=headRecent->m_value;
    
    
    //delete from bucket
    unsigned int computeHash(KeyType);
    unsigned int index=computeHash(key);
    index= index%m_numBuckets;
    
    Node* ptr= m_bucket[index];
    if(ptr->next==nullptr) //if there is only one link in the list
    {
        ptr=nullptr;
        
    }else if(m_bucket[index]->m_key==key) //if you want to delete the head of the linked list
    {
        Node* nextNode=ptr->next;
        delete ptr;
        ptr=nextNode;
        ptr->prev=nullptr;
    }else //want to delete something later in linked list
    {
        while(ptr->m_key!=key)
        {
            ptr=ptr->next;
        }
        
        Node* previous= ptr->prev;
        previous->next=ptr->next;
        ptr->next->prev=previous;
        delete ptr;
        ptr=nullptr;
    }
    
    //delete from recent list
    
    if(headRecent->nextRecent==nullptr) //ie only one item in the recent list
    {
        delete headRecent;
        headRecent=nullptr;
        tailRecent=headRecent;
        return true;
    }
    
    Node* oldHead=headRecent;
    Node* newHead=headRecent->nextRecent;
    newHead->prevRecent=nullptr;
    headRecent=newHead;

    
    delete oldHead;
    --currentCapacity;
    
    return true;
}

inline
unsigned int computeHash(std::string s)
{
    //brmiu
     unsigned int hashValue=2166136261u;
    
    for(int i=0; i<s.size(); i++)
    {
        hashValue+=s[i];
        hashValue*=16777619;
    }
    return hashValue;
    return 1;
}

inline
unsigned int computeHash(unsigned short s)
{
    return (unsigned int) s;
}

#endif
