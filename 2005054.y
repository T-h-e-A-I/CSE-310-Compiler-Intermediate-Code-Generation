%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<string>
#include<utility>
#include <cctype>
#include "2005054_SymbolTable.h"
#include "2005054_SymbolInfo.h"
// #define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
extern int errors;
extern bool inside_global_scope;

extern SymbolTable myTable;
FILE *fp2,*fp3;
FILE *output;

string stored_type;
extern vector<pair<string,string> > list;
vector<pair<string,string> > arguments_list;
vector<string> global_var;
vector<pair<string,int> > global_arr;
int labels = 0;
string current_func;


SymbolTable *table;


void yyerror(char *s)
{
	printf("Error %s\n",s);
}
void new_line_process(){
	fprintf(output,"new_line proc\npush ax\npush dx\nmov ah,2\nmov dl,0Dh\nint 21h\nmov ah,2\nmov dl,0Ah\nint 21h\npop dx\npop ax\nret\nnew_line endp\n\n");
}
void print_process(){
	fprintf(output,"print_output proc  ;print what is in ax\npush ax\npush bx\npush cx\npush dx\npush si\nlea si,number\nmov bx,10\nadd si,4\ncmp ax,0\njnge negate\nprint:\nxor dx,dx\ndiv bx\nmov [si],dl\nadd [si],'0'\ndec si\ncmp ax,0\njne print\ninc si\nlea dx,si\nmov ah,9\nint 21h\npop si\npop dx\npop cx\npop bx\npop ax\nret\nnegate:\npush ax\nmov ah,2\nmov dl,'-'\nint 21h\npop ax\nneg ax\njmp print\nprint_output endp\n\n");

}
string newLabel(){
        string h = to_string(labels++);
        h = "L"+h;
        return h;
}
string getOperation(string operation){
        string operationcode = "";
        if(operation == "<") operationcode ="\tJL";
        else if(operation == ">") operationcode ="\tJG";
        else if(operation == ">=") operationcode ="\tJGE";
        else if(operation == "<=") operationcode ="\tJLE";
        else if(operation == "==") operationcode ="\tJE";
        else if(operation == "!=") operationcode ="\tJNE";
        return operationcode;
    }
