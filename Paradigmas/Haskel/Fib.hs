module Main where

main :: IO ()
main = do
  print (fib 3)

fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n - 1) + fib (n - 2)


fib :: Int -> Int
fib n
  | n == 0 = 0
  | n == 1 = 1
  | n > 1 = fib (n - 1) + fib (n - 2)


fib :: Int -> Int
fib n = 
  if n <= 1 then n
  else fib (n - 1) + fib (n - 2)