/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     ID = 262,
     LPAREN = 263,
     RPAREN = 264,
     SEMICOLON = 265,
     LCURL = 266,
     RCURL = 267,
     LTHIRD = 268,
     RTHIRD = 269,
     COMMA = 270,
     ASSIGNOP = 271,
     RELOP = 272,
     LOGICOP = 273,
     ADDOP = 274,
     MULOP = 275,
     NOT = 276,
     INCOP = 277,
     DECOP = 278,
     PRINTLN = 279,
     RETURN = 280,
     INT = 281,
     FLOAT = 282,
     VOID = 283,
     CONST_INT = 284,
     CONST_FLOAT = 285,
     LOWER_THAN_ELSE = 286
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define ID 262
#define LPAREN 263
#define RPAREN 264
#define SEMICOLON 265
#define LCURL 266
#define RCURL 267
#define LTHIRD 268
#define RTHIRD 269
#define COMMA 270
#define ASSIGNOP 271
#define RELOP 272
#define LOGICOP 273
#define ADDOP 274
#define MULOP 275
#define NOT 276
#define INCOP 277
#define DECOP 278
#define PRINTLN 279
#define RETURN 280
#define INT 281
#define FLOAT 282
#define VOID 283
#define CONST_INT 284
#define CONST_FLOAT 285
#define LOWER_THAN_ELSE 286




/* Copy the first part of user declarations.  */
#line 1 "2005054.y"

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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 657 "2005054.y"
{
    SymbolInfo* symbol_info;
}
/* Line 193 of yacc.c.  */
#line 819 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 832 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    23,
      29,    36,    42,    47,    51,    54,    56,    60,    63,    67,
      69,    71,    73,    77,    84,    86,    91,    95,    97,   100,
     102,   104,   106,   114,   120,   128,   134,   140,   144,   146,
     149,   151,   156,   158,   162,   164,   168,   170,   174,   176,
     180,   182,   186,   189,   192,   194,   196,   201,   205,   207,
     209,   212,   215,   217,   218,   222
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    34,    35,    -1,    35,    -1,
      40,    -1,    36,    -1,    37,    -1,    41,     7,     8,    38,
       9,    10,    -1,    41,     7,     8,     9,    10,    -1,    41,
       7,     8,    38,     9,    39,    -1,    41,     7,     8,     9,
      39,    -1,    38,    15,    41,     7,    -1,    38,    15,    41,
      -1,    41,     7,    -1,    41,    -1,    11,    43,    12,    -1,
      11,    12,    -1,    41,    42,    10,    -1,    26,    -1,    27,
      -1,    28,    -1,    42,    15,     7,    -1,    42,    15,     7,
      13,    29,    14,    -1,     7,    -1,     7,    13,    29,    14,
      -1,     7,    16,    29,    -1,    44,    -1,    43,    44,    -1,
      40,    -1,    45,    -1,    39,    -1,     5,     8,    45,    45,
      47,     9,    44,    -1,     3,     8,    47,     9,    44,    -1,
       3,     8,    47,     9,    44,     4,    44,    -1,     6,     8,
      47,     9,    44,    -1,    24,     8,     7,     9,    10,    -1,
      25,    47,    10,    -1,    10,    -1,    47,    10,    -1,     7,
      -1,     7,    13,    47,    14,    -1,    48,    -1,    46,    16,
      48,    -1,    49,    -1,    49,    18,    49,    -1,    50,    -1,
      50,    17,    50,    -1,    51,    -1,    50,    19,    51,    -1,
      52,    -1,    51,    20,    52,    -1,    19,    52,    -1,    21,
      52,    -1,    53,    -1,    46,    -1,     7,     8,    54,     9,
      -1,     8,    47,     9,    -1,    29,    -1,    30,    -1,    46,
      22,    -1,    46,    23,    -1,    55,    -1,    -1,    55,    15,
      48,    -1,    48,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   671,   671,   683,   690,   699,   707,   714,   724,   734,
     745,   755,   767,   782,   790,   804,   816,   826,   837,   846,
     856,   865,   876,   887,   900,   909,   920,   926,   933,   942,
     950,   957,   964,   971,   978,   985,   992,   999,  1009,  1016,
    1025,  1040,  1066,  1073,  1092,  1099,  1108,  1115,  1124,  1131,
    1140,  1147,  1173,  1180,  1187,  1196,  1203,  1251,  1258,  1265,
    1271,  1278,  1287,  1295,  1302,  1310
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "ID",
  "LPAREN", "RPAREN", "SEMICOLON", "LCURL", "RCURL", "LTHIRD", "RTHIRD",
  "COMMA", "ASSIGNOP", "RELOP", "LOGICOP", "ADDOP", "MULOP", "NOT",
  "INCOP", "DECOP", "PRINTLN", "RETURN", "INT", "FLOAT", "VOID",
  "CONST_INT", "CONST_FLOAT", "LOWER_THAN_ELSE", "$accept", "start",
  "program", "unit", "func_declaration", "func_definition",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    36,
      37,    37,    38,    38,    38,    38,    39,    39,    40,    41,
      41,    41,    42,    42,    42,    42,    42,    43,    43,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    54,    54,    55,    55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     3,     2,     3,     1,
       1,     1,     3,     6,     1,     4,     3,     1,     2,     1,
       1,     1,     7,     5,     7,     5,     5,     3,     1,     2,
       1,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     2,     2,     1,     1,     4,     3,     1,     1,
       2,     2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    20,    21,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    24,     0,     0,     0,     0,    18,     0,
       0,     0,    15,     0,    26,    22,     9,     0,    11,     0,
       0,    14,    25,     0,     0,     0,     0,    40,     0,    38,
      17,     0,     0,     0,     0,    58,    59,    31,    29,     0,
       0,    27,    30,    55,     0,    42,    44,    46,    48,    50,
      54,     8,    10,    13,     0,     0,     0,     0,    63,     0,
       0,    55,    52,    53,     0,     0,    24,    16,    28,     0,
      60,    61,    39,     0,     0,     0,     0,    12,    23,     0,
       0,     0,    65,     0,    62,     0,    57,     0,    37,    43,
      45,    47,    49,    51,     0,     0,     0,    56,     0,    41,
       0,    33,     0,    35,    64,    36,     0,     0,    34,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    21,    47,    48,    49,
      14,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    93,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -60
