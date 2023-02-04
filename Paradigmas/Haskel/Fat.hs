main :: IO ()
main = do
  print (fat 4)

fat :: Int -> Int
fat 0 = 1
fat n = n * fat (n - 1)

fat :: Int -> Int
fat n 
  | n == 0 = 1
  | n > 0 = n * fat (n - 1)


fat :: Int -> Int
fat n = 
  if n == 0 then 1
  else n * fat (n - 1)