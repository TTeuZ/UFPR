module Main where

main :: IO ()
main = do
  print (secondTupla ("Batata", "pao", 'd'))
  print (thirdTupla ("Batata", "pao", 'd'))
  print (firstTupla ("Batata", "pao", 'd'))

firstTupla :: (String, String, Char) -> String
firstTupla (x, y, z) = x

secondTupla :: (String, String, Char) -> String
secondTupla (x, y, z) = y

thirdTupla :: (String, String, Char) -> Char
thirdTupla (x, y, z) = z