void generate_code(SymbolInfo *parent){
	if(parent->getParseLine() == "start : program"){
		fprintf(output,".model small\n.stack 100h\n\n");
		fprintf(output,".data\n\tnumber db \"00000$\"\n");
		for(int i = 0;i < global_var.size();i++){
			fprintf(output,"\t%s DW 1 DUP (0000H)\n",global_var[i].c_str());
		}
		for(int i = 0;i < global_arr.size();i++){
			fprintf(output,"\t%s dw %d DUP (0000H)\n",global_arr[i].first.c_str(),global_arr[i].second);
		}
		fprintf(output,".code\n\n");
		generate_code(parent->getChildren()[0]);
		new_line_process();
		print_process();
		fprintf(output,"end main\n\n");
	}else if(parent->getParseLine() == "program : program unit"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[1]);
	}else if(parent->getParseLine() == "program : unit"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "unit : var_declaration"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "unit : func_declaration"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "unit : func_definition"){
		//fprintf(output,"Inside unit :func : definition");
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[3]);
	}else if(parent->getParseLine() == "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement"){
		current_func = parent->getChildren()[1]->getName();
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[3]);
		fprintf(output,"%s proc\n",parent->getChildren()[1]->getName().c_str());
		fprintf(output,"\tINside func_definition %s\n",parent->getChildren()[1]->getName().c_str());
		if(parent->getChildren()[1]->getName() == "main"){
				fprintf(output,"\tMOV AX, @DATA\n");
				fprintf(output,"\tMOV DS, AX\n");
        }
		fprintf(output,"\tpush bp\n\tmov bp,sp\n");
		generate_code(parent->getChildren()[5]);
		fprintf(output,"%s_exit:\n\n",parent->getChildren()[1]->getName().c_str());
        if(parent->getChildren()[1]->getName() == "main"){
			fprintf(output,"\tMOV AX, 4CH\n\tINT 21H\n");
        }
		fprintf(output,"\tADD SP, %d\n",parent->getChildren()[5]->getOffset());
        fprintf(output,"\tPOP BP\n");
        if(parent->getChildren()[1]->getName() != "main"){
			fprintf(output,"\tRET\n");
        }
		fprintf(output,"%s endp\n\n",parent->getChildren()[1]->getName().c_str());
	}else if(parent->getParseLine() == "func_definition : type_specifier ID LPAREN RPAREN compound_statement"){
		current_func = parent->getChildren()[1]->getName();
		//fprintf(output,"Inside func_definition : type_specifier ID LPAREN RPAREN compound_statement\n");
		generate_code(parent->getChildren()[0]);
		//fprintf(output,"Inside func_definition : type_specifier ID LPAREN RPAREN compound_statement\n");
		//generate_code(parent->getChildren()[4]);
		//fprintf(output,"Inside func_definition : type_specifier ID LPAREN RPAREN compound_statement\n");
		fprintf(output,"%s proc\n",parent->getChildren()[1]->getName().c_str());
		//fprintf(output,"\tINside func_definition %s\n",parent->getChildren()[1]->getName().c_str());
		if(parent->getChildren()[1]->getName() == "main"){
				fprintf(output,"\tMOV AX, @DATA\n");
				fprintf(output,"\tMOV DS, AX\n");
        }
		fprintf(output,"\tpush bp\n\tmov bp,sp\n");
		generate_code(parent->getChildren()[4]);
		fprintf(output,"%s_exit:\n\n",parent->getChildren()[1]->getName().c_str());
        if(parent->getChildren()[1]->getName() == "main"){
			fprintf(output,"\tMOV AX, 4CH\n\tINT 21H\n");
        }
		fprintf(output,"\tADD SP, %d\n",parent->getChildren()[4]->getOffset());
        fprintf(output,"\tPOP BP\n");
        if(parent->getChildren()[1]->getName() != "main"){
			fprintf(output,"\tRET\n");
        }
		fprintf(output,"%s endp\n\n",parent->getChildren()[1]->getName().c_str());
	}else if(parent->getParseLine() == "parameter_list  : parameter_list COMMA type_specifier ID"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[2]);
	}else if(parent->getParseLine() == "parameter_list  : parameter_list COMMA type_specifier"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[2]);
	}else if(parent->getParseLine() == "parameter_list  : type_specifier ID"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[1]);
	}else if(parent->getParseLine() == "parameter_list  : type_specifier"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "compound_statement : LCURL statements RCURL"){
		//fprintf(output,"compound_statement : LCURL statements RCURL\n");
		inside_global_scope = false;
		if(parent->getLabelEnd() == "") parent->setLabelEnd(newLabel());
		parent->getChildren()[1]->setLabelEnd(parent->getLabelEnd());
		generate_code(parent->getChildren()[1]);
		inside_global_scope = true;
	}else if(parent->getParseLine() == "var_declaration : type_specifier declaration_list SEMICOLON"){
		//fprintf(output,"var_declaration : type_specifier declaration_list SEMICOLON\n");
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[1]);
		//fprintf(output,"size is %d\n\n",parent->getChildren()[1]->getSymbolDeclaration().size());
            for(int i= 0; i<parent->getChildren()[1]->getSymbolDeclaration().size(); i++){
                if(inside_global_scope);
                else{
                    if(parent->getChildren()[1]->getSymbolDeclaration()[i]->getIsArray()) fprintf(output,"\tSUB SP, %d\n",2*parent->getChildren()[1]->getSymbolDeclaration()[i]->getArraySize());
                    else fprintf(output,"\tSUB SP, 2\n");
                }
            }
	}else if(parent->getParseLine() == "declaration_list : declaration_list COMMA ID"){
		
	}else if(parent->getParseLine() == "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD"){
		
	}else if(parent->getParseLine() == "declaration_list : ID"){
		
	}else if(parent->getParseLine() == "declaration_list : ID LTHIRD CONST_INT RTHIRD"){
		
	}else if(parent->getParseLine() == "declaration_list : ID ASSIGNOP CONST_INT"){
		
	}else if(parent->getParseLine() == "statements : statement"){
		parent->getChildren()[0]->setLabelEnd(parent->getLabelEnd());
		generate_code(parent->getChildren()[0]);
        fprintf(output,"%s: ;\n",parent->getLabelEnd().c_str());
	}else if(parent->getParseLine() == "statements : statements statement"){
		//fprintf(output,"Inside statements : statements statement\n");
		parent->getChildren()[0]->setLabelEnd(newLabel());
		parent->getChildren()[1]->setLabelEnd(parent->getLabelEnd());
        generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[1]);
		fprintf(output,"%s: ;\n",parent->getLabelEnd().c_str());
	}else if(parent->getParseLine() == "statement : var_declaration"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "statement : expression_statement"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "statement : compound_statement"){
		parent->getChildren()[0]->setLabelEnd(newLabel());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"){
		generate_code(parent->getChildren()[2]);
        string loop = newLabel();
		fprintf(output,"%s: ;\n",loop.c_str());
		parent->getChildren()[3]->setIsConditional(true);
        parent->getChildren()[3]->setLabelTrue(newLabel());
		parent->getChildren()[3]->setLabelFalse(parent->getLabelEnd());
		parent->getChildren()[6]->setLabelEnd(newLabel());
        generate_code(parent->getChildren()[3]);
        fprintf(output,"%s: ;\n",parent->getChildren()[3]->getLabelTrue().c_str());
        generate_code(parent->getChildren()[6]);
		generate_code(parent->getChildren()[4]);
		fprintf(output,"\tJMP %s\n",loop.c_str());
	}else if(parent->getParseLine() == "statement : IF LPAREN expression RPAREN statement"){
		parent->getChildren()[2]->setIsConditional(true);
		parent->getChildren()[2]->setLabelTrue(newLabel());
		parent->getChildren()[2]->setLabelFalse(parent->getLabelEnd());
		parent->getChildren()[4]->setLabelEnd(parent->getLabelEnd());
		generate_code(parent->getChildren()[2]);
		fprintf(output,"%s: ;\n",parent->getChildren()[2]->getLabelTrue().c_str());
		generate_code(parent->getChildren()[4]);
	}else if(parent->getParseLine() == "statement : IF LPAREN expression RPAREN statement ELSE statement"){
		parent->getChildren()[2]->setIsConditional(true);
		parent->getChildren()[2]->setLabelTrue(newLabel());
		parent->getChildren()[2]->setLabelFalse(newLabel());
		parent->getChildren()[4]->setLabelEnd(parent->getChildren()[2]->getLabelFalse());
		parent->getChildren()[6]->setLabelEnd(parent->getLabelEnd());
		generate_code(parent->getChildren()[2]);
		fprintf(output,"%s: ;\n",parent->getChildren()[2]->getLabelTrue().c_str());
		generate_code(parent->getChildren()[4]);
		fprintf(output,"\tJMP %s\n",parent->getLabelEnd().c_str());
		fprintf(output,"%s: :\n",parent->getChildren()[2]->getLabelFalse().c_str());
		generate_code(parent->getChildren()[6]);
	}else if(parent->getParseLine() == "statement : WHILE LPAREN expression RPAREN statement"){
		string loop = newLabel();
		parent->getChildren()[2]->setIsConditional(true);
		parent->getChildren()[2]->setLabelTrue(newLabel());
		parent->getChildren()[2]->setLabelFalse(parent->getLabelEnd());
		parent->getChildren()[4]->setLabelEnd(parent->getLabelEnd());
		fprintf(output,"%s: ;\n",loop.c_str());
		generate_code(parent->getChildren()[2]);
		fprintf(output,"%s: ;\n",parent->getChildren()[2]->getLabelTrue().c_str());
		generate_code(parent->getChildren()[4]);
		fprintf(output,"\tJMP %s\n",loop.c_str());
	}else if(parent->getParseLine() == "statement : PRINTLN LPAREN ID RPAREN SEMICOLON"){
		if(inside_global_scope){
				fprintf(output,"\tmov ax,%s\n",parent->getChildren()[2]->getName().c_str());
				fprintf(output,"\tcall print_output\n");
				fprintf(output,"\tcall new_line\n");
            }
            else{
				fprintf(output,"\tPUSH BP\n");
				fprintf(output,"\tMOV BX, %d\n",parent->getChildren()[2]->getOffset());
				fprintf(output,"\tADD BP, BX\n");
				fprintf(output,"\tMOV AX, [BP]\n");
				fprintf(output,"\tCALL print_output\n");
				fprintf(output,"\tCALL new_line\n");
				fprintf(output,"\tPOP BP\n");
            }
	}else if(parent->getParseLine() == "statement : RETURN expression SEMICOLON"){
		generate_code(parent->getChildren()[1]);
		fprintf(output,"\tMOV DX,CX\n");
		fprintf(output,"\tJMP %s_exit\n",current_func.c_str());
	}else if(parent->getParseLine() == "expression_statement : expression SEMICOLON"){
		parent->setIsConditional(parent->getIsConditional());
		parent->setLabelTrue(parent->getLabelTrue());
		parent->setLabelFalse(parent->getLabelFalse());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "variable : ID"){
		if(inside_global_scope){}
        else{
				fprintf(output,"\tPUSH BP\n");
				fprintf(output,"\tMOV BX, %d\n",parent->getOffset());
				fprintf(output,"\tADD BP, BX\n");
        }
	}else if(parent->getParseLine() == "variable : ID LTHIRD expression RTHIRD"){
		generate_code(parent->getChildren()[2]);
            if(!inside_global_scope){
				fprintf(output,"\tPUSH BP\n");
				fprintf(output,"\tMOV BX, CX\n");
				fprintf(output,"\tADD BX, BX\n");
				fprintf(output,"\tADD BX, %d\n",parent->getOffset());
				fprintf(output,"\tADD BP, BX\n");

            }
            else{
				fprintf(output,"\tLEA SI, %s\n",parent->getChildren()[0]->getName().c_str());
				fprintf(output,"\tADD SI, CX\n");
				fprintf(output,"\tADD SI, CX\n");
				fprintf(output,"\tPUSH BP\n");
				fprintf(output,"\tMOV BP, SI\n");
            }
	}else if(parent->getParseLine() == "expression : variable ASSIGNOP logic_expression"){
		generate_code(parent->getChildren()[2]);
		parent->getChildren()[0]->setIsConditional(false);
        parent->getChildren()[2]->setIsConditional(false);
		bool global = false;
    	if(find(global_var.begin(),global_var.end(),parent->getChildren()[0]->getName()) != global_var.end()){
			global = true;
		};
            if(global && !parent->getChildren()[0]->getIsArray()){
				generate_code(parent->getChildren()[0]);
				fprintf(output,"\tMOV %s, CX\n",parent->getChildren()[0]->getName().c_str());
            }
            else{
				fprintf(output,"\tPUSH CX\n");
				generate_code(parent->getChildren()[0]);
                fprintf(output,"\tPOP AX\n\tPOP AX\n\tPOP CX\n\tMOV [BP], CX\n\tMOV BP, AX\n");
            }
            if(parent->getIsConditional()) fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
	}else if(parent->getParseLine() == "expression : logic_expression"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "logic_expression : rel_expression"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "logic_expression : logic_expression LOGICOP rel_expression"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[2]->setIsConditional(parent->getIsConditional());
        if(parent->getChildren()[1]->getName() == "||"){
				parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
				parent->getChildren()[0]->setLabelFalse(newLabel()+"jmpfalse");
				parent->getChildren()[2]->setLabelTrue(parent->getLabelTrue());
				parent->getChildren()[2]->setLabelFalse(parent->getLabelFalse());
            }
            else{
				parent->getChildren()[0]->setLabelTrue(newLabel()+"jmptrue");
				parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
				parent->getChildren()[2]->setLabelTrue(parent->getLabelTrue());
				parent->getChildren()[2]->setLabelFalse(parent->getLabelFalse());
            }
			generate_code(parent->getChildren()[0]);
            if(parent->getIsConditional()){
                if(parent->getChildren()[1]->getName() == "||") fprintf(output,"%s: ;\n",parent->getChildren()[0]->getLabelFalse().c_str());
				else fprintf(output,"%s: ;\n",parent->getChildren()[0]->getLabelTrue().c_str());
            }
        	else fprintf(output,"\tPUSH CX\n");
			generate_code(parent->getChildren()[2]);
            if(!parent->getIsConditional()){
				fprintf(output,"\tPOP AX\n");
                if(parent->getChildren()[1]->getName()=="||"){
                    string x = newLabel();
                    string y = newLabel();
                    string z = newLabel();
                    string a = newLabel();
                    fprintf(output,"\tCMP AX, 0\n");
                    fprintf(output, "\tJE %s\n",x.c_str());
					fprintf(output, "\tJMP %s\n",y.c_str());
					fprintf(output, "%s: ;\n",x.c_str());
                    fprintf(output,"\tJCXZ  %s\n",z.c_str());
                    fprintf(output,"%s: ;\n",y.c_str());
                    fprintf(output,"\tMOV CX, 1\n");
					fprintf(output,"\tJMP %s\n",a.c_str());
					fprintf(output,"%s: ;\n",z.c_str());
					fprintf(output,"\tMOV CX, 0\n");
					fprintf(output,"%s: ;\n",a.c_str());
                }
                else{
                    string x = newLabel();
                    string y = newLabel();
                    string z = newLabel();
                    fprintf(output, "\tCMP AX, 0\n");
					fprintf(output,"\tJE %s\n",x.c_str());
                    fprintf(output,"\tJCXZ %s\n",x.c_str());
					fprintf(output,"\tJMP %s\n",y.c_str());
					fprintf(output,"%s: ;\n",x.c_str());
                    fprintf(output,"\tMOV CX, 0\n");
                    fprintf(output,"\tJMP %s\n",z.c_str());
					fprintf(output,"%s: ;\n",y.c_str());
                    fprintf(output,"\tMOV CX, 1\n");
					fprintf(output,"%s: ;\n",z.c_str());
                }
            }
	}else if(parent->getParseLine() == "rel_expression : simple_expression"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
        generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "rel_expression : simple_expression RELOP simple_expression"){
		generate_code(parent->getChildren()[0]);
		fprintf(output,"\tPUSH CX\n");
        generate_code(parent->getChildren()[2]);
		string opcode = getOperation(parent->getChildren()[1]->getName());
        fprintf(output,"\tPOP AX\n\tCMP AX, CX\n");
        if(parent->getLabelTrue() == "" ) parent->setLabelTrue(newLabel());
		if(parent->getLabelFalse() == "") parent->setLabelFalse(newLabel());
		fprintf(output,"\t%s %s\n",opcode.c_str(),parent->getLabelTrue().c_str());
		fprintf(output,"\tJMP %s\n",parent->getLabelFalse().c_str());
        if(!parent->getIsConditional()){
			fprintf(output,"%s: ;\n",parent->getLabelTrue().c_str());
			fprintf(output,"\tMOV CX, 1\n");
			string leave = newLabel();
			fprintf(output,"\tJMP %s\n",leave.c_str());
			fprintf(output,"%s: ;\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tMOV CX, 0\n");
			fprintf(output,"%s: ;Line Number\n",leave.c_str());
        }
	}else if(parent->getParseLine() == "simple_expression : term"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "simple_expression : simple_expression ADDOP term"){
		generate_code(parent->getChildren()[0]);
		fprintf(output,"\tPUSH CX\n");
		generate_code(parent->getChildren()[2]);
		fprintf(output,"\tPOP AX\n");
        if(parent->getChildren()[1]->getName() =="+") fprintf(output,"\tADD CX, AX\n");
        if(parent->getChildren()[1]->getName() =="-") fprintf(output,"\tSUB AX, CX\n\tMOV CX, AX\n");
        if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
        }
	}else if(parent->getParseLine() == "term : unary_expression"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "term : term MULOP unary_expression"){
		generate_code(parent->getChildren()[0]);
		fprintf(output,"\tPUSH CX\n");
		generate_code(parent->getChildren()[2]);
		fprintf(output,"\tPOP AX\n");
        if(parent->getChildren()[1]->getName()=="*"){
			fprintf(output,"\tIMUL CX\n\tMOV CX, AX\n");
        }
        else if(parent->getChildren()[1]->getName()=="/"){
			fprintf(output,"\tCWD\n\tIDIV CX\n\tMOV CX, AX\n");
        }
        else if(parent->getChildren()[1]->getName()=="%"){
			fprintf(output,"\tCWD\n\tIDIV CX\n\tMOV CX, DX\n");
        }
        if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
        }
	}else if(parent->getParseLine() == "unary_expression : ADDOP unary_expression"){
		parent->getChildren()[1]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[1]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[1]->setLabelFalse(parent->getLabelFalse());
        generate_code(parent->getChildren()[1]);
        if(parent->getChildren()[0]->getName()=="-"){
			fprintf(output,"\tNEG CX\n");
        }
	}else if(parent->getParseLine() == "unary_expression : NOT unary_expression"){
		parent->getChildren()[1]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[1]->setLabelTrue(parent->getLabelFalse());
		parent->getChildren()[1]->setLabelFalse(parent->getLabelTrue());
		generate_code(parent->getChildren()[1]);
        if(!parent->getIsConditional()){
            string l0 = newLabel();
            string l1 = newLabel();
			fprintf(output,"\tJCXZ %s\n",l1.c_str());
			fprintf(output,"\tMOV CX,0\n");
			fprintf(output,"\tJMP %s\n",l0.c_str());
			fprintf(output,"%s: ;\n",l1.c_str());
			fprintf(output,"\tMOV CX,1\n");
			fprintf(output,"%s: ;\n",l0.c_str());
        }
	}else if(parent->getParseLine() == "unary_expression : factor"){
		parent->getChildren()[0]->setIsConditional(parent->getIsConditional());
		parent->getChildren()[0]->setLabelTrue(parent->getLabelTrue());
		parent->getChildren()[0]->setLabelFalse(parent->getLabelFalse());
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "factor : variable"){
		generate_code(parent->getChildren()[0]);
		bool global = false;
		if(find(global_var.begin(),global_var.end(),parent->getChildren()[0]->getName()) != global_var.end()){
			global = true;
		};
        if(global && !parent->getChildren()[0]->getIsArray()){
			fprintf(output,"\tMOV CX, %s\n",parent->getChildren()[0]->getName().c_str());
        }
		else{
			fprintf(output,"\tMOV CX, [BP]\n\tPOP BP\n");
        }
        if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
        }
	}else if(parent->getParseLine() == "factor : ID LPAREN argument_list RPAREN"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[2]);
		fprintf(output,"\tCALL %s\n",parent->getChildren()[0]->getName().c_str());
		fprintf(output,"\tMOV CX, DX\n");
        fprintf(output,"\tADD SP, %d\n",parent->getChildren()[2]->getOffset());
        if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
        }
	}else if(parent->getParseLine() == "factor : LPAREN expression RPAREN"){
		generate_code(parent->getChildren()[1]);
		if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
		}
	}else if(parent->getParseLine() == "factor : CONST_INT"){
		generate_code(parent->getChildren()[0]);
		fprintf(output,"mov cx, %s\n",parent->getChildren()[0]->getName().c_str());
		if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
		}
	}else if(parent->getParseLine() == "factor : CONST_FLOAT"){
		generate_code(parent->getChildren()[0]);
		fprintf(output,"mov cx, %s\n",parent->getChildren()[0]->getName().c_str());
		if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
		}
	}else if(parent->getParseLine() == "factor : variable INCOP"){
		generate_code(parent->getChildren()[0]);
		bool global = false;
		if(find(global_var.begin(),global_var.end(),parent->getChildren()[0]->getName()) != global_var.end()){
			global = true;
		}
        if(global && !parent->getChildren()[0]->getIsArray()){
			fprintf(output,"\tMOV CX, %s\n",parent->getChildren()[0]->getName().c_str());
		} 
        else fprintf(output,"\tMOV CX, [BP]\n");
		fprintf(output,"\tMOV AX, CX\n");
        if(parent->getChildren()[1]->getName()=="++") fprintf(output,"\tINC CX\n");
        if(parent->getChildren()[1]->getName()=="--") fprintf(output,"\tDEC CX\n");
            
        if(global) {
			fprintf(output,"\tMOV %s, CX\n",parent->getChildren()[0]->getName().c_str());
		}
		else{
			fprintf(output,"\tMOV [BP], CX\n");
			fprintf(output,"\tPOP BP\n");
		}
		fprintf(output,"\tMOV CX, AX\n");
		if(parent->getIsConditional()){
			fprintf(output,"\tJCXZ %s\n",parent->getLabelFalse().c_str());
			fprintf(output,"\tJMP %s\n",parent->getLabelTrue().c_str());
		}
	}else if(parent->getParseLine() == "argument_list : arguments"){
		generate_code(parent->getChildren()[0]);
	}else if(parent->getParseLine() == "arguments : arguments COMMA logic_expression"){
		generate_code(parent->getChildren()[0]);
		generate_code(parent->getChildren()[2]);
		fprintf(output,"push cx\n");
	}else if(parent->getParseLine() == "arguments : logic_expression"){
		generate_code(parent->getChildren()[0]);
		fprintf(output,"push cx\n");
	}
}
void parse_tree_print(SymbolInfo *parent,int level){
	if(parent->getIsLeaf()==true){
		fprintf(fp2,"             %s : %s  <Line: %d>\n",parent->getParseLine().c_str(),parent->getName().c_str(),parent->getStartLine());
		return;
	}
	else{
		for(int i=0; i<level; i++){
			fprintf(fp2,"  ");
		}
		fprintf(fp2,"%s <Line: %d-%d>\n",parent->getParseLine().c_str(),parent->getStartLine(),parent->getEndLine());
	}

	for(int i=0; i<parent->getChildren().size(); i++){
		parse_tree_print(parent->getChildren()[i], level+1);
	}
}
void check_and_insert_var_in_symbol_table(string id,string type){
	for(char &c: type){
		c = toupper(c);
	}
	if(type=="VOID"){
		fprintf(fp3,"Line# %d: Variable or field '%s' declared void\n",line_count,id.c_str());
		errors++;
		return;
	}
	SymbolInfo *temp = myTable.lookUpCurrentScope(id);
	if(temp==NULL){
		SymbolInfo *temp = new SymbolInfo(id,type);
		myTable.insert(temp);
		if(inside_global_scope){
			global_var.push_back(id);
		}
	}
	else{
		if(temp->getType() != type){
			fprintf(fp3,"Line# %d: Conflicting types for'%s'\n",line_count,id.c_str());
		}else{
			fprintf(fp3,"Line# %d: %s already declared in this scope\n",line_count,id.c_str());
		}
		errors++;
	}
}
void check_and_insert_func_in_symbol_table(string id,string type,bool isDefined,bool isDeclared,int startline){
	for(char &c: type){
		c = toupper(c);
	}
	SymbolInfo *temp = myTable.lookUpCurrentScope(id);
	if(temp==NULL){
		SymbolInfo *temp = new SymbolInfo(id,type);
		temp->setIsFunction(true);
		temp->setReturnType(type);
		temp->setParameterList(list);
		temp->setIsDeclared(isDeclared);
		temp->setIsDefined(isDefined);
		//fprintf(output,"Name of current function from insert: %s\n",current_func.c_str());
		myTable.insert(temp);
	}
	else{
		if(temp->getIsDeclared()){
			//fprintf(fp3,"<Line: %d> %s already declared\n",line_count,id.c_str());
			if(temp->getReturnType() != type || temp->getParameterList() != list){
				fprintf(fp3,"Line# %d: Conflicting types for '%s'\n",startline,id.c_str());
				errors++;
			}
		}else if(temp->getIsDefined()){
			fprintf(fp3,"Line: %d: '%s' already defined\n",startline,id.c_str());
			errors++;

		}else{
			fprintf(fp3,"Line# %d: '%s' redeclared as different kind of symbol\n",startline,id.c_str());
			errors++;
		}
	}
	list.clear();
}
void check_and_insert_array_in_symbol_table(string id,string type,string size){
	for(char &c: type){
		c = toupper(c);
	}
	if(type=="VOID"){
		fprintf(fp3,"Line# %d: Variable or field '%s' declared void\n",line_count,id.c_str());
		errors++;
		return;
	}
	SymbolInfo *temp = myTable.lookUpCurrentScope(id);
	if(temp==NULL){
		SymbolInfo *temp = new SymbolInfo(id,type);
		temp->setIsArray(true);
		if(inside_global_scope){
			global_arr.push_back(make_pair(id,stoi(size)));
		}
		myTable.insert(temp);
	}
	else{
		if(temp->getType() != type){
			fprintf(fp3,"Line# %d: Conflicting types for'%s'\n",line_count,id.c_str());
		}else{
			fprintf(fp3,"Line# %d: %s already declared in this scope\n",line_count,id.c_str());
		}
		errors++;
	}
}

