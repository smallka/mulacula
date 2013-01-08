
data OpType = OpPlus | OpMinus

data RPNType = RPNValue Float
            | RPNBinaryOp OpType

calcRPN :: [ RPNType ] -> Float
calcRPN rpns = head $ foldl calcRPN' [] rpns
    where
        calcRPN' stack (RPNValue value) = (value:stack)
        calcRPN' (b:a:rest) (RPNBinaryOp op) = (c:rest)
            where
                c = case op of
                    OpPlus -> a + b
                    OpMinus -> a - b

testRPN = calcRPN [
    (RPNValue 2.0),
    (RPNValue 3.0),
    (RPNValue 5.5),
    (RPNBinaryOp OpMinus),
    (RPNBinaryOp OpPlus) ]
