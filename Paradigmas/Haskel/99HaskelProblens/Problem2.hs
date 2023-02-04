module Main where

main :: IO ()
main = do
  print (lLast [2, 3, 2])

lLast :: [a] -> a
lLast [] = error "Lista vazia"
lLast [a] = error "apenas 1 elemento"
lLast (a:x)
  | length x == 1 = a
  | otherwise = lLast x

lLast (a:x) = 
  if length x == 1 then a
  else lLast x