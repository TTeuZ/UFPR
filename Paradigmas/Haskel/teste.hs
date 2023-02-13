module Main where

main :: IO ()
main = do
  -- let list = [x * 2 | x <- [1 .. 10]]
  -- print (list)
  -- print (reverseList list)
  -- print (listSize list)
  -- print (cubeList list)

  -- let list2 = ['a', 'b', 'c', 'd']
  -- print (hasChar list2 'g')

  print (ehPrimo 11)

-- reverseList :: [a] -> [a]
-- reverseList [] = []
-- reverseList (a : x) = reverseList x ++ [a]

listSize :: [Int] -> Int
listSize [] = 0
listSize (a : x) = 1 + listSize x

-- cubeList :: [Int] -> [Int]
-- cubeList [] = []
-- cubeList (a : x) = [cube a] ++ cubeList x

-- cube :: Int -> Int
-- cube a = a * a * a

-- hasChar :: [Char] -> Char -> Bool
-- hasChar [] x = False
-- hasChar (h:t) x
--   | x == h = True
--   | otherwise = hasChar t x

ehPrimo :: Int -> Bool
ehPrimo n = 
  if (listSize [x | x <- [1..n], mod n x == 0]) == 2 then True
  else False