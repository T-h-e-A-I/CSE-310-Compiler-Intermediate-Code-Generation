//
//  ScopeTable.h
//  Compiler
//
//  Created by Awesh Islam on 30/11/23.
//

#ifndef ScopeTable_h
#define ScopeTable_h
#include <string>
#include<iostream>
#include "2005054_SymbolInfo.h"

using namespace std;

class ScopeTable
{
private:
    int id;
    SymbolInfo **table;
    int size;
    ScopeTable *parentScope;
    int children;
    int offset = 0;
    public:
    
    ScopeTable(int id, int size)
    {
        this->id = id;
        this->size = size;
        this->parentScope = NULL;
        this->children = 0;
        table = new SymbolInfo*[size];
        for(int i=0; i<size; i++)
            table[i] = NULL;
        //cout<<"\t"<<"ScopeTable# "<<id<<" created"<<endl;
    }
    ~ScopeTable()
    {
        //cout<<"\t"<<"ScopeTable# "<<id<<" deleted"<<endl;
        for(int i=0; i<size; i++)
        {
            SymbolInfo *temp = table[i];
            while(temp != NULL)
            {
                SymbolInfo *del = temp;
                temp = temp->getNext();
                delete del;
            }
        }
        delete[] table;
    }
    static unsigned long long sdbm(const unsigned char *str)
    {
        unsigned long hash = 0;
        int c;

        while (c = *str++)
            hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
    }
    bool insert(string name, string type)
    {
        unsigned long long hash = sdbm((const unsigned char*)name.c_str());
        int index = hash%size;
        SymbolInfo *temp = table[index];
        SymbolInfo *newSymbol = new SymbolInfo(name, type);
        if(temp == NULL)
        {
            table[index] = newSymbol;
            //cout<<"\t"<<"Inserted  at position <"<<index+1<<", "<<1<<"> of ScopeTable# "<<id<<endl;
            return true;
        }
        else
        {
            int pos = 1;
            while(temp->getNext() != NULL)
            {
                if(temp->getName() == name)
                {
                    //cout<<"\t"<<name<<" already exists in the current ScopeTable"<<endl;
                    return false;
                }
                temp = temp->getNext();
                pos++;
            }
            if(temp->getName() == name)
            {
                //cout<<"\t"<<name<<" already exists in the current ScopeTable"<<endl;
                return false;
            }
            temp->setNext(newSymbol);
            //cout<<"\t"<<"Inserted  at position <"<<index+1<<", "<<pos+1<<"> of ScopeTable# "<<id<<endl;
            return true;
        }
    }
    bool insert(SymbolInfo *symbol)
    {
        string name = symbol->getName();
        string type = symbol->getType();
        unsigned long long hash = sdbm((const unsigned char*)name.c_str());
        int index = hash%size;
        SymbolInfo *temp = table[index];
        if(temp == NULL)
        {
            table[index] = symbol;
            //cout<<"\t"<<"Inserted  at position <"<<index+1<<", "<<1<<"> of ScopeTable# "<<id<<endl;
            return true;
        }
        else
        {
            int pos = 1;
            while(temp->getNext() != NULL)
            {
                if(temp->getName() == name)
                {
                   // cout<<"\t"<<name<<" already exists in the current ScopeTable"<<endl;
                    return false;
                }
                temp = temp->getNext();
                pos++;
            }
            if(temp->getName() == name)
            {
               // cout<<"\t"<<name<<" already exists in the current ScopeTable"<<endl;
                return false;
            }
            temp->setNext(symbol);
            //cout<<"\t"<<"Inserted  at position <"<<index+1<<", "<<pos+1<<"> of ScopeTable# "<<id<<endl;
            return true;
        }
    }
    SymbolInfo* Lookup(string name){
        unsigned long long hash = sdbm((const unsigned char*)name.c_str());
        int index = hash%size;
        SymbolInfo *temp = table[index];
        if(temp == NULL)
        {
            return NULL;
        }
        else
        {
            int pos = 0;
            while(temp != NULL)
            {
                if(temp->getName() == name)
                {
                    //cout<<"\t"<<"'"<<name<<"' found at position <"<<index+1<<", "<<pos+1<<"> of ScopeTable# "<<id<<endl;
                    return temp;
                }
                temp = temp->getNext();
                pos++;
            }
            return NULL;
        }
    }
    bool Delete(string name){
        unsigned long long hash = sdbm((const unsigned char*)name.c_str());
        int index = hash%size;
        SymbolInfo *temp = table[index];
        if(temp == NULL)
        {
            //cout<<"\t"<<"Not found in the current ScopeTable# "<<id<<endl;
            return false;
        }
        else
        {
            int pos = 0;
            if(temp->getName() == name)
            {
                table[index] = temp->getNext();
                delete temp;
                //cout<<"\t"<<"Deleted '"<<name<<"' from position <"<<index+1<<", "<<pos+1<<"> of ScopeTable# "<<id<<endl;
                return true;
            }
            while(temp->getNext() != NULL)
            {
                if(temp->getNext()->getName() == name)
                {
                    SymbolInfo *del = temp->getNext();
                    temp->setNext(del->getNext());
                    delete del;
                    //cout<<"\t"<<"Deleted '"<<name<<"' from position <"<<index+1<<", "<<pos+1<<"> of ScopeTable# "<<id<<endl;
                    return true;
                }
                temp = temp->getNext();
                pos++;
            }
          //  cout<<"\t"<<"Not found in the current ScopeTable# "<<id<<endl;
            return false;
        }
    }
    void print(){
        cout<<"\t"<<"ScopeTable# "<<id<<endl;
        for(int i=0; i<size; i++)
        {
            SymbolInfo *temp = table[i];
            if(temp == NULL)
                continue;
            cout<<"\t"<<i+1;
                cout<<"--> ";
            while(temp != NULL)
            {
                if(temp->getIsFunction()){
                    //transform(temp->getType().begin(), temp->getType().end(),temp->getType().begin(), ::toupper);
                    cout<<"<"<<temp->getName()<<","<<"FUNCTION"<<","<<temp->getType()<<">";
                }
                else if(temp->getIsArray()){
                    cout<<"<"<<temp->getName()<<","<<"ARRAY"<<">";
                }
                else{
                    cout<<"<"<<temp->getName()<<","<<temp->getType()<<">";
                }
                cout<<" ";
                temp = temp->getNext();
            }
            cout<<endl;
            
        }
    }
    int getId(){
        return id;
    }
    void setId(int id){
        this->id = id;
    }
    ScopeTable* getParentScope(){
        return parentScope;
    }
    void setParentScope(ScopeTable *parentScope){
        this->parentScope = parentScope;
    }
    int getSize(){
        return size;
    }
    void setSize(int size){
        this->size = size;
    }
    SymbolInfo** getTable(){
        return table;
    }
    void SetTable(SymbolInfo **table){
        this->table = table;
    }
    int getChildren(){
        return children;
    }
    void setChildren(int children){
        this->children = children;
    }
    void setOffset(int offset){
        this->offset = offset;
    }
    int getOffset(){
        return offset;
    }
};


#endif /* ScopeTable_h */