%}
%union {
    SymbolInfo* symbol_info;
}
%token<symbol_info> IF ELSE FOR WHILE ID LPAREN RPAREN SEMICOLON LCURL RCURL LTHIRD RTHIRD COMMA ASSIGNOP RELOP LOGICOP ADDOP MULOP NOT INCOP DECOP PRINTLN RETURN INT FLOAT VOID CONST_INT CONST_FLOAT 
%type<symbol_info> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments
/* %left 
%right*/

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : program
	{
		printf("start : program\n");
		string temp = "start : program";
		$$ = new SymbolInfo($1->getName(), "start",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
		parse_tree_print($$,0);
		generate_code($$);

	}
	;

program : program unit 
	{
		printf("program : program unit\n");
		string temp = "program : program unit";
		$$ = new SymbolInfo($1->getName(), "program",$1->getStartLine(),$2->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);
	}
	| unit
	{
		printf("program : unit\n");
		string temp = "program : unit";
		$$ = new SymbolInfo($1->getName(), "program",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	}
	;
	
unit : var_declaration
	{
		printf("unit : var_declaration\n");
		string temp = "unit : var_declaration";
		$$ = new SymbolInfo($1->getName(), "unit",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);

	 }
     | func_declaration
	 {
		printf("unit : func_declaration\n");
		string temp = "unit : func_declaration";
		$$ = new SymbolInfo($1->getName(), "unit",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	 }
     | func_definition
	 {
		printf("unit : func_definition\n");
		string temp = "unit : func_definition";
		$$ = new SymbolInfo($1->getName(), "unit",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	 
	 }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
		{
			printf("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n");
			string temp = "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
			$$ = new SymbolInfo($2->getName(), "func_declaration",$2->getStartLine(),$5->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);$$->addChild($6);

			check_and_insert_func_in_symbol_table($2->getName(),$1->getName(),false,true,$2->getStartLine());

		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			printf("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n");
			string temp = "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
			$$ = new SymbolInfo($2->getName(), "func_declaration",$2->getStartLine(),$5->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);

			check_and_insert_func_in_symbol_table($2->getName(),$1->getName(),false,true,$2->getStartLine());
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{
		
			//fprintf(output,"current function from defintion %s;\n",$2->getName.c_str());
			printf("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n");
			string temp = "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";
			$$ = new SymbolInfo($2->getName(), "func_definition",$2->getStartLine(),$6->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);$$->addChild($6);
			check_and_insert_func_in_symbol_table($2->getName(),$1->getName(),true,false,$2->getStartLine());
		}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
			//fprintf(output,"current function from defintion %s;\n",current_func.c_str());
			printf("func_definition : type_specifier ID LPAREN RPAREN compound_statement\n");
			string temp = "func_definition : type_specifier ID LPAREN RPAREN compound_statement";
			$$ = new SymbolInfo($2->getName(), "func_definition",$2->getStartLine(),$5->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);
			check_and_insert_func_in_symbol_table($2->getName(),$1->getName(),true,false,$2->getStartLine());
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			printf("parameter_list  : parameter_list COMMA type_specifier ID\n");
			string temp = "parameter_list  : parameter_list COMMA type_specifier ID";
			$$ = new SymbolInfo($4->getName(), "parameter_list",$4->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);
			for(pair<string,string> p: list){
				if(p.second == $4->getName()){
					fprintf(fp3,"Line# %d: Redefinition of parameter '%s'\n",$4->getStartLine(),$4->getName().c_str());
					errors++;
				}
			}
			
			list.push_back(make_pair($3->getName(),$4->getName()));
		}
		| parameter_list COMMA type_specifier
		{
			printf("parameter_list  : parameter_list COMMA type_specifier\n");
			string temp = "parameter_list  : parameter_list COMMA type_specifier";
			$$ = new SymbolInfo($3->getName(), "parameter_list",$3->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);
			list.push_back(make_pair($3->getName(),""));
		}
 		| type_specifier ID
		{
			printf("parameter_list  : type_specifier ID\n");
			string temp = "parameter_list  : type_specifier ID";
			$$ = new SymbolInfo($2->getName(), "parameter_list",$2->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);
			for(pair<string,string> p: list){
				if(p.second == $2->getName()){
					fprintf(fp3,"Line# %d: Redefinition of parameter '%s'\n",$2->getStartLine(),$2->getName().c_str());
					errors++;
				}
			}
			list.push_back(make_pair($1->getName(),$2->getName()));
		}
		| type_specifier
		{
			printf("parameter_list  : type_specifier\n");
			string temp = "parameter_list  : type_specifier";
			$$ = new SymbolInfo($1->getName(), "parameter_list",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);

			list.push_back(make_pair($1->getName(),""));
		}
 		;

 		
compound_statement : LCURL statements RCURL
			{
				printf("compound_statement : LCURL statements RCURL\n");
				string temp = "compound_statement : LCURL statements RCURL";
				$$ = new SymbolInfo($1->getName(), "compound_statement",$1->getStartLine(),$3->getEndLine(),temp);
				$$->addChild($1);$$->addChild($2);$$->addChild($3);
				myTable.printAllScope();
    			myTable.exitScope();
				
			}
 		    | LCURL RCURL
			{
				printf("compound_statement : LCURL RCURL\n");
				string temp = "compound_statement : LCURL RCURL";
				$$ = new SymbolInfo($1->getName(), "compound_statement",$1->getStartLine(),$2->getEndLine(),temp);
				$$->addChild($1);$$->addChild($2);
				myTable.printAllScope();
    			myTable.exitScope();
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
{
	printf("var_declaration : type_specifier declaration_list SEMICOLON\n");
	string temp = "var_declaration : type_specifier declaration_list SEMICOLON";
	$$ = new SymbolInfo($1->getName(), "var_declaration",$1->getStartLine(),$3->getEndLine(),temp);
	$$->addChild($1);$$->addChild($2);$$->addChild($3);
}
 		 ;
 		 
type_specifier	: INT
		{
			printf("type_specifier	: INT\n");
			string temp = "type_specifier	: INT";
			$$ = new SymbolInfo($1->getName(), "type_specifier",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);

			stored_type = "INT";

		}
 		| FLOAT
		{
			printf("type_specifier	: FLOAT\n");
			string temp = "type_specifier	: FLOAT";
			$$ = new SymbolInfo($1->getName(), "type_specifier",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);

			stored_type = "FLOAT";
		}
 		| VOID
		{
			printf("type_specifier	: VOID\n");
			string temp = "type_specifier	: VOID";
			$$ = new SymbolInfo($1->getName(), "type_specifier",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);

			stored_type = "VOID";
		}
 		;
 		
declaration_list : declaration_list COMMA ID
			{
				printf("declaration_list : declaration_list COMMA ID\n");
				string temp = "declaration_list : declaration_list COMMA ID";
				$$ = new SymbolInfo($3->getName(), "declaration_list",$3->getStartLine(),$1->getEndLine(),temp);
				$$->addChild($1);$$->addChild($2);$$->addChild($3);
				$$->setSymbolDeclaration($1->getSymbolDeclaration());
				$$->addDeclaration($3);
				check_and_insert_var_in_symbol_table($3->getName(),stored_type);
				
			}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		  {
			printf("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE\n");
			string temp = "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";
			$$ = new SymbolInfo($3->getName(), "declaration_list",$3->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);$$->addChild($6);
			$$->setSymbolDeclaration($1->getSymbolDeclaration());
			$3->setIsArray(true);
			$3->setArraySize(stoi($5->getName()));
			$$->addDeclaration($3);

			check_and_insert_array_in_symbol_table($3->getName(),stored_type,$5->getName());
		}
 		  | ID
		  {
			printf("declaration_list : ID\n");
			string temp = "declaration_list : ID";
			$$ = new SymbolInfo($1->getName(), "declaration_list",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
			$$->addDeclaration($1);
			check_and_insert_var_in_symbol_table($1->getName(),stored_type);
		  }
 		  | ID LTHIRD CONST_INT RTHIRD
		  {
			printf("declaration_list : ID LSQUARE CONST_INT RSQUARE\n");
			string temp = "declaration_list : ID LSQUARE CONST_INT RSQUARE";
			$$ = new SymbolInfo($1->getName(), "declaration_list",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);
			$1->setIsArray(true);
			$1->setArraySize(stoi($2->getName()));
			$$->addDeclaration($1);
			check_and_insert_array_in_symbol_table($1->getName(),stored_type,$3->getName());
		  }
 		  | ID ASSIGNOP CONST_INT
		  {
			check_and_insert_var_in_symbol_table($1->getName(),stored_type);
		  }
 		  ;
 		  
statements : statement
		{
			printf("statements : statement\n");
			string temp = "statements : statement";
			$$ = new SymbolInfo($1->getName(), "statements",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
		}
	   | statements statement
	   {
		printf("statements : statements statement\n");
		string temp = "statements : statements statement";
		$$ = new SymbolInfo($1->getName(), "statements",$1->getStartLine(),$2->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);
	   }
	   ;
	   
statement : var_declaration
		{	
			printf("statement : var_declaration\n");
			string temp = "statement : var_declaration";
			$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);

		}	
	  | expression_statement
	  {
		printf("statement : expression_statement\n");
		string temp = "statement : expression_statement";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	  }
	  | compound_statement
	  {
		printf("statement : compound_statement\n");
		string temp = "statement : compound_statement";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	  }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  {
		printf("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n");
		string temp = "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$7->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);$$->addChild($6);$$->addChild($7);
	  }
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	  {
		printf("statement : IF LPAREN expression RPAREN statement\n");
		string temp = "statement : IF LPAREN expression RPAREN statement";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$5->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);
	  }
	  | IF LPAREN expression RPAREN statement ELSE statement
	  {
		printf("statement : IF LPAREN expression RPAREN statement ELSE statement\n");
		string temp = "statement : IF LPAREN expression RPAREN statement ELSE statement";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$7->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);$$->addChild($6);$$->addChild($7);
	  }
	  | WHILE LPAREN expression RPAREN statement
	  {
		printf("statement : WHILE LPAREN expression RPAREN statement\n");
		string temp = "statement : WHILE LPAREN expression RPAREN statement";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$5->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);
	  }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  {
		printf("statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n");
		string temp = "statement : PRINTLN LPAREN ID RPAREN SEMICOLON";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$5->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);$$->addChild($5);
	  }
	  | RETURN expression SEMICOLON
	  {
		printf("statement : RETURN expression SEMICOLON\n");
		string temp = "statement : RETURN expression SEMICOLON";
		$$ = new SymbolInfo($1->getName(), "statement",$1->getStartLine(),$3->getEndLine(),temp);
		//fprintf(output,"Name of current function from rule: %s\n",current_func.c_str());
		$$->addChild($1);$$->addChild($2);$$->addChild($3);
	  }
	  ;
	  
expression_statement 	: SEMICOLON		
			{
				printf("expression_statement : SEMICOLON\n");
				string temp = "expression_statement : SEMICOLON";
				$$ = new SymbolInfo($1->getName(), "expression_statement",$1->getStartLine(),$1->getEndLine(),temp);
				$$->addChild($1);
			}	
			| expression SEMICOLON 
			{
				printf("expression_statement : expression SEMICOLON\n");
				string temp = "expression_statement : expression SEMICOLON";
				$$ = new SymbolInfo($1->getName(), "expression_statement",$1->getStartLine(),$2->getEndLine(),temp);
				$$->addChild($1);$$->addChild($2);
			}
			;
	  
variable : ID 		
	{
		printf("variable : ID\n");
		string temp = "variable : ID";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
		SymbolInfo *symbol = myTable.lookUp($1->getName());
		if(symbol==NULL){
			fprintf(fp3,"Line# %d: Undeclared variable '%s'\n",$1->getStartLine(),$1->getName().c_str());
			errors++;
		}else{
			$1->setType(symbol->getType());
			$$->setType(symbol->getType());
		}
	}
	 | ID LTHIRD expression RTHIRD 
	 {
		printf("variable : ID LSQUARE expression RSQUARE\n");
		string temp = "variable : ID LSQUARE expression RSQUARE";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$4->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);
		if($3->getType()!="INT"){
			fprintf(fp3,"Line# %d: Array subscript is not an integer\n",$3->getStartLine());
			errors++;
		}
		SymbolInfo *symbol = myTable.lookUp($1->getName());
		if(symbol==NULL){
			fprintf(fp3,"Line# %d: Undeclared variable '%s'\n",$1->getStartLine(),$1->getName().c_str());
			errors++;
		}else{
			if(symbol->getIsArray()==false){
				fprintf(fp3,"Line# %d: '%s' is not an array\n",$1->getStartLine(),$1->getName().c_str());
				errors++;
			}else{
				$1->setType(symbol->getType());
				$$->setType(symbol->getType());
			}
		}
	 }
	 ;
	 
 expression : logic_expression	
		{
			printf("expression : logic_expression\n");
			string temp = "expression : logic_expression";
			$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
		}
	   | variable ASSIGNOP logic_expression 
	   {
		printf("expression : variable ASSIGNOP logic_expression\n");
		string temp = "expression : variable ASSIGNOP logic_expression";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$3->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);
		//Important to check type:
		//fprintf(fp3,"Line# %d: type of 1: %s && type of 2: %s\n",$1->getStartLine(),$1->getType().c_str(),$3->getType().c_str());
		if($3->getType() == "FLOAT" && $1->getType() == "INT"){
			fprintf(fp3,"Line# %d: Warning: possible loss of data in assignment of FLOAT to INT\n",$1->getStartLine());
			errors++;
		}
		if($3->getType() == "VOID"){
			fprintf(fp3,"Line# 58: Void cannot be used in expression\n");
			errors++;
		}
	   }	
	   ;
			
