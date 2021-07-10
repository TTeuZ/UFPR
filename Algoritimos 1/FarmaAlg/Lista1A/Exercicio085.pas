program Exercicio085;

var diametro, raio, volume: real;

begin
  read(diametro);
  raio := diametro/2;
  volume := ((4*3.14)/3)*(raio*raio*raio);
  writeln(volume:1:2) 
end.