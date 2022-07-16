select count(distinct(C_CUSTKEY))
from (
    select      distinct(C_CUSTKEY)
    from        CUSTOMER left join ORDERS
    where       O_CUSTKEY = C_CUSTKEY and O_ORDERKEY is not null
    except 
    select      distinct(C_CUSTKEY)
    from        ORDERS, CUSTOMER
    where       O_CUSTKEY = C_CUSTKEY and 
                O_COMMENT like "%special request%"
);