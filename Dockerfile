
FROM ubuntu:latest

RUN apt-get update

RUN apt-get install -y build-essential cgdb valgrind

RUN apt-get install -y imagemagick

RUN apt-get install -y tcsh

WORKDIR /app

COPY . /app
