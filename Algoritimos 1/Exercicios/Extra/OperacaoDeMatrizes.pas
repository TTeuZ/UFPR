program OperacaoDeMatrizes;
type matriz = array[0..50, 0..50] of integer;

procedure somar_matrizes(var v, w, soma_v_w: matriz; n,m :integer);
var j,i : integer;
begin
  for i := 0 to n do
    for j := 0 to m do 
      soma_v_w[i,j] := v[i,j] + w[i,j];
end;

procedure multiplicar_matrizes (var mA, mB, mAB: matriz; lin_A, col_A, lin_B, col_B: integer; var lin_AB, col_AB);
var j, i, k: integer;
begin
  lin_AB = lin_A; col_AB := col_B;
  for i := 1 to lin_A do
    for j := 1 to col_B do begin
      mAB[i,j] := 0;
      for k := 1 to lin_b do
        mAB[i,j] := mAB[i,j] + mA[i,k] * mB[k,j];
    end;
end;

begin
end.