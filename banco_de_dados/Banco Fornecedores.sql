create database controleestoque;

use controleestoque;

CREATE TABLE fornecedores (
  idFornecedor int NOT NULL PRIMARY KEY AUTO_INCREMENT,
  nomeFornecedor varchar(100) DEFAULT NULL,
  CNPJ bigint(14) DEFAULT NULL,
  endFornecedor varchar(150) DEFAULT NULL
  );
