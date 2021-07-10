program prova3;
const max_linha = 1000;
	  max_coluna = 1000;
type  TpMatriz = array [1..max_linha, 1..max_coluna] of integer;
	  TpVetor = array [1..max_coluna] of integer;
var M: TpMatriz;
	V: Tpvetor;
	l,c: integer;

procedure ler_matriz(var M:TpMatriz;l,c:integer);
var i,j : integer;
begin
	for i:= 1 to l do
		for j:= 1 to c do
			read(M[i,j]);
end;

procedure imprime_matriz(var M:TpMatriz; l, c: integer);
var i, j: integer;
begin
	for i:= 1 to l do
	begin
		for j:= 1 to c do
			write(M[i,j]);
		writeln;
	end;
end;

procedure imprime_vetor (var V:TpVetor; tam: integer);
var i: integer;
begin
	for i:=1 to tam do
		write(V[i],' ');
end;

procedure compacta_imagem (var M:TpMatriz; V:TpVetor; l, c: integer);
var atual, cont, i, j, k :integer;
begin
	atual:= 1;
	cont:= 0;
	k:= 0;
	for i:= 1 to l do
		for j:=1 to c do
			if(M[i, j] = atual) then
				cont := cont + 1
			else
			begin
				k:=k + 1;
				V[k]:= cont;
				atual:= M[i,j];
				cont:= 1;
			end;
	if(atual <> 0) then
	begin
		k:= k + 1;
		v[k]:= 0;
	end;
	writeln(k);
	imprime_vetor(V,k);
end;

begin
	read(c, l);
	ler_matriz(M, l, c);
	imprime_matriz(M, l, c);
	compacta_imagem(M, V, l, c);
end.