static const yytype_int16 yypact[] =
{
      27,   -60,   -60,   -60,    28,    27,   -60,   -60,   -60,   -60,
      45,   -60,   -60,     5,     4,    -4,    19,    37,   -60,    49,
       6,    17,    56,    54,   -60,    60,   -60,    69,   -60,    51,
      27,   -60,   -60,    53,    70,    75,    76,    26,   153,   -60,
     -60,   153,   153,    77,   153,   -60,   -60,   -60,   -60,    79,
      97,   -60,   -60,    14,    81,   -60,    71,    40,    67,   -60,
     -60,   -60,   -60,    85,    87,   153,   149,   153,   153,   153,
     101,    42,   -60,   -60,    99,   102,    34,   -60,   -60,   153,
     -60,   -60,   -60,   153,   153,   153,   153,   -60,   -60,   104,
     149,   105,   -60,   106,    96,   103,   -60,   110,   -60,   -60,
     -60,   115,    67,   -60,   125,   153,   125,   -60,   153,   -60,
     119,   116,   128,   -60,   -60,   -60,   125,   125,   -60,   -60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -60,   -60,   -60,   133,   -60,   -60,   -60,   -17,    41,    10,
     -60,   -60,   -46,   -55,   -41,   -36,   -59,    57,    55,    58,
     -35,   -60,   -60,   -60
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      71,    71,    70,    28,    78,    20,    72,    73,    75,    92,
      10,    90,    62,    15,    18,    10,    26,    27,    16,    19,
      99,    17,     1,     2,     3,    22,    29,    71,    11,    89,
      79,    91,    30,    95,    68,   105,    80,    81,    71,    69,
      63,     9,    71,    71,    71,    71,     9,    16,    23,   114,
      17,   103,    13,     1,     2,     3,    25,    84,   111,    85,
     113,    61,    27,    31,    80,    81,    24,    71,    32,   112,
     118,   119,    34,    33,    35,    36,    37,    38,    65,    39,
      27,    40,    64,    66,    67,    74,    76,    86,    41,    83,
      42,    82,    87,    43,    44,     1,     2,     3,    45,    46,
      34,    88,    35,    36,    37,    38,    97,    39,    27,    77,
      96,   108,    98,   104,   106,   107,    41,   109,    42,   110,
     116,    43,    44,     1,     2,     3,    45,    46,    34,   115,
      35,    36,    37,    38,    85,    39,    27,   117,    12,   101,
     100,     0,     0,   102,    41,     0,    42,     0,     0,    43,
      44,     1,     2,     3,    45,    46,    37,    38,     0,    39,
      37,    38,     0,     0,     0,     0,     0,     0,    41,     0,
      42,     0,    41,     0,    42,     0,     0,     0,    45,    46,
       0,     0,    45,    46
};

