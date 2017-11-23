CREATE TABLE funcionarios (
  idFuncionario int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  NomeFuncionario varchar(100) NOT NULL,
  SexoFuncionario varchar(2) NOT NULL,
  DataNascimentoFuncionario varchar(11) NOT NULL,
  EnderecoFuncionario varchar(300) NOT NULL,
  cidadeFuncionario varchar(200) NOT NULL,
  cepFuncionario int(10) NOT NULL,
  telefoneFuncionario int(10) NOT NULL,
  cpfFuncionario int(12) NOT NULL,
  rgFuncionario int(10) NOT NULL,
  profissaoFuncionario varchar(100) NOT NULL,
  pisPasepFuncionario  varchar(11) NOT NULL
 );
