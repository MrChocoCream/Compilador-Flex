%{
#include <string.h>    
#include <stdio.h>
#include <stdlib.h>
#include "prueba.tab.h"

void add_token(char* type, char* value);
int yyparse(void);

void print_tokens();
void print_syntax_tokens();
void print_error_messages();
void print_tabla_simbolos();
int rule_applied1 = 0; // Variable para rastrear si la regla ya se ha aplicado
int rule_applied2 = 0; // Variable para rastrear si la regla ya se ha aplicado


char* strndup(const char* s, size_t n) {
    char* result;
    size_t len = strlen(s);

    if (n < len)
        len = n;

    result = (char*)malloc(len + 1);
    if (!result)
        return 0;

    result[len] = '\0';
    return (char*)memcpy(result, s, len);
}
%}

%option case-insensitive
%option noyywrap  





CONST_CADENA \"[^\n"]*\"
IDENTIFICADOR [a-zA-Z][a-zA-Z0-9_]*



%%

\"---.*     {
    if (!rule_applied1) {
    
        char* text = strdup(yytext + 4);
        YY_BUFFER_STATE new_buffer = yy_scan_string(text);
        yy_switch_to_buffer(new_buffer);
        rule_applied1 = 1;
        free(text);
    }
}

---\"     {
    if (!rule_applied2) {
        char* text = strdup(yytext);
        text[strlen(text) - 4] = '\0';
        YY_BUFFER_STATE new_buffer = yy_scan_string(text);
        yy_switch_to_buffer(new_buffer);
        rule_applied2 = 1;
        free(text);
    }
}




[\t \n \r] ;

[&]+{IDENTIFICADOR} {
    
    add_token("IMPRIMIR_VAR", yytext + 1);
    yylval.str = strdup(yytext);
    return IMPRIMIR_VAR;
}

{CONST_CADENA} {
    add_token("CONST_CADENA", yytext);
    yylval.str = strndup(yytext + 1, yyleng - 2);
    return CONST_CADENA;
}


(int|char|float|bool|void) {
   add_token("TIPO_DE_DATO", yytext);
    yylval.str = strdup(yytext);
    return TIPO_DE_DATO;
}


"if"|"else"|"for"|"while"|"do"|"printf"|"scanf"|"main" {
    add_token("PALABRA_RESERVADA", yytext);
    yylval.str = strdup(yytext);
    return *yytext;
}




{IDENTIFICADOR} {
   add_token("IDENTIFICADOR", yytext);
 yylval.str = strdup(yytext);  
    return IDENTIFICADOR;
}


[0-9]+(\.[0-9]+)? {
   add_token("NUMERO", yytext);
    yylval.entero = atof(yytext);  
    return NUMERO;
}

"=" {
  add_token("SIMBOLO_ASIGNACION", yytext);
 yylval.str = strdup(yytext); 
    return SIMBOLO_ASIGNACION;
}


("=="|"<"|">"|"<="|">=") {
  add_token("COMPARACION", yytext);
 yylval.str = strdup(yytext); 
    return COMPARACION;
}

"++" {
  add_token("INCREMENTO", yytext);
 yylval.str = strdup(yytext); 
    return INCREMENTO;
}


";" {
    add_token("FIN", yytext);
    yylval.str = strdup(yytext);
    return FIN;  
}

"," {
    add_token("COMA", yytext);
    yylval.str = strdup(yytext);
    return *yytext;  
}

["{" | "}"]   {
    add_token("LLAVE", yytext);
    yylval.str = strdup(yytext);
    return *yytext;
}


["(" | ")"]   {
    add_token("PAREN", yytext);
    yylval.str = strdup(yytext);
    return *yytext;
}




['+'|'\-'|'*'|'/'] {
    add_token("OPERADOR", yytext);
    yylval.str = strdup(yytext); 
    return *yytext;  
}


. {
    add_token("ERROR CARACTER NO RECONOCIDO", yytext);
    yylval.str = strdup(yytext);
    return ERROR;
}

%%



int main() {

    yyparse();
    printf("\{");
    print_tokens();
    print_syntax_tokens();
    print_error_messages();
    print_tabla_simbolos();
    
     printf("}");
    return 0;
}

