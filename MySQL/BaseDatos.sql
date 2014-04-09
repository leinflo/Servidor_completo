create database Trabajo_Terminal_II;

use Trabajo_Terminal_II;

create table usuarios (
id_usuario int auto_increment primary key not null,
nombre varchar(30) not null,
apellido_paterno varchar(50) not null,
apellido_materno varchar(50),
correo_electronico varchar(50) not null,
password varchar(50) not null
);

alter table usuarios add unique (correo_electronico);

create table Mon_Proc(
ID int auto_increment primary key not null,
agente varchar(15),
user varchar(50),
nombre_proc varchar(100),
inicio_proc varchar(100),
fin_proc varchar(100)
);

create table Mon_files(
ID int auto_increment primary key not null,
agente varchar(15),
user varchar(50),
archivo varchar(200),
tipo_cambio varchar(50),
momento_de_cambio varchar(50)
);

create table Equipos(
ID int auto_increment primary key not null,
Direccion_IP varchar(15),
digesto_de_verificacion varchar(32),
verificado varchar(2),
conectado varchar(2)
);
