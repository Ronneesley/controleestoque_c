CREATE TABLE funcionarios (
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
