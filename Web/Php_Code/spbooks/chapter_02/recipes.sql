#pooker数据库 fror pooker site

#下面这句drop慎用
DROP DATABASE IF EXISTS recipes ;
#创建数据库，指定编码集合和校对规则 
CREATE database IF NOT EXISTS  recipes
CHARACTER SET utf8 
COLLATE  utf8_general_ci;

-- 切换数据库
USE recipes
CHARSET utf8;

#创建recipes表
CREATE TABLE IF NOT EXISTS recipes(
	id  		INT  AUTO_INCREMENT PRIMARY KEY ,
	name		VARCHAR(400) NOT NULL,
	description	TEXT,
	category_id	INT,
	chef		VARCHAR(255),
	created		DATETIME	
)engine = innodb;


#创建categories表  
CREATE TABLE IF NOT EXISTS categories (
	id			INT PRIMARY KEY AUTO_INCREMENT,
	name		VARCHAR(400) NOT NULL
)engine = innodb;


INSERT INTO categories (name)
VALUES ('Starter');
INSERT INTO categories (name)
VALUES ('Main');
INSERT INTO categories (name)
VALUES ('Pudding');

INSERT INTO recipes (name, description, category_id, chef, created)
VALUES ('Apple Crumble','Traditional Pudding with crunchy crumble layered over sweet fruit and baked', 3,'lorna', NOW());
INSERT INTO recipes (name, description, category_id, chef, created)
VALUES ('Fruits Salad','Combination of in-season fruits, covered with fruit juice and served chilled', 3,'lorna', NOW());
