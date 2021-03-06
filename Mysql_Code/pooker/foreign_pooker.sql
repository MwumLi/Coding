#pooker数据库 fror pooker site

#下面这句drop慎用
#DROP DATABASE IF EXISTS pooker ;
#创建数据库，指定编码集合和校对规则 
CREATE database IF NOT EXISTS  pooker
CHARACTER SET utf8 
COLLATE  utf8_general_ci;

-- 切换数据库
USE pooker
CHARSET utf8;

#创建users表
CREATE TABLE IF NOT EXISTS users(
	user_id		INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
	user_type	ENUM('g', 'm') default 'g',
	password	VARBINARY(16) NOT NULL,
	salt		CHAR(20) NOT NULL,
	nick_name	VARCHAR(250) NULL,
	name		VARCHAR(250) NULL,
	pic_name	VARCHAR(250) NULL,
	pic_path	VARCHAR(250) NULL,
	birth		date NULL,
	province	VARCHAR(250) NULL,
	city		VARCHAR(250) NULL,
	sex			ENUM('m', 'f') DEFAULT 'm',
	occupation	VARCHAR(250) NULL,
	phone		CHAR(11) NULL,
	mail		VARCHAR(250) NOT NULL,
	mail_flag	BOOLEAN DEFAULT false,
	reg			DATETIME NOT NULL
)engine = innodb;


#创建lecturers表  
CREATE TABLE IF NOT EXISTS lecturers (
	lecturer_id		SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name			VARCHAR(250) NOT NULL,
	pic_name		VARCHAR(250) NOT NULL,
	pic_path		VARCHAR(250) NOT NULL,
	intro			TEXT NOT NULL
)engine = innodb;


#创建courses
CREATE TABLE IF NOT EXISTS courses (
	course_id	INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	name		VARCHAR(250) NOT NULL,
	path		VARCHAR(250) NOT NULL,
	pic_name	VARCHAR(250) NOT NULL,
	pic_path	VARCHAR(250) NOT NULL,
	intro		TEXT NOT NULL,
	watch_man	INT UNSIGNED DEFAULT 0,
	good_man	INT UNSIGNED DEFAULT 0,

	lecturer_id	SMALLINT UNSIGNED NOT NULL,
	FOREIGN KEY(lecturer_id) REFERENCES lecturers(lecturer_id) ON DELETE CASCADE ON UPDATE CASCADE,

	price		FLOAT DEFAULT 0.0,
	rebate		FLOAT DEFAULT 1.0,
	service		FLOAT DEFAULT 0.0,
	time		TIME NOT NULL,
	type		VARCHAR(250) NOT NULL,
	section		SMALLINT NOT NULL
);

#创建subscription表  
CREATE TABLE IF NOT EXISTS subscription (
	ss_id		INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	course_id	INT UNSIGNED NOT NULL  ,
	FOREIGN KEY(course_id) REFERENCES courses(course_id) ON DELETE CASCADE ON UPDATE CASCADE,

	user_id		INT UNSIGNED NOT NULL  ,
	FOREIGN KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE
);

#创建discussion表  
CREATE TABLE IF NOT EXISTS discussion (
	dis_id		INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	course_id	INT UNSIGNED NOT NULL,
	FOREIGN KEY(course_id) REFERENCES courses(course_id) ON DELETE CASCADE ON UPDATE CASCADE,

	reply_id	INT UNSIGNED NOT NULL,
	FOREIGN KEY(reply_id) REFERENCES discussion(dis_id) ON DELETE CASCADE ON UPDATE CASCADE,

	content		TEXT NOT NULL,
	time		DATETIME NOT NULL
);

#创建evaluation表  
CREATE TABLE IF NOT EXISTS evaluation (
	eva_id		INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	course_id	INT UNSIGNED NOT NULL,
	FOREIGN KEY(course_id) REFERENCES courses(course_id) ON DELETE CASCADE ON UPDATE CASCADE,

	user_id		INT UNSIGNED NOT NULL,
	FOREIGN	KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE ,

	content		TEXT NOT NULL,
	star		tinyint(1) default 5
);

#创建note表  
CREATE TABLE IF NOT EXISTS note (
	note_id			INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	user_id			INT UNSIGNED NOT NULL,
	FOREIGN KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,

	course_id		INT UNSIGNED NOT NULL,
	FOREIGN KEY(course_id) REFERENCES courses(course_id) ON DELETE CASCADE ON UPDATE CASCADE,

	content			TEXT NOT NULL,
	course_time		TIME NOT NULL,
	note_time		DATETIME NOT NULL
);

#创建topic表  
CREATE TABLE IF NOT EXISTS topic (
	topic_id	INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEy,
	
	user_id		INT UNSIGNED NOT NULL,
	FOREIGN KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,

	title		VARCHAR(250) NOT NULL,
	content		TEXT NOT NULL,
	type		VARCHAR(250) NOT NULL,
	lable1		VARCHAR(250) NOT NULL,
	lable2		VARCHAR(250) NOT NULL,
	lable3		VARCHAR(250) NOT NULL,
	browse		INT UNSIGNED NOT NULL,
	reply		INT UNSIGNED NOT NULL,
	time		DATETIME NOT NULL

);

#创建topic_reply表  
CREATE TABLE IF NOT EXISTS topic_reply (
	topic_reply_id	INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	topic_id		INT UNSIGNED NOT NULL,
	FOREIGN KEY(topic_id) REFERENCES topic(topic_id) ON DELETE CASCADE ON UPDATE CASCADE,

	reply_id		INT UNSIGNED NOT NULL,
	FOREIGN KEY(reply_id) REFERENCES topic_reply(topic_reply_id) ON DELETE CASCADE ON UPDATE CASCADE,

	user_id			INT UNSIGNED NOT NULL,
	FOREIGN KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,

	content			TEXT NOT NULL,
	time			DATETIME NOT NULL
);


#创建interview表  
CREATE TABLE IF NOT EXISTS interview (
	view_id			INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	user_id			INT UNSIGNED NOT NULL,
	FOREIGN KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,

	lecturer_id		SMALLINT UNSIGNED NOT NULL,
	FOREIGN KEY(lecturer_id) REFERENCES lecturers(lecturer_id) ON DELETE CASCADE ON UPDATE CASCADE,

	att_name		VARCHAR(250) NOT NULL,
	att_path		VARCHAR(250) NOT NULL
);

#创建cfd表  
CREATE TABLE IF NOT EXISTS cfd (
	cfd_id			INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
	course_name		VARCHAR(250) NOT NULL,
	intro			TEXT NOT NULL,
	do_man			INT UNSIGNED NOT NULL DEFAULT 0,
	deal_man		INT UNSIGNED NOT NULL DEFAULT 0,
	deadline		datetime NOT NULL,
	price			FLOAT NOT NULL DEFAULT 0.0
);

#创建cfd_reply表  
CREATE TABLE IF NOT EXISTS cfd_reply (
	cfd_reply_id	INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,

	cfd_id			INT UNSIGNED NOT NULL ,
	FOREIGN KEY(cfd_id) REFERENCES cfd(cfd_id) ON DELETE CASCADE ON UPDATE CASCADE,

	reply_id		INT UNSIGNED NOT NULL ,
	FOREIGN KEY(reply_id) REFERENCES cfd_reply(cfd_reply_id) ON DELETE CASCADE ON UPDATE CASCADE,

	user_id			INT UNSIGNED NOT NULL,
	FOREIGN KEY(user_id) REFERENCES users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,

	content			TEXT NOT NULL,
	time			DATETIME NOT NULL 
);




