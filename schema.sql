create table logradouro
(
logr_id serial primary key,
logr_pais varchar,
logr_estado varchar(2),
logr_cidade varchar,
logr_bairro varchar,
logr_logradouro varchar,
logr_cep varchar
);
insert into logradouro
(logr_pais, logr_estado, logr_cidade, logr_bairro, logr_logradouro, logr_cep)
values('BRASIL', 'SP', 'SÃO PAULO', 'BELA VISTA', 'RUA MANOEL DUTRA', '01328010');
insert into logradouro
(logr_pais, logr_estado, logr_cidade, logr_bairro, logr_logradouro, logr_cep)
values('BRASIL', 'SP', 'SÃO PAULO', 'BELA VISTA', 'RUA ABOLIÇÃO', '01319010');