static const yytype_int8 yycheck[] =
{
      41,    42,    38,    20,    50,     9,    41,    42,    44,    68,
       0,    66,    29,     8,    10,     5,    10,    11,    13,    15,
      79,    16,    26,    27,    28,    15,     9,    68,     0,    65,
      16,    67,    15,    69,     8,    90,    22,    23,    79,    13,
      30,     0,    83,    84,    85,    86,     5,    13,    29,   108,
      16,    86,     7,    26,    27,    28,     7,    17,   104,    19,
     106,    10,    11,     7,    22,    23,    29,   108,    14,   105,
     116,   117,     3,    13,     5,     6,     7,     8,     8,    10,
      11,    12,    29,     8,     8,     8,     7,    20,    19,    18,
      21,    10,     7,    24,    25,    26,    27,    28,    29,    30,
       3,    14,     5,     6,     7,     8,     7,    10,    11,    12,
       9,    15,    10,     9,     9,     9,    19,    14,    21,     9,
       4,    24,    25,    26,    27,    28,    29,    30,     3,    10,
       5,     6,     7,     8,    19,    10,    11,     9,     5,    84,
      83,    -1,    -1,    85,    19,    -1,    21,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,     7,     8,    -1,    10,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      21,    -1,    19,    -1,    21,    -1,    -1,    -1,    29,    30,
      -1,    -1,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    27,    28,    33,    34,    35,    36,    37,    40,
      41,     0,    35,     7,    42,     8,    13,    16,    10,    15,
       9,    38,    41,    29,    29,     7,    10,    11,    39,     9,
      15,     7,    14,    13,     3,     5,     6,     7,     8,    10,
      12,    19,    21,    24,    25,    29,    30,    39,    40,    41,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    10,    39,    41,    29,     8,     8,     8,     8,    13,
      47,    46,    52,    52,     8,    47,     7,    12,    44,    16,
      22,    23,    10,    18,    17,    19,    20,     7,    14,    47,
      45,    47,    48,    54,    55,    47,     9,     7,    10,    48,
      49,    50,    51,    52,     9,    45,     9,     9,    15,    14,
       9,    44,    47,    44,    48,    10,     4,     9,    44,    44
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 672 "2005054.y"
    {
		printf("start : program\n");
		string temp = "start : program";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "start",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		parse_tree_print((yyval.symbol_info),0);
		generate_code((yyval.symbol_info));

	}
    break;

  case 3:
#line 684 "2005054.y"
    {
		printf("program : program unit\n");
		string temp = "program : program unit";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), "program",(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
	}
    break;

  case 4:
#line 691 "2005054.y"
    {
		printf("program : unit\n");
		string temp = "program : unit";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "program",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	}
    break;

  case 5:
#line 700 "2005054.y"
    {
		printf("unit : var_declaration\n");
		string temp = "unit : var_declaration";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "unit",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));

	 }
    break;

  case 6:
#line 708 "2005054.y"
    {
		printf("unit : func_declaration\n");
		string temp = "unit : func_declaration";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "unit",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	 }
    break;

  case 7:
#line 715 "2005054.y"
    {
		printf("unit : func_definition\n");
		string temp = "unit : func_definition";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "unit",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	 
	 }
    break;

  case 8:
#line 725 "2005054.y"
    {
			printf("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n");
			string temp = "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(2) - (6)].symbol_info)->getName(), "func_declaration",(yyvsp[(2) - (6)].symbol_info)->getStartLine(),(yyvsp[(5) - (6)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(6) - (6)].symbol_info));

			check_and_insert_func_in_symbol_table((yyvsp[(2) - (6)].symbol_info)->getName(),(yyvsp[(1) - (6)].symbol_info)->getName(),false,true,(yyvsp[(2) - (6)].symbol_info)->getStartLine());

		}
    break;

  case 9:
#line 735 "2005054.y"
    {
			printf("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n");
			string temp = "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(2) - (5)].symbol_info)->getName(), "func_declaration",(yyvsp[(2) - (5)].symbol_info)->getStartLine(),(yyvsp[(5) - (5)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (5)].symbol_info));

			check_and_insert_func_in_symbol_table((yyvsp[(2) - (5)].symbol_info)->getName(),(yyvsp[(1) - (5)].symbol_info)->getName(),false,true,(yyvsp[(2) - (5)].symbol_info)->getStartLine());
		}
    break;

  case 10:
#line 746 "2005054.y"
    {
		
			//fprintf(output,"current function from defintion %s;\n",$2->getName.c_str());
			printf("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n");
			string temp = "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(2) - (6)].symbol_info)->getName(), "func_definition",(yyvsp[(2) - (6)].symbol_info)->getStartLine(),(yyvsp[(6) - (6)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(6) - (6)].symbol_info));
			check_and_insert_func_in_symbol_table((yyvsp[(2) - (6)].symbol_info)->getName(),(yyvsp[(1) - (6)].symbol_info)->getName(),true,false,(yyvsp[(2) - (6)].symbol_info)->getStartLine());
		}
    break;

  case 11:
