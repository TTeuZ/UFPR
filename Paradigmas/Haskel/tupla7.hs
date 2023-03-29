module Main where

main :: IO ()
main = do
  print (listaPesquisadores 5)
  print (onlyDoctors (listaPesquisadores 5))

type Nome = String

type Titulo = String

type Genero = Char

type Pesquisador = (Nome, Titulo, Genero)

type Grupo = [Pesquisador]

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

listaPesquisadores :: Int -> [Pesquisador]
listaPesquisadores 0 = []
listaPesquisadores n = [base n] ++ listaPesquisadores (n - 1)

onlyDoctors :: [Pesquisador] -> [Pesquisador]
onlyDoctors [] = []
onlyDoctors (h : t)
  | secondTupla h == "doutor" = [h] ++ onlyDoctors t
  | otherwise = onlyDoctors t