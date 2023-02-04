module Main where

main :: IO ()
main = do
  print (palindrome "xamax")

palindrome :: Eq a => [a] -> Bool
palindrome [] = True
palindrome a = a == reverse a