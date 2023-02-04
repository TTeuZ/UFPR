module Main where

main :: IO ()
main = do
  print (numOfElements "Hello, world!")

numOfElements :: [a] -> Int
numOfElements [] = 0
numOfElements (a:x) = length x + 1