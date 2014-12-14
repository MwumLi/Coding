CREATE DATABASE IF NOT EXISTS mail;
USE mail;
CREATE TABLE IF NOT EXISTS users (
	user_id		INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
	name		varchar(250) not null,
	mail		varchar(250) not null
);

