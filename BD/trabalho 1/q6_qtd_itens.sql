select   N_NAME, sum(L_QUANTITY) as ITENS_QTD
from     ORDERS, CUSTOMER, NATION, LINEITEM
where    O_ORDERKEY = L_ORDERKEY and
         C_CUSTKEY = O_CUSTKEY and
         N_NATIONKEY = C_NATIONKEY
group by N_NAME
order by ITENS_QTD desc limit 10;