
SET @query = CONCAT('CREATE DATABASE ', @dbname);
PREPARE stmt FROM @query;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
SET @query = CONCAT('GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, INDEX, ALTER ON ', @dbname, '.', @dbname, " TO '", @uname, "'@'localhost' IDENTIFIED BY '", @pw, "'");
PREPARE stmt FROM @query;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
