module Main where

main :: IO ()
main = do
  print (insertList [1..10] 11)

insertList :: [Int] -> Int -> [Int]
insertList [] x = [x]
insertList (h:t) x 
  | h == x = [h] ++ t
  | otherwise = [h] ++ insertList t x
  