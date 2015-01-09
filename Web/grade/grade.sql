-- MySQL dump 10.13  Distrib 5.6.19, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: grade
-- ------------------------------------------------------
-- Server version	5.6.19-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `tb_grade`
--
 CREATE database IF NOT EXISTS  grade
 CHARACTER SET utf8
 COLLATE  utf8_general_ci;
 
 -- 切换数据库
 USE grade
 CHARSET utf8;

DROP TABLE IF EXISTS `tb_grade`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_grade` (
  `play_id` int(11) NOT NULL COMMENT '选手id',
  `judger1` int(11) NOT NULL DEFAULT 0,
  `judger2` int(11) NOT NULL DEFAULT 0,
  `judger3` int(11) NOT NULL DEFAULT 0,
  `judger4` int(11) NOT NULL DEFAULT 0,
  `judger5` int(11) NOT NULL DEFAULT 0,
  `judger6` int(11) NOT NULL DEFAULT 0,
  `judger7` int(11) NOT NULL DEFAULT 0,
  `judger8` int(11) NOT NULL DEFAULT 0,
  `judger9` int(11) NOT NULL DEFAULT 0,
  `score` float NOT NULL DEFAULT 0,
  PRIMARY KEY (`play_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='评委评分表';
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_grade`
--

LOCK TABLES `tb_grade` WRITE;
/*!40000 ALTER TABLE `tb_grade` DISABLE KEYS */;
INSERT INTO `tb_grade` (play_id) VALUES (1),(2),(3),(4),(5),(6),(7),(8),(9),(10),(11),(12),(13),(14),(15);
/*!40000 ALTER TABLE `tb_grade` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tb_player`
--

DROP TABLE IF EXISTS `tb_player`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tb_player` (
  `play_id` int(11) NOT NULL,
  `name` varchar(255) CHARACTER SET utf8 NOT NULL COMMENT '选手名字',
  PRIMARY KEY (`play_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tb_player`
--

LOCK TABLES `tb_player` WRITE;
/*!40000 ALTER TABLE `tb_player` DISABLE KEYS */;

INSERT INTO `tb_player` VALUES (1,'西邮软件之翼'),(2,'UNT.H'),(3,'小煤球'),(4,'Creator'),(5,'Four In Create'),(6,'Miracle Boy'),(7,'逐梦 "FLY"'),(8,'HomeLeader'),(9,'茅坡计算机小分队'),(10,'御风向荣'),(11,'聪明豆子'),(12,'指尖营养餐APP'),(13,'Four Coders'),(14,'同路人'),(15,'比目鱼');
/*!40000 ALTER TABLE `tb_player` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-12-12 14:01:58
