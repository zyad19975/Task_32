/*============ 1 ============*/
/*List name, age and nationally of customers grandmother with age greater
than forty-five years old, have many hobbies like “swimming”, “reading’,
‘writing’.*/

/*Start by creating a Temp table that contains the id of the Parents of the customers*/
WITH parents AS(
    SELECT GL_account.parent_id As id
    FROM GL_account
    JOIN Customer
    ON GL_account.id = Customer.account_id
),
/*From the parents id we can use it to get their parents so we have the IDs of Grand parents*/
GrandParents AS(
    SELECT GL_account.parent_id AS id
    FROM Customer
    JOIN parents
    ON Customer.id = parents.id
    JOIN GL_account
    ON GL_account.id = Customer.account_id
)
/*From the Grandparents table select only the femals with age greater than 45*/
SELECT C.name, C.age, C.nationally
FROM Customer AS C
JOIN GrandParents AS GP
ON C.id = GP.id AND C.age > 45 AND c.gender = "Female";/*Assume that, this how female is stored in the DB*/

/*============ 2 ============*/
/*List name and code of account receive money in day “10-1-2020”.*/
/*****************************************************************/
/* ASSUME THAT THE ACCOUNT TO RECEIVE MONEY IS THE CUSTOMER TABLE  */
/*****************************************************************/

SELECT C.name, C.code
FROM customer AS C
JOIN GL_account as GL
ON GL.id = C.account_id
JOIN Bill AS BL
ON GL.id = BL.account_id AND DATE_TRUNC('day',BL.date) = “10-1-2020”;

/*============ 3 ============*/
/*List name and code of stores used with branch his code ‘st-1234’*/

SELECT S.name, S.code
FROM store AS S
JOIN Bill as BL
ON S.id = BL.store_id
JOIN branch AS B
ON B.id = BL.branch_id AND B.code = "st-1234";

/*============ 4 ============*/
/*List name, debit and credit of customer for every account even unassigned
with account.*/

SELECT GL.name, GL.debit, GL.credit
FROM GL_account as GL
JOIN customer as C
ON C.account_id = GL.id;

/*============ 5 ============*/
/*List total, VAT, extra, quantity and price for every cost center name and
code*/

SELECT B.total, B.VAT, B.extra , BI.qty, BI.price
FROM Bill as B
JOIN Bill_items as BI
ON B.id = BI.bill_id
JOIN cost_center as cc
ON BI.costcenter_id = cc.id


/*============ 6 ============*/
/*Explain ACID Database principles*/

ACID {
     A: Atomicity,
     C: Consistency
     I: Isolation,
     D: Durability
}

/*--------------------------------------------------------------------------------------------------------------------*/

it refeeres to the standers properties that guarantee the reliablity of the Database
it especially concerned with how a database recovers from any failure that might occur while processing a transaction.

Atomicity:
Atomicity means that you guarantee that either all of the transaction succeeds or none of it does. You don’t get part
of it succeeding and part of it not. If one part of the transaction fails, the whole transaction fails. With atomicity,
it’s either “all or nothing”.

Consistency:
This ensures that you guarantee that all data will be consistent. All data will be valid according to all defined rules,
including any constraints, cascades, and triggers that have been applied on the database.

Isolation:
Guarantees that all transactions will occur in isolation. No transaction will be affected by any other transaction.
So a transaction cannot read data from any other transaction that has not yet completed.

Durability:
Durability means that, once a transaction is committed, it will remain in the system – even if there’s a system crash
immediately following the transaction. Any changes from the transaction must be stored permanently.
If the system tells the user that the transaction has succeeded, the transaction must have, in fact, succeeded.

/*--------------------------------------------------------------------------------------------------------------------*/

if a transaction fails halfway through, it could have major consequences. Money could be debited from the first
account but not credited to the other account.

This is where the ACID principles should apply.
