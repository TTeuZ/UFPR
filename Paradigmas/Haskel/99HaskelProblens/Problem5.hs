module Main where

main :: IO ()
main = do
  print (reverseList "Hello, world!")

reverseList :: [a] -> [a]
reverseList [] = []
reverseList (a:x) = reverseList x ++ [a]