logic_expression : rel_expression 
		{
			printf("logic_expression : rel_expression\n");
			string temp = "logic_expression : rel_expression";
			$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
		}	
		 | rel_expression LOGICOP rel_expression 	
		 {
			printf("logic_expression : rel_expression LOGICOP rel_expression\n");
			string temp = "logic_expression : rel_expression LOGICOP rel_expression";
			$$ = new SymbolInfo($1->getName(), "INT",$1->getStartLine(),$3->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);
		 }
		 ;
			
rel_expression	: simple_expression 
		{
			printf("rel_expression	: simple_expression\n");
			string temp = "rel_expression	: simple_expression";
			$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
		}
		| simple_expression RELOP simple_expression
		{
			printf("rel_expression	: simple_expression RELOP simple_expression\n");
			string temp = "rel_expression	: simple_expression RELOP simple_expression";
			$$ = new SymbolInfo($1->getName(), "INT",$1->getStartLine(),$3->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);
		}	
		;
				
simple_expression : term 
			{
				printf("simple_expression : term\n");
				string temp = "simple_expression : term";
				$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
				$$->addChild($1);
			}
		  | simple_expression ADDOP term 
		  {
			printf("simple_expression : simple_expression ADDOP term\n");
			string temp = "simple_expression : simple_expression ADDOP term";
			$$ = new SymbolInfo($1->getName(),$1->getType(),$1->getStartLine(),$3->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);$$->addChild($3);
		  }
		  ;
					
