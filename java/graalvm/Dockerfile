## Stage 1 : build with maven builder image with native capabilities
FROM quay.io/quarkus/centos-quarkus-maven:19.2.1 AS build
WORKDIR /app
COPY src src
COPY pom.xml .
USER root
RUN chown -R quarkus .
USER quarkus
RUN mvn -f pom.xml -Pnative clean package

## Stage 2 : create the docker final image
FROM frolvlad/alpine-glibc:alpine-3.9_glibc-2.29
WORKDIR /work/
COPY --from=build /app/target/*-runner /work/application
RUN chmod 775 /work
EXPOSE 8080
CMD ["./application", "-Dquarkus.http.host=0.0.0.0"]

