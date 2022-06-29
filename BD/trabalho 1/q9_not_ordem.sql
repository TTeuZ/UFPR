select count(distinct(C_CUSTKEY))
from (
    select  distinct(C_CUSTKEY)
    from    CUSTOMER
    except 
    select  distinct(C_CUSTKEY)
    from    ORDERS, CUSTOMER
    where   O_CUSTKEY = C_CUSTKEY
);