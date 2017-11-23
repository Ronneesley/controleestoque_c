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
	id int not null auto_increment,
	nome varchar(65) not null,
	cep varchar(10) not null,
	idEstado int not null,
	constraint foreign key (idEstado) references estados(idEstado),
	primary key (id)
);


create table fornecedor (
	idFornecedor int not null auto_increment primary key,
	nome varchar (100) not null,
	endereco varchar(45) not null,
	telefone varchar(15) not null,
	cnpj varchar (45) not null,
	insc_estadual int not null,
	cep varchar(10) not null,
	data_cadastro datetime not null,
	idCidades int not null,
	constraint foreign key (idCidades) references cidades(id)
);

create table pessoas(
	idPessoas int not null auto_increment primary key,
	nome varchar (100) not null,
	sexo char(1) not null,
	sexo char(1) not null,
	data_nascimento date not null,
	endereco varchar (150) not null,
	cep varchar(10) not null,
	telefone varchar(20) not null,
	cpf varchar (20) not null,
	rg varchar(20) not null
);

CREATE TABLE profissao(
	  idProfissao int auto_increment primary key,
	  profissao varchar(45) not null);

create table funcionarios(
	  idFuncionarios int auto_increment primary key,
	   pis_pasep int (11) not null,
	  fornecedor_idFornecedor INT NOT NULL,
	  Pessoas_idPessoas INT NOT NULL,
	  profissao_idprofissao INT NOT NULL,
	  constraint foreign key (fornecedor_idFornecedor) references fornecedor(idFornecedor),
	    constraint foreign key (Pessoas_idPessoas) references pessoas(idPessoas),
	      constraint foreign key (profissao_idprofissao) references profissao(idProfissao)
);
  


