select   N_NAME, sum(L_QUANTITY) as ITENS_QTD
from     NATION, ORDERS, CUSTOMER, LINEITEM
where    N_NATIONKEY = C_NATIONKEY and 
         C_CUSTKEY = O_CUSTKEY     and 
         O_ORDERKEY = L_ORDERKEY   
group by N_NAME 
having   ITENS_QTD > 62000
order by ITENS_QTD  desc;
