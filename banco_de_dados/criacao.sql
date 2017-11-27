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

create table funcionarios (
    id int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
    nome varchar(100) NOT NULL,
	sexo char,
	dataNascimento varchar(10),
	endereco varchar(200),
	cidade varchar(50),
	cep varchar (10),
	telefone varchar(15),
	cpf varchar(14),
	rg varchar(15),
	profissao varchar(50),
    pisPasep  varchar(12)
 );
