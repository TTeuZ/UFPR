program programa1;

var ch: char; // armazena um caracter
    string4: array[0..3] of char; // para armazenar um vetor de caracteres
    s, str1, str2: string[10]; // para armazenar string, tem que especificar o tamanho da string
    n: integer;

begin
  str1 := 'abc';
  str2 := '123';
  s := str1 + str2; // concatena as strings
  n := length(s); // pega o tamanhao da string
end.