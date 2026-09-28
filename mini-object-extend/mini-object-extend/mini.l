%{
#include <string.h>
#include "tac.h"
#include "mini.y.h"
void yyerror(char*);
%}

%option noinput nounput yylineno


%x CCOMMENT

ID      [A-Za-z][A-Za-z0-9]*
NUM     [0-9]+

%%


"//"[^\n]*          { /* 忽略 // 注释 */ }
"/*"                { BEGIN(CCOMMENT); }
<CCOMMENT>"*/"      { BEGIN(INITIAL); }
<CCOMMENT>\n        { /* 行号自动增加，忽略 */ }
<CCOMMENT>.         { /* 忽略注释内容 */ }
<CCOMMENT><<EOF>>   { yyerror("unterminated comment"); return 0; }


"int"      { return INT; }
"char"     { return CHAR; }
"struct"   { return STRUCT; }
"typedef"  { return TYPEDEF; }
"->"       { return ARROW; }

"switch"   { return SWITCH; }
"case"     { return CASE; }
"default"  { return DEFAULT; }
"break"    { return BREAK; }
"continue" { return CONTINUE; }

"for"      { return FOR; }
"do"       { return DO; }

"input"    { return INPUT; }
"output"   { return OUTPUT; }
"return"   { return RETURN; }
"if"       { return IF; }
"else"     { return ELSE; }
"while"    { return WHILE; }

"&&"       { return AND; }
"||"       { return OR; }


"'"([^\\\n]|\\.)"'"  {
    char c;
    if (yytext[1] == '\\') {
        switch (yytext[2]) {
            case 'n': c = '\n'; break;
            case 't': c = '\t'; break;
            case 'r': c = '\r'; break;
            case '\\': c = '\\'; break;
            case '\'': c = '\''; break;
            case '0': c = '\0'; break;
            default: c = yytext[2]; break;
        }
    } else {
        c = yytext[1];
    }
    yylval.character = c;
    return CHARACTER;
}


{ID}  {
    yylval.string = strdup(yytext);
    if (is_typedef_name(yytext)) return TYPEID;
    return IDENTIFIER;
}


{NUM} {
    yylval.string = strdup(yytext);
    return INTEGER;
}

\"[^\"]*\"  {
    yylval.string = strdup(yytext);
    return TEXT;
}


"=="  { return EQ; }
"!="  { return NE; }
"<="  { return LE; }
"<"   { return LT; }
">="  { return GE; }
">"   { return GT; }


[ \t\r\n]+   ;
"#".*        ;


.     { return *yytext; }

%%

int yywrap(void) { return 1; }