#line 756 "2005054.y"
    {
			//fprintf(output,"current function from defintion %s;\n",current_func.c_str());
			printf("func_definition : type_specifier ID LPAREN RPAREN compound_statement\n");
			string temp = "func_definition : type_specifier ID LPAREN RPAREN compound_statement";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(2) - (5)].symbol_info)->getName(), "func_definition",(yyvsp[(2) - (5)].symbol_info)->getStartLine(),(yyvsp[(5) - (5)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (5)].symbol_info));
			check_and_insert_func_in_symbol_table((yyvsp[(2) - (5)].symbol_info)->getName(),(yyvsp[(1) - (5)].symbol_info)->getName(),true,false,(yyvsp[(2) - (5)].symbol_info)->getStartLine());
		}
    break;

  case 12:
#line 768 "2005054.y"
    {
			printf("parameter_list  : parameter_list COMMA type_specifier ID\n");
			string temp = "parameter_list  : parameter_list COMMA type_specifier ID";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(4) - (4)].symbol_info)->getName(), "parameter_list",(yyvsp[(4) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (4)].symbol_info));
			for(pair<string,string> p: list){
				if(p.second == (yyvsp[(4) - (4)].symbol_info)->getName()){
					fprintf(fp3,"Line# %d: Redefinition of parameter '%s'\n",(yyvsp[(4) - (4)].symbol_info)->getStartLine(),(yyvsp[(4) - (4)].symbol_info)->getName().c_str());
					errors++;
				}
			}
			
			list.push_back(make_pair((yyvsp[(3) - (4)].symbol_info)->getName(),(yyvsp[(4) - (4)].symbol_info)->getName()));
		}
    break;

  case 13:
#line 783 "2005054.y"
    {
			printf("parameter_list  : parameter_list COMMA type_specifier\n");
			string temp = "parameter_list  : parameter_list COMMA type_specifier";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(3) - (3)].symbol_info)->getName(), "parameter_list",(yyvsp[(3) - (3)].symbol_info)->getStartLine(),(yyvsp[(1) - (3)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
			list.push_back(make_pair((yyvsp[(3) - (3)].symbol_info)->getName(),""));
		}
    break;

  case 14:
#line 791 "2005054.y"
    {
			printf("parameter_list  : type_specifier ID\n");
			string temp = "parameter_list  : type_specifier ID";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(2) - (2)].symbol_info)->getName(), "parameter_list",(yyvsp[(2) - (2)].symbol_info)->getStartLine(),(yyvsp[(1) - (2)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
			for(pair<string,string> p: list){
				if(p.second == (yyvsp[(2) - (2)].symbol_info)->getName()){
					fprintf(fp3,"Line# %d: Redefinition of parameter '%s'\n",(yyvsp[(2) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getName().c_str());
					errors++;
				}
			}
			list.push_back(make_pair((yyvsp[(1) - (2)].symbol_info)->getName(),(yyvsp[(2) - (2)].symbol_info)->getName()));
		}
    break;

  case 15:
#line 805 "2005054.y"
    {
			printf("parameter_list  : type_specifier\n");
			string temp = "parameter_list  : type_specifier";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "parameter_list",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));

			list.push_back(make_pair((yyvsp[(1) - (1)].symbol_info)->getName(),""));
		}
    break;

  case 16:
#line 817 "2005054.y"
    {
				printf("compound_statement : LCURL statements RCURL\n");
				string temp = "compound_statement : LCURL statements RCURL";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), "compound_statement",(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
				myTable.printAllScope();
    			myTable.exitScope();
				
			}
    break;

  case 17:
#line 827 "2005054.y"
    {
				printf("compound_statement : LCURL RCURL\n");
				string temp = "compound_statement : LCURL RCURL";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), "compound_statement",(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
				myTable.printAllScope();
    			myTable.exitScope();
			}
    break;

  case 18:
#line 838 "2005054.y"
    {
	printf("var_declaration : type_specifier declaration_list SEMICOLON\n");
	string temp = "var_declaration : type_specifier declaration_list SEMICOLON";
	(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), "var_declaration",(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
	(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
}
    break;

  case 19:
#line 847 "2005054.y"
    {
			printf("type_specifier	: INT\n");
			string temp = "type_specifier	: INT";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "type_specifier",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));

			stored_type = "INT";

		}
    break;

  case 20:
#line 857 "2005054.y"
    {
			printf("type_specifier	: FLOAT\n");
			string temp = "type_specifier	: FLOAT";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "type_specifier",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));

			stored_type = "FLOAT";
		}
    break;

  case 21:
