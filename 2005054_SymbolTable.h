//
//  SymbolTable.h
//  Compiler
//
//  Created by Awesh Islam on 30/11/23.
//

#ifndef SymbolTable_h
#define SymbolTable_h
#include<iostream>
#include<string>
#include<cstring>
#include "2005054_ScopeTable.h"
using namespace std;

class SymbolTable
{
private:
    ScopeTable *currentScope;
    int size;
    int global_id = 1;
public:
    SymbolTable(int size)
    {
        this->size = size;
        currentScope = new ScopeTable(1, size);
    }
    ~SymbolTable()
    {
        while (currentScope) {
            ScopeTable *temp = currentScope;
            currentScope = currentScope->getParentScope();
            delete temp;
        }
    }
    void enterScope()
    {
        ScopeTable *newScope = new ScopeTable(++global_id, size);
        currentScope->setChildren(currentScope->getChildren()+1);
        newScope->setParentScope(currentScope);
        currentScope = newScope;
    }
    void exitScope()
    {
        ScopeTable *temp = currentScope;
        currentScope = currentScope->getParentScope();
        delete temp;
    }
    bool insert(string name, string type)
    {
        return currentScope->insert(name, type);
    }
    bool insert(SymbolInfo *symbol)
    {
        return currentScope->insert(symbol);
    }
    bool remove(string name)
    {
        return currentScope->Delete(name);
    }
    SymbolInfo* lookUp(string name)
    {
        ScopeTable *temp = currentScope;
        while(temp != NULL)
        {
            SymbolInfo *symbol = temp->Lookup(name);
            if(symbol != NULL)
                return symbol;
            temp = temp->getParentScope();
        }
        //cout<<"\t"<<"'"<<name<<"' not found in any of the ScopeTables"<<endl;
        return NULL;
    }
    SymbolInfo *lookUpCurrentScope(string name){
        return currentScope->Lookup(name);
    }
    void printCurrentScope()
    {
        currentScope->print();
    }
    void printAllScope()
    {
        ScopeTable *temp = currentScope;
        while(temp != NULL)
        {
            temp->print();
            temp = temp->getParentScope();
        }
    }
    int getCurrentScopeId(){
        return currentScope->getId();
    }
    ScopeTable* getCurrentScope(){
        return currentScope;
    }
    void setCurrentScope(ScopeTable *currentScope){
        this->currentScope = currentScope;
    }
    int getSize(){
        return size;
    }
    void setSize(int size){
        this->size = size;
    }
    int getOffset(){
        return currentScope->getOffset();
    }
    void setOffset(int offset){
        currentScope->setOffset(offset);
    }
};

#endif /* SymbolTable_h */
