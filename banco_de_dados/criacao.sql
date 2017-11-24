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

create table cidades(
	idCidade int not null auto_increment,
	nomeCidade varchar(65) not null,
	idEstado int not null,
	constraint foreign key (idEstado) references estados(idEstado),
	primary key (id)
);



