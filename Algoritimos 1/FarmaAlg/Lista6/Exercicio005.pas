program Exercicio005;

var angulo: real;

(* coloque aqui o codigo da sua funcao que calcula o seno *)

(* coloque aqui o codigo da sua funcao que calcula o cosseno *)

(* coloque aqui o codigo da sua funcao que calcula a tangente *)

begin
    read (angulo);
    if existe_tangente(angulo, tg) then
        writeln (tg:0:3)
    else
        writeln ('nao existe tangente de ',angulo:0:3);
end.