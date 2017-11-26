create database if not exists controleestoque;

use controleestoque;

create table clientes (
	id int primary key auto_increment not null,
	nome varchar(200) not null,
	sexo char,
	data varchar(10),
	endereco varchar(200),
	cidade varchar(50),
	cep varchar (10),
	telefone varchar(15),
	cpf varchar(14),
	rg varchar(15),
	profissao varchar(50)
);
