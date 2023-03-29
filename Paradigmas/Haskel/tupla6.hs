module Main where

main :: IO ()
main = do
  print (countMDG 5 "doutor" 'f')

firstTupla :: (String, String, Char) -> String
firstTupla (x, y, z) = x

secondTupla :: (String, String, Char) -> String
secondTupla (x, y, z) = y

thirdTupla :: (String, String, Char) -> Char
thirdTupla (x, y, z) = z

base :: Int -> (String, String, Char)
base x
  | x == 1 = ("joao", "mestre", 'm')
  | x == 2 = ("jonas", "doutor", 'm')
  | x == 3 = ("joice", "mestre", 'f')
  | x == 4 = ("janete", "doutor", 'f')
  | x == 5 = ("jocileide", "doutor", 'f')
  | otherwise = ("ninguem", "", 'x')

countMDG :: Int -> String -> Char -> Int
countMDG 0 _ _ = 0
countMDG n s c
  | secondTupla (base n) == s =
    if thirdTupla (base n) == c then 1 + countMDG (n - 1) s c
    else countMDG (n - 1) s c
  | otherwise =countMDG (n - 1) s c