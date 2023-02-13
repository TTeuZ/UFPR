module Main where

main :: IO ()
main = do
  print (generateTupla 10)

generateTupla :: Int -> (Int, Int, Int, Int)
generateTupla n = (n*n, n*n*n, n*n*n*n, n*n*n*n*n)
  