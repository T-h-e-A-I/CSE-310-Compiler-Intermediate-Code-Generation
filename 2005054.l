%{
#include <stdio.h>
#include<string>
#include<cstring>
#include "2005054_SymbolTable.h"
#include "2005054_SymbolInfo.h"
#include "y.tab.h"

using namespace std;

extern YYSTYPE yylval;

void yyerror(char *);

int line_count = 1;
int line_number = 1;
int errors = 0;
int warnings = 0;
bool inside_global_scope = true;
vector<pair<string,string> > list;


FILE *log_file = freopen("log.txt","w",stdout);
SymbolTable myTable(11);


%}

%option noyywrap


NEW_LINE (\r)?\n

%%
{NEW_LINE} {
    line_count++;
    line_number++;
}
[ \t]+  
if {
    string temp = "IF";
    SymbolInfo* send = new SymbolInfo(yytext, "IF", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <IF> Lexeme if found\n", line_number);
    return IF; 
}
else {
    string temp = "ELSE";
    SymbolInfo* send = new SymbolInfo(yytext, "ELSE", line_count, line_count, true, temp);
    yylval.symbol_info = send; 
    printf("Line# %d: Token <ELSE> Lexeme else found\n", line_number);
    return ELSE; 
}
for { 
    string temp = "FOR";
    SymbolInfo* send = new SymbolInfo(yytext, "FOR", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <FOR> Lexeme for found\n", line_number);
    return FOR;
}
while {
    string temp = "WHILE";
    SymbolInfo* send = new SymbolInfo(yytext, "WHILE", line_count, line_count, true, temp);
    yylval.symbol_info = send; 
    printf("Line# %d: Token <WHILE> Lexeme while found\n", line_number);
    return WHILE; 
}

int { 
    string temp = "INT";
    SymbolInfo* send = new SymbolInfo(yytext, "INT", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <INT> Lexeme int found\n", line_number);
    return INT;
}
float { 
    string temp = "FLOAT";
    SymbolInfo* send = new SymbolInfo(yytext, "FLOAT", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <FLOAT> Lexeme float found\n", line_number);
    return FLOAT; 
}
void { 
    string temp = "VOID";
    SymbolInfo* send = new SymbolInfo(yytext, "VOID", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <VOID> Lexeme void found\n", line_number);
    return VOID; 
}
return {
    string temp = "RETURN";
    SymbolInfo* send = new SymbolInfo(yytext, "RETURN", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RETURN> Lexeme return found\n", line_number);
    return RETURN;
}

[0-9]+ {
    string temp = "CONST_INT";
    SymbolInfo* send = new SymbolInfo(yytext, "CONST_INT", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <CONST_INT> Lexeme %s found\n", line_number, yytext);
    return CONST_INT;
}
[0-9]+[.][0-9]*([eE][-+]?[0-9]+)?|[.][0-9]+([eE][-+]?[0-9]+)?|[0-9]+[eE][-+]?[0-9]+ { 
    string temp = "CONST_FLOAT";
    SymbolInfo* send = new SymbolInfo(yytext, "CONST_FLOAT", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <CONST_FLOAT> Lexeme %s found\n", line_number, yytext);
    return CONST_FLOAT;
}

"+" {
    string temp = "ADDOP";
    SymbolInfo* send = new SymbolInfo(yytext, "ADDOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <ADDOP> Lexeme + found\n", line_number);
    return ADDOP;
}
"-" {
    string temp = "ADDOP";
    SymbolInfo* send = new SymbolInfo(yytext, "ADDOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <ADDOP> Lexeme - found\n", line_number);
    return ADDOP;
}
"*" {
    string temp = "MULOP";
    SymbolInfo* send = new SymbolInfo(yytext, "MULOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <MULOP> Lexeme * found\n", line_number);
    return MULOP;
}
"/" {
    string temp = "MULOP";
    SymbolInfo* send = new SymbolInfo(yytext, "MULOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <MULOP> Lexeme / found\n", line_number);
    return MULOP;
}
"%" {
    string temp = "MULOP";
    SymbolInfo* send = new SymbolInfo(yytext, "MULOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <MULOP> Lexeme %% found\n", line_number);
    return MULOP;
}
"++" {
    string temp = "INCOP";
    SymbolInfo* send = new SymbolInfo(yytext, "INCOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <INCOP> Lexeme ++ found\n", line_number);
    return INCOP;
}
"--" {
    string temp = "INCOP";
    SymbolInfo* send = new SymbolInfo(yytext, "INCOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <INCOP> Lexeme -- found\n", line_number);
    return INCOP;
}
"<" {
    string temp = "RELOP";
    SymbolInfo* send = new SymbolInfo(yytext, "RELOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RELOP> Lexeme < found\n", line_number);
    return RELOP;
}
"<=" {
    string temp = "RELOP";
    SymbolInfo* send = new SymbolInfo(yytext, "RELOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RELOP> Lexeme <= found\n", line_number);
    return RELOP;
}
">" {
    string temp = "RELOP";
    SymbolInfo* send = new SymbolInfo(yytext, "RELOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RELOP> Lexeme > found\n", line_number);
    return RELOP;
}
">=" {
    string temp = "RELOP";
    SymbolInfo* send = new SymbolInfo(yytext, "RELOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RELOP> Lexeme >= found\n", line_number);
    return RELOP;
}
"==" {
    string temp = "RELOP";
    SymbolInfo* send = new SymbolInfo(yytext, "RELOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RELOP> Lexeme == found\n", line_number);
    return RELOP;
}
"!=" {
    string temp = "RELOP";
    SymbolInfo* send = new SymbolInfo(yytext, "RELOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RELOP> Lexeme != found\n", line_number);
    return RELOP;
}
"=" {
    string temp = "ASSIGNOP";
    SymbolInfo* send = new SymbolInfo(yytext, "ASSIGNOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <ASSIGNOP> Lexeme = found\n", line_number);
    return ASSIGNOP;
}
"&&" {
    string temp = "LOGICOP";
    SymbolInfo* send = new SymbolInfo(yytext, "LOGICOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <LOGICOP> Lexeme && found\n", line_number);
    return LOGICOP;
}
"||" {
    string temp = "LOGICOP";
    SymbolInfo* send = new SymbolInfo(yytext, "LOGICOP", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <LOGICOP> Lexeme || found\n", line_number);
    return LOGICOP;
}

"!" {
    string temp = "NOT";
    SymbolInfo* send = new SymbolInfo(yytext, "NOT", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <NOT> Lexeme ! found\n", line_number);
    return NOT;
}
"(" {
    string temp = "LPAREN";
    SymbolInfo* send = new SymbolInfo(yytext, "LPAREN", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <LPAREN> Lexeme ( found\n", line_number);
    return LPAREN;
}
")" {
    string temp = "RPAREN";
    SymbolInfo* send = new SymbolInfo(yytext, "RPAREN", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RPAREN> Lexeme ) found\n", line_number);
    return RPAREN;
}
"{" {
    string temp = "LCURL";
    SymbolInfo* send = new SymbolInfo(yytext, "LCURL", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <LCURL> Lexeme { found\n", line_number);
    myTable.enterScope();
    inside_global_scope = false;
    for(pair<string,string> item: list){
        if(item.second != ""){
            for(char &c : item.first){
                c = toupper(c);
            }
            myTable.insert(item.second, item.first);
        }
    }
    return LCURL;
}
"}" {
    string temp = "RCURL";
    SymbolInfo* send = new SymbolInfo(yytext, "RCURL", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RCURL> Lexeme } found\n", line_number);
    inside_global_scope = true;
    return RCURL;
}
"[" {
    string temp = "LSQUARE";
    SymbolInfo* send = new SymbolInfo(yytext, "LSQUARE", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <LSQUARE> Lexeme [ found\n", line_number);
    return LTHIRD;
}
"]" {
    string temp = "RSQUARE";
    SymbolInfo* send = new SymbolInfo(yytext, "RSQUARE", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <RSQUARE> Lexeme ] found\n", line_number);
    return RTHIRD;
}
"," {
    string temp = "COMMA";
    SymbolInfo* send = new SymbolInfo(yytext, "COMMA", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <COMMA> Lexeme , found\n", line_number);
    return COMMA;
}
";" {
    string temp = "SEMICOLON";
    SymbolInfo* send = new SymbolInfo(yytext, "SEMICOLON", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <SEMICOLON> Lexeme ; found\n", line_number);
    return SEMICOLON;
}
"println" {
    string temp = "PRINTLN";
    SymbolInfo* send = new SymbolInfo(yytext, "PRINTLN", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <PRINTLN> Lexeme println found\n", line_number);
    return PRINTLN;
}
[a-zA-Z_][a-zA-Z0-9_]* { 
    string temp = "ID";
    SymbolInfo* send = new SymbolInfo(yytext, "ID", line_count, line_count, true, temp);
    yylval.symbol_info = send;
    printf("Line# %d: Token <ID> Lexeme %s found\n", line_number, yytext);
    return ID;
}







%%