term :	unary_expression
	{
		printf("term : unary_expression\n");
		string temp = "term : unary_expression";
		$$ = new SymbolInfo($1->getName(),$1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	}
     |  term MULOP unary_expression
	 {
		printf("term : term MULOP unary_expression\n");
		string temp = "term : term MULOP unary_expression";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$3->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);
		//fprintf(fp3,"Type of MULOP : %s\n",$2->getName().c_str());
		if($1->getType() == "VOID" || $3->getType() == "VOID"){
			fprintf(fp3,"Line# %d: Void cannot be used in expression\n",$2->getStartLine());
			errors++;
		}
		if($2->getName() == "%"){
			if($1->getType() != "INT" || $3->getType() != "INT"){
				fprintf(fp3,"Line# %d: Operands of modulus must be integers\n",$2->getStartLine());
				errors++;
			}
		}
		if($2->getName() == "/" || $2->getName() == "%"){
			if($3->getName() == "0"){
				fprintf(fp3,"Line# %d: Warning: division by zero\n",$2->getStartLine());
				errors++;
			}	
		}
	 }
     ;

unary_expression : ADDOP unary_expression 
	{
		printf("unary_expression : ADDOP unary_expression\n");
		string temp = "unary_expression : ADDOP unary_expression";
		$$ = new SymbolInfo($1->getName(), $2->getType(),$1->getStartLine(),$2->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);
	} 
		 | NOT unary_expression 
		 {
			printf("unary_expression : NOT unary_expression\n");
			string temp = "unary_expression : NOT unary_expression";
			$$ = new SymbolInfo($1->getName(), "INT",$1->getStartLine(),$2->getEndLine(),temp);
			$$->addChild($1);$$->addChild($2);
		 }
		 | factor 
		 {
			printf("unary_expression : factor\n");
			string temp = "unary_expression : factor";
			$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
		 }
		 ;
	
