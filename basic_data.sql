CREATE TABLE people (name character varying(50),age int);
INSERT INTO people VALUES ('Peter',15);
INSERT INTO people VALUES ('John',19);
INSERT INTO people VALUES ('Richard',35);
INSERT INTO people VALUES ('Michael',55);
INSERT INTO people VALUES ('Joseph',53);
INSERT INTO people VALUES ('Maria',30);
INSERT INTO people VALUES ('Luisa',21);
INSERT INTO people VALUES ('Pedro',20);
INSERT INTO people VALUES ('Simon',56);
INSERT INTO people VALUES ('Juan',70);
INSERT INTO people VALUES ('Andres',80);
INSERT INTO people VALUES ('Guillermo',60);
INSERT INTO people VALUES ('Josefina',25);
INSERT INTO people VALUES ('Andreina',34);
INSERT INTO people VALUES ('Jose',82);
INSERT INTO people VALUES ('Ricardo',26);
INSERT INTO people VALUES ('Luz',90);

SELECT fuzzy.sqlf('CREATE FUZZY PREDICATE young ON 0..120 AS (0,0,20,30)'::text);
SELECT fuzzy.sqlf('CREATE FUZZY PREDICATE old ON 0..120 AS (50,60,INFINIT,INFINIT)'::text);

SELECT * FROM fuzzy.sqlf('SELECT name FROM people WHERE age=young ORDER BY name'::text) AS (name character varying, membdg float);
SELECT * FROM fuzzy.sqlf('SELECT name FROM people WHERE age=old ORDER BY name'::text) AS (name character varying, membdg float);