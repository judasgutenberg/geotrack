 
CREATE TABLE user(
  user_id INT AUTO_INCREMENT PRIMARY KEY,
  email VARCHAR(100) NULL,
  role VARCHAR(100) NULL,
  password VARCHAR(100) NULL,
  expired DATETIME NULL,
  preferences TEXT NULL,
  created DATETIME
);

CREATE TABLE device(
  device_id INT AUTO_INCREMENT PRIMARY KEY,
  device_type_id INT,
  name VARCHAR(100) NULL,
  description VARCHAR(2000) NULL,
  user_id INT NULL,
  sensor_id INT NULL,
  latitude DECIMAL(8,5) NULL,
  longitude DECIMAL(8,5) NULL,
  created DATETIME
);

CREATE TABLE location_data(
  location_data_id INT AUTO_INCREMENT PRIMARY KEY,
  device_id INT NULL,
  recorded DATETIME,
  latitude DECIMAL(8,5) NULL,
  longitude DECIMAL(8,5) NULL,
  rssi INT NULL,
  temperature DECIMAL(6,3) NULL,
  pressure DECIMAL(9,4) NULL,
  humidity DECIMAL(6,3) NULL,
  wind_direction INT NULL,
  precipitation INT NULL,
  wind_speed DECIMAL(8,3) NULL,
  wind_increment INT NULL,
  gas_metric DECIMAL(15,4) NULL,
  sensor_id INT NULL
);


   
 