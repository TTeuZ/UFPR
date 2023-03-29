module Main where

main :: IO ()
main = do
  print (countMD 5 "doutor")

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

countMD :: Int -> String -> Int
countMD 0 _ = 0
countMD n s =
  if secondTupla (base n) == s
    then 1 + countMD (n - 1) s
    else countMD (n - 1) s