#line 866 "2005054.y"
    {
			printf("type_specifier	: VOID\n");
			string temp = "type_specifier	: VOID";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "type_specifier",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));

			stored_type = "VOID";
		}
    break;

  case 22:
#line 877 "2005054.y"
    {
				printf("declaration_list : declaration_list COMMA ID\n");
				string temp = "declaration_list : declaration_list COMMA ID";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(3) - (3)].symbol_info)->getName(), "declaration_list",(yyvsp[(3) - (3)].symbol_info)->getStartLine(),(yyvsp[(1) - (3)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
				(yyval.symbol_info)->setSymbolDeclaration((yyvsp[(1) - (3)].symbol_info)->getSymbolDeclaration());
				(yyval.symbol_info)->addDeclaration((yyvsp[(3) - (3)].symbol_info));
				check_and_insert_var_in_symbol_table((yyvsp[(3) - (3)].symbol_info)->getName(),stored_type);
				
			}
    break;

  case 23:
#line 888 "2005054.y"
    {
			printf("declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE\n");
			string temp = "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(3) - (6)].symbol_info)->getName(), "declaration_list",(yyvsp[(3) - (6)].symbol_info)->getStartLine(),(yyvsp[(1) - (6)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (6)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(6) - (6)].symbol_info));
			(yyval.symbol_info)->setSymbolDeclaration((yyvsp[(1) - (6)].symbol_info)->getSymbolDeclaration());
			(yyvsp[(3) - (6)].symbol_info)->setIsArray(true);
			(yyvsp[(3) - (6)].symbol_info)->setArraySize(stoi((yyvsp[(5) - (6)].symbol_info)->getName()));
			(yyval.symbol_info)->addDeclaration((yyvsp[(3) - (6)].symbol_info));

			check_and_insert_array_in_symbol_table((yyvsp[(3) - (6)].symbol_info)->getName(),stored_type,(yyvsp[(5) - (6)].symbol_info)->getName());
		}
    break;

  case 24:
#line 901 "2005054.y"
    {
			printf("declaration_list : ID\n");
			string temp = "declaration_list : ID";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "declaration_list",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
			(yyval.symbol_info)->addDeclaration((yyvsp[(1) - (1)].symbol_info));
			check_and_insert_var_in_symbol_table((yyvsp[(1) - (1)].symbol_info)->getName(),stored_type);
		  }
    break;

  case 25:
#line 910 "2005054.y"
    {
			printf("declaration_list : ID LSQUARE CONST_INT RSQUARE\n");
			string temp = "declaration_list : ID LSQUARE CONST_INT RSQUARE";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (4)].symbol_info)->getName(), "declaration_list",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (4)].symbol_info));
			(yyvsp[(1) - (4)].symbol_info)->setIsArray(true);
			(yyvsp[(1) - (4)].symbol_info)->setArraySize(stoi((yyvsp[(2) - (4)].symbol_info)->getName()));
			(yyval.symbol_info)->addDeclaration((yyvsp[(1) - (4)].symbol_info));
			check_and_insert_array_in_symbol_table((yyvsp[(1) - (4)].symbol_info)->getName(),stored_type,(yyvsp[(3) - (4)].symbol_info)->getName());
		  }
    break;

  case 26:
#line 921 "2005054.y"
    {
			check_and_insert_var_in_symbol_table((yyvsp[(1) - (3)].symbol_info)->getName(),stored_type);
		  }
    break;

  case 27:
#line 927 "2005054.y"
    {
			printf("statements : statement\n");
			string temp = "statements : statement";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "statements",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		}
    break;

  case 28:
#line 934 "2005054.y"
    {
		printf("statements : statements statement\n");
		string temp = "statements : statements statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), "statements",(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
	   }
    break;

  case 29:
#line 943 "2005054.y"
    {	
			printf("statement : var_declaration\n");
			string temp = "statement : var_declaration";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "statement",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));

		}
    break;

  case 30:
