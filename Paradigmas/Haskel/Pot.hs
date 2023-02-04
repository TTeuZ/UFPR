module Main where

main :: IO ()
main = do
  print (pot 2 2)

pot :: Int -> Int -> Int
pot x 0 = 1
pot x n = x * pot x (n - 1)