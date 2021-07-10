program Exercicio094;

var valor, desconto, preco: Real;

begin
  read(valor);
  read(desconto);
  preco := valor - desconto;
  writeln(preco:1:0);
end.