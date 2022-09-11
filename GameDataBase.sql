/*
 Navicat Premium Data Transfer

 Source Server         : ALiTech_0xFFFF
 Source Server Type    : MySQL
 Source Server Version : 80028
 Source Host           : localhost:3306
 Source Schema         : gameserver

 Target Server Type    : MySQL
 Target Server Version : 80028
 File Encoding         : 65001

 Date: 15/04/2022 18:15:47
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for users
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users`  (
  `user_index` int NOT NULL AUTO_INCREMENT,
  `user_id` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `password` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `register_time` date NULL DEFAULT NULL,
  `points` int NULL DEFAULT NULL,
  PRIMARY KEY (`user_index`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of users
-- ----------------------------
INSERT INTO `users` VALUES (1, 'Jaccy', '235712', '2022-04-08', 0);
INSERT INTO `users` VALUES (2, 'mike', '23712', '2022-04-08', 0);
INSERT INTO `users` VALUES (3, 'Tom', 'asdf', '2022-04-09', 0);
INSERT INTO `users` VALUES (4, 'Jack', 'qwert', '2022-04-09', 0);
INSERT INTO `users` VALUES (5, 'LanSan', 'HARRY', '2022-04-13', 0);

-- ----------------------------
-- Function structure for login
-- ----------------------------
DROP FUNCTION IF EXISTS `login`;
delimiter ;;
CREATE FUNCTION `login`(user_name varchar(10),pw varchar(10))
 RETURNS int
BEGIN
	DECLARE userid INT;
	if (LENGTH(user_name) >10|| LENGTH(pw)>10) 
	THEN RETURN 0;
	end if;
	select user_index into userid from users where user_id=user_name and password=pw; 
	if userid is not null  
	then return 1;	
	else return 0;
	end if;
END
;;
delimiter ;

-- ----------------------------
-- Function structure for register
-- ----------------------------
DROP FUNCTION IF EXISTS `register`;
delimiter ;;
CREATE FUNCTION `register`(user_name varchar(10),pw varchar(10))
 RETURNS int
BEGIN
	DECLARE userid INT;
	if (LENGTH(user_name) >10|| LENGTH(pw)>10) 
	THEN RETURN 0;
	end if;
	select user_index into userid from users where user_id=user_name; 
	if userid is not null  
	then return 0;	
	end if;
	INSERT INTO users (user_id,password,register_time,points) values(user_name,pw,CURRENT_DATE(),0);
	return 1;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
