module Main where

main :: IO ()
main = do
  print (pairRemove [1..10])

pairRemove :: [Int] -> [Int]
pairRemove [] = []
pairRemove (h:t) 
  | mod h 2 == 0 = pairRemove t
  | otherwise = [h] ++ pairRemove t