factor	: variable 
	{
		printf("factor	: variable\n");
		string temp = "factor	: variable";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	}
	| ID LPAREN argument_list RPAREN
	{
		printf("factor	: ID LPAREN argument_list RPAREN\n");
		string temp = "factor	: ID LPAREN argument_list RPAREN";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$4->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);$$->addChild($4);
		SymbolInfo *symbol = myTable.lookUp($1->getName());
		if(symbol==NULL){
			fprintf(fp3,"Line# %d: Undeclared function '%s'\n",$1->getStartLine(),$1->getName().c_str());
			errors++;
		}else{
			$$->setType(symbol->getReturnType());
			if(symbol->getIsFunction()==false){
				fprintf(fp3,"Line# %d: '%s' is not a function\n",$1->getStartLine(),$1->getName().c_str());
				errors++;
			}else{
				if(symbol->getParameterList().size() < arguments_list.size()){
					fprintf(fp3,"Line# %d: Too many arguments to function '%s'\n",$1->getStartLine(),$1->getName().c_str());
					errors++;
				}else if(symbol->getParameterList().size() > arguments_list.size()){
					fprintf(fp3,"Line# %d: Too few arguments to function '%s'\n",$1->getStartLine(),$1->getName().c_str());
					errors++;
						
				}else{
					for(int i=0; i<arguments_list.size(); i++){
						for(char &c: arguments_list[i].first){
							c = tolower(c);
						}
						for(char &c: symbol->getParameterList()[i].first){
							c = tolower(c);
						}
						//fprintf(fp3,"Line# %d: Type of argument %d of '%s' is %s, but %s was given\n",$1->getStartLine(),i+1,$1->getName().c_str(),symbol->getParameterList()[i].first.c_str(),arguments_list[i].first.c_str());
						if(symbol->getParameterList()[i].first != arguments_list[i].first){
							fprintf(fp3,"Line# %d: Type mismatch for argument %d of '%s'\n",$1->getStartLine(),i+1,$1->getName().c_str());
							errors++;
						}
						for(char &c: arguments_list[i].first){
							c = toupper(c);
						}
						for(char &c: symbol->getParameterList()[i].first){
							c = toupper(c);
						}
					}
				}
				arguments_list.clear();
			}
		}
	}
	| LPAREN expression RPAREN
	{
		printf("factor	: LPAREN expression RPAREN\n");
		string temp = "factor	: LPAREN expression RPAREN";
		$$ = new SymbolInfo($2->getName(), $2->getType(),$1->getStartLine(),$3->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);$$->addChild($3);
	}
	| CONST_INT 
	{
		printf("factor	: CONST_INT\n");
		string temp = "factor	: CONST_INT";
		$$ = new SymbolInfo($1->getName(), "INT",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	}
	| CONST_FLOAT{
		printf("factor	: CONST_FLOAT\n");
		string temp = "factor	: CONST_FLOAT";
		$$ = new SymbolInfo($1->getName(), "FLOAT",$1->getStartLine(),$1->getEndLine(),temp);
		$$->addChild($1);
	}
	| variable INCOP 
	{
		printf("factor	: variable INCOP\n");
		string temp = "factor	: variable INCOP";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$2->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);
	}
	| variable DECOP
	{
		printf("factor	: variable DECOP\n");
		string temp = "factor	: variable DECOP";
		$$ = new SymbolInfo($1->getName(), $1->getType(),$1->getStartLine(),$2->getEndLine(),temp);
		$$->addChild($1);$$->addChild($2);	
	}
	;
	