#line 951 "2005054.y"
    {
		printf("statement : expression_statement\n");
		string temp = "statement : expression_statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "statement",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	  }
    break;

  case 31:
#line 958 "2005054.y"
    {
		printf("statement : compound_statement\n");
		string temp = "statement : compound_statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "statement",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	  }
    break;

  case 32:
#line 965 "2005054.y"
    {
		printf("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n");
		string temp = "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (7)].symbol_info)->getName(), "statement",(yyvsp[(1) - (7)].symbol_info)->getStartLine(),(yyvsp[(7) - (7)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(6) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(7) - (7)].symbol_info));
	  }
    break;

  case 33:
#line 972 "2005054.y"
    {
		printf("statement : IF LPAREN expression RPAREN statement\n");
		string temp = "statement : IF LPAREN expression RPAREN statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (5)].symbol_info)->getName(), "statement",(yyvsp[(1) - (5)].symbol_info)->getStartLine(),(yyvsp[(5) - (5)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (5)].symbol_info));
	  }
    break;

  case 34:
#line 979 "2005054.y"
    {
		printf("statement : IF LPAREN expression RPAREN statement ELSE statement\n");
		string temp = "statement : IF LPAREN expression RPAREN statement ELSE statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (7)].symbol_info)->getName(), "statement",(yyvsp[(1) - (7)].symbol_info)->getStartLine(),(yyvsp[(7) - (7)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(6) - (7)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(7) - (7)].symbol_info));
	  }
    break;

  case 35:
#line 986 "2005054.y"
    {
		printf("statement : WHILE LPAREN expression RPAREN statement\n");
		string temp = "statement : WHILE LPAREN expression RPAREN statement";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (5)].symbol_info)->getName(), "statement",(yyvsp[(1) - (5)].symbol_info)->getStartLine(),(yyvsp[(5) - (5)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (5)].symbol_info));
	  }
    break;

  case 36:
#line 993 "2005054.y"
    {
		printf("statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n");
		string temp = "statement : PRINTLN LPAREN ID RPAREN SEMICOLON";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (5)].symbol_info)->getName(), "statement",(yyvsp[(1) - (5)].symbol_info)->getStartLine(),(yyvsp[(5) - (5)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (5)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(5) - (5)].symbol_info));
	  }
    break;

  case 37:
