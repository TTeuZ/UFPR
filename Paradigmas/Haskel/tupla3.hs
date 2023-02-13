module Main where

main :: IO ()
main = do
  print (contMestre base)

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

contMestre :: Int
contMestre 0 = 0
contMestre n = 
  let tupla = base n
  if secondTupla tupla == "mestre" then 1 + contMestre (n - 1)
  else contMestre (n - 1)