program exercicioA;

var W, A, B, C, X, resultado: real;

begin
  read(X);
  read(C);
  read(B);
  read(A);
  read(W);

  resultado := (W*W) / (A*X*X + B*X + C);
  writeln(resultado);
end.