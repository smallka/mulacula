{
module Scanner where
}

%wrapper "basic"

$digit = 0-9

token :-
	$white+			;
	$digit+			{ \s -> TokenNum (read s) }
	"+"			{ \s -> TokenPlus }
	"-"			{ \s -> TokenMinus }
	"*"			{ \s -> TokenTimes }
	"/"			{ \s -> TokenDivide }
	"("			{ \s -> TokenOpenBrack }
	")"			{ \s -> TokenCloseBrack }

{
data Token
	= TokenNum Int
	| TokenPlus
	| TokenMinus
	| TokenTimes
	| TokenDivide
	| TokenOpenBrack
	| TokenCloseBrack
	deriving Show
}