argument_list : arguments
		{
				printf("argument_list : arguments\n");
				string temp = "argument_list : arguments";
				$$ = new SymbolInfo($1->getName(), "argument_list",$1->getStartLine(),$1->getEndLine(),temp);
				$$->addChild($1);
		}
		|
		{
			printf("argument_list : \n");
			string temp = "argument_list : ";
			$$ = new SymbolInfo("", "argument_list");
		}
		;
	
arguments : arguments COMMA logic_expression
			{
				printf("arguments : arguments COMMA logic_expression\n");
				string temp = "arguments : arguments COMMA logic_expression";
				$$ = new SymbolInfo($1->getName(), "arguments",$1->getStartLine(),$3->getEndLine(),temp);
				$$->addChild($1);$$->addChild($2);$$->addChild($3);
				arguments_list.push_back(make_pair($3->getType(),$3->getName()));
			}
	      | logic_expression
		  {
			printf("arguments : logic_expression\n");
			string temp = "arguments : logic_expression";
			$$ = new SymbolInfo($1->getName(), "arguments",$1->getStartLine(),$1->getEndLine(),temp);
			$$->addChild($1);
			arguments_list.push_back(make_pair($1->getType(),$1->getName()));
		  }
	      ;
 

%%
int main(int argc,char *argv[])
{
	FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	fp2= fopen("parsetree.txt","w");
	fclose(fp2);
	fp3= fopen("error.txt","w");
	fclose(fp3);
	output = fopen("output.asm","w");
	fclose(output);
	
	fp2= fopen("parsetree.txt","a");
	fp3= fopen("error.txt","a");
	output = fopen("output.asm","a");

	yyin=fp;
	yyparse();
	

	fclose(fp2);
	fclose(fp3);
	fclose(output);
	printf("Total Lines: %d\n",line_count);
	printf("Total Errors: %d\n",errors);
	return 0;
}

