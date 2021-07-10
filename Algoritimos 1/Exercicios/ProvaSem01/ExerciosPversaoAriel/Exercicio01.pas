program Exercicio01;

var espigas, graos, graosGerminados, anos: int64;
    peso: double;

begin
  // Inicialização das variaveis
  espigas := 1;
  graos := 150;
  anos := 0;
  peso := 0.150;

  while peso < 100000 do begin  // enquanto a quantidade de graos for menos que 10.000 kg
    graosGerminados := graos - (graos * (10 div 100));
    espigas := graosGerminados * 2;
    graos := espigas * 150;
    anos := anos + 1;
    peso := peso + (graos * 0.001);
  end;
  writeln(anos);
end.

