create database if not exists controleestoque;

use controleestoque;

create table paises (
	id int auto_increment primary key,
	nome varchar(100) not null
);

create table estados (
	idEstado int auto_increment primary key,
	nomeEstado varchar(100) not null,
	uf varchar(2) not null,
	idPais int not null,
	constraint foreign key (idPais) references paises(id)
);
