module Main where

main :: IO ()
main = do
  print (lLast ['a', 'c', 'b'])

lLast :: [a] -> a
lLast [] = error "Lista vazia"
lLast [a] = a
lLast (a:x) = lLast x