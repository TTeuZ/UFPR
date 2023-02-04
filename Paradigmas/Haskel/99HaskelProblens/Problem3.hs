module Main where

main :: IO ()
main = do
  print (kElement [10, 22, 13, 44] 1)

kElement :: [a] -> Int -> a
kElement [] k = error "Fora do limite"
kElement (a:x) k
  | k == 1 = a
  | otherwise = kElement x (k - 1)