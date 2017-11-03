create database if not exists controleestoque;

use controleestoque;

create table funcionarios (
	idFuncionario int auto_increment primary key not null,
	NomeFuncionario varchar(100) not null,
	SexoFuncionario varchar (2) not null,
	DataNascimentoFuncionario date not null,
	EnderecoFuncionario varchar (300) not null,
	cidadeFuncionario varchar (200) not null,
	cepFuncionario int(10) not null,
	telefoneFuncionario int(10) not null,
	cpfFuncionario int(12) not null,
	rgFuncionario int (10) not null
	profissaoFuncionario varchar(100) not null,
	pisPasepFuncionario varchar (200) not null
	
);
