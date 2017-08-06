FROM openjdk:8-jre-slim

ARG GENDEV_VERSION=0.3.0

WORKDIR /game

RUN apt-get update
RUN apt-get -y install texinfo make wget
RUN apt-get clean

RUN wget https://github.com/kubilus1/gendev/releases/download/v${GENDEV_VERSION}/gendev_${GENDEV_VERSION}_all.deb
RUN dpkg -i gendev_${GENDEV_VERSION}_all.deb
RUN rm -rf gendev_${GENDEV_VERSION}_all.deb

ENV GENDEV /opt/gendev

CMD /bin/bash