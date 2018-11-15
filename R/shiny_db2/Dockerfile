FROM rocker/shiny:3.5.1

ENV PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/lib/jvm/java-8-openjdk-amd64/bin
ENV JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
RUN apt-get update \
    && apt-get install -y --no-install-recommends openjdk-8-jdk liblzma-dev libbz2-dev libicu-dev \
    && update-java-alternatives -s java-1.8.0-openjdk-amd64 \
    && R CMD javareconf \
    && Rscript -e "install.packages(c('leaflet', 'RJDBC'))" \
    && rm -rf /tmp/* \
    && apt-get autoremove -y \
    && apt-get autoclean -y \
    && rm -rf /var/lib/apt/lists/*

# COPY db2jcc*.jar  /opt/ibm/db2/java

USER 1000
