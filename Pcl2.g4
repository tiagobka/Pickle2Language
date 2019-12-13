grammar Pcl2;  // A tiny subset of Pascal
@header {
#include "wci/intermediate/TypeSpec.h"
using namespace wci::intermediate;
}

program   : header mainBlock '.' ;
header    : PROGRAM IDENTIFIER ';' ; 
mainBlock : block;
block     : declarations compoundStmt ;

declarations : VAR declList ';' ;
declList     : decl ( ';' decl )* ;
decl         : varList ':' typeId ;
varList      : varId ( ',' varId )* ;
varId        : IDENTIFIER ;
typeId       : IDENTIFIER ;

compoundStmt : BEGIN stmtList END ;

stmt : compoundStmt
     | assignmentStmt
     | printStmt
     | ifStmt
     | keepGoingStmt
     |
     ;
     
stmtList       : stmt ( ';' stmt )* ;
assignmentStmt : variable ':=' expr ;
printStmt      : PRINTF '(' formatString printArg* ')' ;
ifStmt		   : IS '(' expr ')' QM '{' stmtList '}' (ISNT '{' stmtList '}')?;
keepGoingStmt  : KEEP '{' stmtList '}' GOING expr;

formatString   : STRING ;
printArg       : ',' expr ;

variable : IDENTIFIER ;
	
expr locals [ TypeSpec *type = nullptr ]
    : expr mulDivOp expr   # mulDivExpr
    | expr addSubOp expr   # addSubExpr
    | expr cmprOp expr 	   #cmprOpExpr
    | number               # unsignedNumberExpr
    | signedNumber         # signedNumberExpr
    | variable             # variableExpr
    | '(' expr ')'         # parenExpr
    ;
     
mulDivOp : MUL_OP | DIV_OP ;
addSubOp : ADD_OP | SUB_OP ;
cmprOp	 : EQ_OP | GT_OP | LT_OP | NE_OP | GE_OP | LE_OP;
     
signedNumber locals [ TypeSpec *type = nullptr ] 
    : sign number 
    ;
sign : ADD_OP | SUB_OP ;

number locals [ TypeSpec *type = nullptr ]
    : INTEGER    # integerConst
    | FLOAT      # floatConst
    ;

PROGRAM : 'PROGRAM' ;
VAR     : 'VAR' ;
BEGIN   : 'BEGIN' ;
END     : 'END' ;
PRINTF  : 'PRINTF' ;
IS      : 'IS' ;
QM		: '?';
ISNT    : 'ISNT' ;
KEEP    : 'KEEP';
GOING	: 'GOING';
DEF		: 'DEF';
CALL 	: 'CALL';


IDENTIFIER : [a-zA-Z][a-zA-Z0-9]* ;
INTEGER    : [0-9]+ ;
FLOAT      : [0-9]+ '.' [0-9]+ ;

MUL_OP :   '*' ;
DIV_OP :   '/' ;
ADD_OP :   '+' ;
SUB_OP :   '-' ;

EQ_OP  : '==';
GT_OP  : '>';
LT_OP  : '<';
NE_OP  : '!=';
GE_OP  : '>=' | '=>';
LE_OP  : '<=' | '=<';



NEWLINE : '\r'? '\n' -> skip  ;
WS      : [ \t]+ -> skip ; 
//channels { COMMENTS }

LINE_COMMENT
    : '//' ~[\r\n]* -> skip
    ;
    
COMMENT
: '/*' .*? '*/' -> skip
;

QUOTE  : '\'' ;
STRING : QUOTE STRING_CHAR* QUOTE ;

fragment STRING_CHAR : QUOTE QUOTE  // two consecutive quotes
                     | ~('\'')      // any non-quote character
                     ;
