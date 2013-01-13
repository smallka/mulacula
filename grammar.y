{
module Grammar where
import Scanner
}

%name genTree
%tokentype { Token }
%error { parseError }

%token
	num	{ TokenNum $$ }
	'+'	{ TokenPlus }
	'-'	{ TokenMinus }
	'*'	{ TokenTimes }
	'/'	{ TokenDivide }
	'('	{ TokenOpenBrack }
	')'	{ TokenCloseBrack }

%%

Expr	: Expr '+' Term		{ Plus $1 $3 }
	| Expr '-' Term		{ Minus $1 $3 }
	| Term			{ Term $1 }

Term	: Term '*' Factor	{ Times $1 $3 }
	| Term '/' Factor	{ Divide $1 $3 }
	| Factor		{ Factor $1 }

Factor	: num			{ Num $1 }
	| '(' Expr ')'		{ Brack $2 }

{
parseError :: [ Token ] -> a
parseError _ = error "Parse error"

data Expr
	= Plus Expr Term
	| Minus Expr Term
	| Term Term
	deriving Show

data Term
	= Times Term Factor
	| Divide Term Factor
	| Factor Factor
	deriving Show

data Factor
	= Num Int
	| Brack Expr
	deriving Show

parseTree = genTree . alexScanTokens
}
