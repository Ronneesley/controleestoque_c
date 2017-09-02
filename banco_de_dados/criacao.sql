create database if not exists controleestoque;

use controleestoque;

create table paises (
	id int auto_increment primary key,
	nome varchar(100) not null
);

create table produtos (
	id int auto_increment primary key,
	nome varchar(100) not null,
	fornecedor varchar(100) not null,
	precoCompra real not null,
	precoVenda real not null,
	descricao varchar(100) not null,
	qtdEmEstoque int not null,
	dataCadastro timestamp default current_timestamp()
);
