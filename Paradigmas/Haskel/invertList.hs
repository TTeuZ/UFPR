module Main where

main :: IO ()
main = do
  print (invertList [10.0, 23.3, 12.3, 132.9])

invertList :: [Float] -> [Float]
invertList [] = []
invertList (h:t) = invertList t ++ [h]