#line 1000 "2005054.y"
    {
		printf("statement : RETURN expression SEMICOLON\n");
		string temp = "statement : RETURN expression SEMICOLON";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), "statement",(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
		//fprintf(output,"Name of current function from rule: %s\n",current_func.c_str());
		(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
	  }
    break;

  case 38:
#line 1010 "2005054.y"
    {
				printf("expression_statement : SEMICOLON\n");
				string temp = "expression_statement : SEMICOLON";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "expression_statement",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
			}
    break;

  case 39:
#line 1017 "2005054.y"
    {
				printf("expression_statement : expression SEMICOLON\n");
				string temp = "expression_statement : expression SEMICOLON";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), "expression_statement",(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
			}
    break;

  case 40:
#line 1026 "2005054.y"
    {
		printf("variable : ID\n");
		string temp = "variable : ID";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		SymbolInfo *symbol = myTable.lookUp((yyvsp[(1) - (1)].symbol_info)->getName());
		if(symbol==NULL){
			fprintf(fp3,"Line# %d: Undeclared variable '%s'\n",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getName().c_str());
			errors++;
		}else{
			(yyvsp[(1) - (1)].symbol_info)->setType(symbol->getType());
			(yyval.symbol_info)->setType(symbol->getType());
		}
	}
    break;

  case 41:
#line 1041 "2005054.y"
    {
		printf("variable : ID LSQUARE expression RSQUARE\n");
		string temp = "variable : ID LSQUARE expression RSQUARE";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (4)].symbol_info)->getName(), (yyvsp[(1) - (4)].symbol_info)->getType(),(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(4) - (4)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (4)].symbol_info));
		if((yyvsp[(3) - (4)].symbol_info)->getType()!="INT"){
			fprintf(fp3,"Line# %d: Array subscript is not an integer\n",(yyvsp[(3) - (4)].symbol_info)->getStartLine());
			errors++;
		}
		SymbolInfo *symbol = myTable.lookUp((yyvsp[(1) - (4)].symbol_info)->getName());
		if(symbol==NULL){
			fprintf(fp3,"Line# %d: Undeclared variable '%s'\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
			errors++;
		}else{
			if(symbol->getIsArray()==false){
				fprintf(fp3,"Line# %d: '%s' is not an array\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
				errors++;
			}else{
				(yyvsp[(1) - (4)].symbol_info)->setType(symbol->getType());
				(yyval.symbol_info)->setType(symbol->getType());
			}
		}
	 }
    break;

  case 42:
#line 1067 "2005054.y"
    {
			printf("expression : logic_expression\n");
			string temp = "expression : logic_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		}
    break;

  case 43:
#line 1074 "2005054.y"
    {
		printf("expression : variable ASSIGNOP logic_expression\n");
		string temp = "expression : variable ASSIGNOP logic_expression";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), (yyvsp[(1) - (3)].symbol_info)->getType(),(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
		//Important to check type:
		//fprintf(fp3,"Line# %d: type of 1: %s && type of 2: %s\n",$1->getStartLine(),$1->getType().c_str(),$3->getType().c_str());
		if((yyvsp[(3) - (3)].symbol_info)->getType() == "FLOAT" && (yyvsp[(1) - (3)].symbol_info)->getType() == "INT"){
			fprintf(fp3,"Line# %d: Warning: possible loss of data in assignment of FLOAT to INT\n",(yyvsp[(1) - (3)].symbol_info)->getStartLine());
			errors++;
		}
		if((yyvsp[(3) - (3)].symbol_info)->getType() == "VOID"){
			fprintf(fp3,"Line# 58: Void cannot be used in expression\n");
			errors++;
		}
	   }
    break;

  case 44:
#line 1093 "2005054.y"
    {
			printf("logic_expression : rel_expression\n");
			string temp = "logic_expression : rel_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		}
    break;

  case 45:
#line 1100 "2005054.y"
    {
			printf("logic_expression : rel_expression LOGICOP rel_expression\n");
			string temp = "logic_expression : rel_expression LOGICOP rel_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), "INT",(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
		 }
    break;

  case 46:
#line 1109 "2005054.y"
    {
			printf("rel_expression	: simple_expression\n");
			string temp = "rel_expression	: simple_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		}
    break;

  case 47:
#line 1116 "2005054.y"
    {
			printf("rel_expression	: simple_expression RELOP simple_expression\n");
			string temp = "rel_expression	: simple_expression RELOP simple_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), "INT",(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
		}
    break;

  case 48:
#line 1125 "2005054.y"
    {
				printf("simple_expression : term\n");
				string temp = "simple_expression : term";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
			}
    break;

  case 49:
#line 1132 "2005054.y"
    {
			printf("simple_expression : simple_expression ADDOP term\n");
			string temp = "simple_expression : simple_expression ADDOP term";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(),(yyvsp[(1) - (3)].symbol_info)->getType(),(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
		  }
    break;

  case 50:
#line 1141 "2005054.y"
    {
		printf("term : unary_expression\n");
		string temp = "term : unary_expression";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(),(yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	}
    break;

  case 51:
#line 1148 "2005054.y"
    {
		printf("term : term MULOP unary_expression\n");
		string temp = "term : term MULOP unary_expression";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), (yyvsp[(1) - (3)].symbol_info)->getType(),(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
		//fprintf(fp3,"Type of MULOP : %s\n",$2->getName().c_str());
		if((yyvsp[(1) - (3)].symbol_info)->getType() == "VOID" || (yyvsp[(3) - (3)].symbol_info)->getType() == "VOID"){
			fprintf(fp3,"Line# %d: Void cannot be used in expression\n",(yyvsp[(2) - (3)].symbol_info)->getStartLine());
			errors++;
		}
		if((yyvsp[(2) - (3)].symbol_info)->getName() == "%"){
			if((yyvsp[(1) - (3)].symbol_info)->getType() != "INT" || (yyvsp[(3) - (3)].symbol_info)->getType() != "INT"){
				fprintf(fp3,"Line# %d: Operands of modulus must be integers\n",(yyvsp[(2) - (3)].symbol_info)->getStartLine());
				errors++;
			}
		}
		if((yyvsp[(2) - (3)].symbol_info)->getName() == "/" || (yyvsp[(2) - (3)].symbol_info)->getName() == "%"){
			if((yyvsp[(3) - (3)].symbol_info)->getName() == "0"){
				fprintf(fp3,"Line# %d: Warning: division by zero\n",(yyvsp[(2) - (3)].symbol_info)->getStartLine());
				errors++;
			}	
		}
	 }
    break;

  case 52:
#line 1174 "2005054.y"
    {
		printf("unary_expression : ADDOP unary_expression\n");
		string temp = "unary_expression : ADDOP unary_expression";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), (yyvsp[(2) - (2)].symbol_info)->getType(),(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
	}
    break;

  case 53:
#line 1181 "2005054.y"
    {
			printf("unary_expression : NOT unary_expression\n");
			string temp = "unary_expression : NOT unary_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), "INT",(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
		 }
    break;

  case 54:
#line 1188 "2005054.y"
    {
			printf("unary_expression : factor\n");
			string temp = "unary_expression : factor";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		 }
    break;

  case 55:
#line 1197 "2005054.y"
    {
		printf("factor	: variable\n");
		string temp = "factor	: variable";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), (yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	}
    break;

  case 56:
#line 1204 "2005054.y"
    {
		printf("factor	: ID LPAREN argument_list RPAREN\n");
		string temp = "factor	: ID LPAREN argument_list RPAREN";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (4)].symbol_info)->getName(), (yyvsp[(1) - (4)].symbol_info)->getType(),(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(4) - (4)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (4)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(4) - (4)].symbol_info));
		SymbolInfo *symbol = myTable.lookUp((yyvsp[(1) - (4)].symbol_info)->getName());
		if(symbol==NULL){
			fprintf(fp3,"Line# %d: Undeclared function '%s'\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
			errors++;
		}else{
			(yyval.symbol_info)->setType(symbol->getReturnType());
			if(symbol->getIsFunction()==false){
				fprintf(fp3,"Line# %d: '%s' is not a function\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
				errors++;
			}else{
				if(symbol->getParameterList().size() < arguments_list.size()){
					fprintf(fp3,"Line# %d: Too many arguments to function '%s'\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
					errors++;
				}else if(symbol->getParameterList().size() > arguments_list.size()){
					fprintf(fp3,"Line# %d: Too few arguments to function '%s'\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
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
							fprintf(fp3,"Line# %d: Type mismatch for argument %d of '%s'\n",(yyvsp[(1) - (4)].symbol_info)->getStartLine(),i+1,(yyvsp[(1) - (4)].symbol_info)->getName().c_str());
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
    break;

  case 57:
#line 1252 "2005054.y"
    {
		printf("factor	: LPAREN expression RPAREN\n");
		string temp = "factor	: LPAREN expression RPAREN";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(2) - (3)].symbol_info)->getName(), (yyvsp[(2) - (3)].symbol_info)->getType(),(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
	}
    break;

  case 58:
#line 1259 "2005054.y"
    {
		printf("factor	: CONST_INT\n");
		string temp = "factor	: CONST_INT";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "INT",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	}
    break;

  case 59:
#line 1265 "2005054.y"
    {
		printf("factor	: CONST_FLOAT\n");
		string temp = "factor	: CONST_FLOAT";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "FLOAT",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
	}
    break;

  case 60:
#line 1272 "2005054.y"
    {
		printf("factor	: variable INCOP\n");
		string temp = "factor	: variable INCOP";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), (yyvsp[(1) - (2)].symbol_info)->getType(),(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));
	}
    break;

  case 61:
#line 1279 "2005054.y"
    {
		printf("factor	: variable DECOP\n");
		string temp = "factor	: variable DECOP";
		(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (2)].symbol_info)->getName(), (yyvsp[(1) - (2)].symbol_info)->getType(),(yyvsp[(1) - (2)].symbol_info)->getStartLine(),(yyvsp[(2) - (2)].symbol_info)->getEndLine(),temp);
		(yyval.symbol_info)->addChild((yyvsp[(1) - (2)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (2)].symbol_info));	
	}
    break;

  case 62:
#line 1288 "2005054.y"
    {
				printf("argument_list : arguments\n");
				string temp = "argument_list : arguments";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "argument_list",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
		}
    break;

  case 63:
#line 1295 "2005054.y"
    {
			printf("argument_list : \n");
			string temp = "argument_list : ";
			(yyval.symbol_info) = new SymbolInfo("", "argument_list");
		}
    break;

  case 64:
#line 1303 "2005054.y"
    {
				printf("arguments : arguments COMMA logic_expression\n");
				string temp = "arguments : arguments COMMA logic_expression";
				(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (3)].symbol_info)->getName(), "arguments",(yyvsp[(1) - (3)].symbol_info)->getStartLine(),(yyvsp[(3) - (3)].symbol_info)->getEndLine(),temp);
				(yyval.symbol_info)->addChild((yyvsp[(1) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(2) - (3)].symbol_info));(yyval.symbol_info)->addChild((yyvsp[(3) - (3)].symbol_info));
				arguments_list.push_back(make_pair((yyvsp[(3) - (3)].symbol_info)->getType(),(yyvsp[(3) - (3)].symbol_info)->getName()));
			}
    break;

  case 65:
#line 1311 "2005054.y"
    {
			printf("arguments : logic_expression\n");
			string temp = "arguments : logic_expression";
			(yyval.symbol_info) = new SymbolInfo((yyvsp[(1) - (1)].symbol_info)->getName(), "arguments",(yyvsp[(1) - (1)].symbol_info)->getStartLine(),(yyvsp[(1) - (1)].symbol_info)->getEndLine(),temp);
			(yyval.symbol_info)->addChild((yyvsp[(1) - (1)].symbol_info));
			arguments_list.push_back(make_pair((yyvsp[(1) - (1)].symbol_info)->getType(),(yyvsp[(1) - (1)].symbol_info)->getName()));
		  }
    break;


/* Line 1267 of yacc.c.  */
#line 2939 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1321 "2005054.y"

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


