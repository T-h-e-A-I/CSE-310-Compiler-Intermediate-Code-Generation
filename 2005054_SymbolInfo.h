//
//  Symbolinfo.h
//  Compiler
//
//  Created by Awesh Islam on 30/11/23.
//

#ifndef Symbolinfo_h
#define Symbolinfo_h
#include<string>
#include <vector>
#include<utility>
using namespace std;

class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo *next;

    // Parse Tree
    int start_line;
    int end_line;
    bool is_leaf = false;
    vector<SymbolInfo *> children;
    string parse_line;

    // Function
    string return_type;
    bool is_function = false;
    bool is_defined = false;
    bool is_declared = false;
    vector<pair<string,string> > parameter_list;

    // Array
    bool is_array = false;
    int array_size = 0;

    // ID
    bool is_id = false;
    string id_structure;

    //CodeGeneration
    int offset;

    //labels
    string labelTrue = "";
    string labelFalse = "";
    string labelEnd = "";

    //lists 
    vector<SymbolInfo*> symbol_parameter;
    vector<SymbolInfo*> symbol_declaration;

    //conditional
    bool isConditional = false;

public:
    // Constructors
    SymbolInfo(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->next = nullptr;
    }

    SymbolInfo()
    {
        this->name = "";
        this->type = "";
        this->next = nullptr;
    }
    SymbolInfo(string name, string type,int start_line,int end_line,bool is_leaf,string parse_line){
        this->name = name;
        this->type = type;
        this->start_line = start_line;
        this->end_line = end_line;
        this->is_leaf = is_leaf;
        this->parse_line = parse_line;
    }
    SymbolInfo(string name, string type,int start_line,int end_line,string parse_line){
        this->name = name;
        this->type = type;
        this->start_line = start_line;
        this->end_line = end_line;
        this->parse_line = parse_line;
    }

    // Getter and Setter for Name
    void setName(string name)
    {
        this->name = name;
    }

    string getName()
    {
        return this->name;
    }

    // Getter and Setter for Type
    void setType(string type)
    {
        this->type = type;
    }

    string getType()
    {
        return this->type;
    }

    // Getter and Setter for Next
    void setNext(SymbolInfo *next)
    {
        this->next = next;
    }

    SymbolInfo *getNext()
    {
        return this->next;
    }

    // Getter and Setter for Start Line
    void setStartLine(int start_line)
    {
        this->start_line = start_line;
    }

    int getStartLine()
    {
        return this->start_line;
    }

    // Getter and Setter for End Line
    void setEndLine(int end_line)
    {
        this->end_line = end_line;
    }

    int getEndLine()
    {
        return this->end_line;
    }

    // Getter and Setter for Is Leaf
    void setIsLeaf(bool is_leaf)
    {
        this->is_leaf = is_leaf;
    }

    bool getIsLeaf()
    {
        return this->is_leaf;
    }

    // Getter and Setter for Children
    void setChildren(vector<SymbolInfo *> children)
    {
        this->children = children;
    }

    vector<SymbolInfo *> getChildren()
    {
        return this->children;
    }

    // Getter and Setter for Parse Line
    void setParseLine(string parse_line)
    {
        this->parse_line = parse_line;
    }

    string getParseLine()
    {
        return this->parse_line;
    }

    // Getter and Setter for Return Type
    void setReturnType(string return_type)
    {
        this->return_type = return_type;
    }

    string getReturnType()
    {
        return this->return_type;
    }

    // Getter and Setter for Is Function
    void setIsFunction(bool is_function)
    {
        this->is_function = is_function;
    }

    bool getIsFunction()
    {
        return this->is_function;
    }

    // Getter and Setter for Is Defined
    void setIsDefined(bool is_defined)
    {
        this->is_defined = is_defined;
    }

    bool getIsDefined()
    {
        return this->is_defined;
    }

    // Getter and Setter for Is Declared
    void setIsDeclared(bool is_declared)
    {
        this->is_declared = is_declared;
    }

    bool getIsDeclared()
    {
        return this->is_declared;
    }

    // Getter and Setter for Parameter List
    void setParameterList(vector<pair<string,string> > parameter_list)
    {
        this->parameter_list = parameter_list;
    }

    vector<pair<string,string> > getParameterList()
    {
        return this->parameter_list;
    }

    // Getter and Setter for Is Array
    void setIsArray(bool is_array)
    {
        this->is_array = is_array;
    }

    bool getIsArray()
    {
        return this->is_array;
    }

    // Getter and Setter for Is ID
    void setIsId(bool is_id)
    {
        this->is_id = is_id;
    }

    bool getIsId()
    {
        return this->is_id;
    }

    // Getter and Setter for ID Structure
    void setIdStructure(string id_structure)
    {
        this->id_structure = id_structure;
    }

    string getIdStructure()
    {
        return this->id_structure;
    }

    //adding child
    void addChild(SymbolInfo *child)
    {
        this->children.push_back(child);

    }
    int getOffset() {
        return offset;
    }
    void setOffset(int offset) {
        this->offset = offset;
    }

    string getLabelTrue() {
        return labelTrue;
    }
    void setLabelTrue(string label) {
        this->labelTrue = label;
    }
    string getLabelFalse() {
        return labelFalse;
    }
    void setLabelFalse(string label) {
        this->labelFalse = label;
    }
    string getLabelEnd() {
        return labelEnd;
    }
    void setLabelEnd(string label) {
        this->labelEnd = label;
    }
    //getter setter for symbol_parameter
    void setSymbolParameter(vector<SymbolInfo*> symbol_parameter){
        this->symbol_parameter = symbol_parameter;
    }
    vector<SymbolInfo*> getSymbolParameter(){
        return this->symbol_parameter;
    }
    //getter setter for symbol_declaration
    void setSymbolDeclaration(vector<SymbolInfo*> symbol_declaration){
        this->symbol_declaration = symbol_declaration;
    }
    vector<SymbolInfo*> getSymbolDeclaration(){
        return this->symbol_declaration;
    }
    void addDeclaration(SymbolInfo *symbol){
        this->symbol_declaration.push_back(symbol);
    }

    //getter setter for array_size 
    void setArraySize(int array_size){
        this->array_size = array_size;
    }
    int getArraySize(){
        return this->array_size;
    }

    //setter getter for isConditional
    void setIsConditional(bool isConditional){
        this->isConditional = isConditional;
    }
    bool getIsConditional(){
        return this->isConditional;
    }
};



#endif /* Symbolinfo_h */
