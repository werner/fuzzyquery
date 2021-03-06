
CREATE SCHEMA fuzzy;

GRANT USAGE ON SCHEMA fuzzy TO PUBLIC;

SET search_path TO fuzzy;

CREATE TABLE pg_fuzzypredicate (
        id serial,
	predicate CHARACTER VARYING(200),
	beginf CHARACTER VARYING(50), endf CHARACTER VARYING(50),
	minimum CHARACTER VARYING(50), first_core CHARACTER VARYING(50), 
	second_core CHARACTER VARYING(50), maximum CHARACTER VARYING(50)) WITHOUT OIDS;

CREATE TABLE pg_fuzzypred_rel(
        id_fuzzypred integer,
        id_data integer,
        membdg numeric(4,2)) WITHOUT OIDS;

GRANT SELECT ON pg_fuzzypredicate TO PUBLIC;

CREATE OR REPLACE FUNCTION sqlf (text) RETURNS SETOF record
AS '$libdir/fuzzyquery', 'sqlf'
LANGUAGE C VOLATILE STRICT;

CREATE OR REPLACE FUNCTION membdg(double precision,text,text,text,text)
RETURNS float
AS '$libdir/fuzzyquery', 'membdg'
LANGUAGE C;

CREATE OR REPLACE FUNCTION membdg_total(text)
RETURNS float
AS '$libdir/fuzzyquery', 'membdg_total'
LANGUAGE C;
