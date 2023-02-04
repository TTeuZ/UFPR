module Main where

main :: IO ()
main = do
  print (addInterval 1 7)

addInterval :: Int -> Int -> Int
addInterval x y =
  if x > y
    then 0
    else x + addInterval (x + 1) y

addInterval x y
  | x > y = 0
  | otherwise = x + addInterval (x + 1) y