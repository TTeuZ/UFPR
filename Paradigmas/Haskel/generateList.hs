module Main where

main :: IO ()
main = do
  print ([x | x <- [0 .. 15], mod x 3 == 0])
  print ([[x] | x <- [1..5]])